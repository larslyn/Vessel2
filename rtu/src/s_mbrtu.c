/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/rtu/src/s_mbrtu.c $
  $DateTime: 2023/04/03 10:32:06 $
  $Revision: #1 $
  $Author: llu $
*******************************************************************************/

/* ----------------------- Platform includes --------------------------------*/

#include "stm8s.h"
#include "stm8s_rs485.h"


/* ----------------------- Modbus includes ----------------------------------*/
#include "s_mb.h"
#include "s_mbrtu.h"
#include "s_portevent.h"

#include "s_mbcrc.h"
#include "stm8_hw.h"


/* ----------------------- Type definitions ---------------------------------*/
typedef enum
{
  STATE_RX_INIT,              /*!< Receiver is in initial state. */
  STATE_RX_IDLE,              /*!< Receiver is in idle state. */
  STATE_RX_RCV,               /*!< Frame is being received. */
  STATE_RX_ERROR              /*!< If the frame is invalid. */
} eMBRcvState;

typedef enum
{
  STATE_TX_IDLE,              /*!< Transmitter is in idle state. */
  STATE_TX_XMIT               /*!< Transmitter is in transfer state. */
} eMBSndState;

/* ----------------------- Static variables ---------------------------------*/
static volatile eMBSndState m_eTxState;
static volatile eMBRcvState m_eRxState;

@near volatile uint8_t  m_ucRTUBuf[MB_SER_PDU_SIZE_MAX];

static volatile uint8_t *m_pucTxBufferCur;
static volatile uint16_t m_usTxBufferLength;

static volatile uint16_t m_usRxBufferIndex;   //index in the Receive buffer


/*******************************************************************************
 * @brief
 * @param ucSlaveAddress
 * @param ucPort
 * @param ucBaudRate
 * @param uParity
 * @return eStopBit
*******************************************************************************/
eMBErrorCode eMBRTUInit(MB_RS485module_t *pRS485module)
{
  eMBErrorCode eStatus = MB_ENOERR;

  disableInterrupts();

  RS485_Init(pRS485module);
  RS485_SymbolTimerInit(pRS485module);
  RS485_TranceiverRxState(ENABLE);

  enableInterrupts();

  return eStatus;
}

/*******************************************************************************
 * @brief
 * @param None
 * @return None
 *******************************************************************************/
void eMBRTUStart(void)
{

  disableInterrupts();
  /* Initially the receiver is in the state STATE_RX_INIT. we start
   * the timer and if no character is received within t3.5 we change
   * to STATE_RX_IDLE. This makes sure that we delay startup of the
   * modbus protocol stack until the bus is free.
   */
  m_eRxState = STATE_RX_INIT;
  RS485_ReceiverEnable(TRUE);
  RS485_SymbolTimerEnable();      //Enable 3.5 symbol timer
  UART3->CR2 |= UART3_CR2_TEN;    //enable UART2 transmitter

  enableInterrupts();
}

/*******************************************************************************
 * @brief
 * @param None
 * @return None
 *******************************************************************************/
void eMBRTUStop(void)
{
  disableInterrupts();
  RS485_ReceiverEnable(FALSE);
  RS485_SymbolTimerDisable();
  enableInterrupts();
}

/*******************************************************************************
 * @brief
 * @param *pucRcvAddress
 * @param **pucFrame
 * @param *pusLength
 * @return eMBErrorCode
 *******************************************************************************/
eMBErrorCode eMBRTUReceive(uint8_t *pucRcvAddress, uint8_t **pucFrame, uint16_t *pusLength)
{
  eMBErrorCode eStatus = MB_ENOERR; //set MB_ENOERR to no error

  WATCHDOG;
  disableInterrupts();
  //assert_param( usRcvBufferPos < MB_SER_PDU_SIZE_MAX );

  /*Length check*/
  if(m_usRxBufferIndex >= MB_SER_PDU_SIZE_MIN)
  {
    /* Save the address field. All frames are passed to the upper layed
     * and the decision if a frame is used is done there. */
    *pucRcvAddress = m_ucRTUBuf[MB_SER_PDU_ADDR_OFF];

    /* Total length of Modbus-PDU is Modbus-Serial-Line-PDU minus
     * size of address field and CRC checksum. */
    *pusLength = (uint16_t)(m_usRxBufferIndex - MB_SER_PDU_PDU_OFF - MB_SER_PDU_SIZE_CRC);

    /* Return the start of the Modbus PDU to the caller. */
    *pucFrame = (uint8_t*) &m_ucRTUBuf[MB_SER_PDU_PDU_OFF];

  }
  else
  {
    eStatus = MB_EIO;
  }

  enableInterrupts();
  return eStatus;
}


/*******************************************************************************
 * @brief
 * @param None
 * @return eMBErrorCode
 *******************************************************************************/
eMBErrorCode eMBRTUSend(uint8_t ucSlaveID, const uint8_t *pucFrame, uint16_t usLength)
{
  eMBErrorCode eStatus = MB_ENOERR;
  uint16_t     usCRC16;

  WATCHDOG;

  /* Check if the receiver is still in idle state. If not we where to
   * slow with processing the received frame and the master sent another
   * frame on the network. We have to abort sending the frame.
   */
  if(m_eRxState == STATE_RX_IDLE)
  {
    /* First byte before the Modbus-PDU is the slave address. */
    m_pucTxBufferCur = (uint8_t*)pucFrame - 1;
    m_usTxBufferLength = 1;

    /* Now copy the Modbus-PDU into the Modbus-Serial-Line-PDU. */
    m_pucTxBufferCur[MB_SER_PDU_ADDR_OFF] = ucSlaveID;
    m_usTxBufferLength += usLength;

    /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
    usCRC16 = usMBCRC16((uint8_t*) m_pucTxBufferCur, m_usTxBufferLength);
    m_ucRTUBuf[m_usTxBufferLength++] = (uint8_t)(usCRC16 & 0xFF);
    m_ucRTUBuf[m_usTxBufferLength++] = (uint8_t)(usCRC16 >> 8);

    /* Activate the transmitter. */
    m_eTxState = STATE_TX_XMIT;

    RS485_ReceiverEnable(FALSE);  //Disable RS485 receiver
    RS485_TranceiverTxState(ENABLE);  //Enable RS485 transceiver
    UART3->CR2 |= UART3_CR2_TIEN;
  }
  else
  {
    eStatus = MB_EIO;
  }
  //enableInterrupts();
  return eStatus;
}

/*******************************************************************************
 * @brief MBRTU_Receive_IT called each time an RX interrupt occurs
 * @param None
 * @return
 *******************************************************************************/
bool MBRTU_Receive_IT(void)
{
  bool      xTaskNeedSwitch = FALSE;
  uint8_t   ucByte;
  uint8_t   ucTempReg;

  assert_param(m_eSndState == STATE_TX_IDLE);

  //check for Parity and framing error
  ucTempReg = (uint8_t)UART3->SR;
  if(ucTempReg & (UART3_SR_PE + UART3_SR_FE))
  {
    m_eRxState = STATE_RX_ERROR;
  }

  /* Always read the character. */
  RS485_ReadByte8(&ucByte);

  switch(m_eRxState)
  {
    /* If a character is received in the INIT state, wait until the frame is finished. */
    case STATE_RX_INIT:
      RS485_SymbolTimerEnable();
      break;

    /* In ERROR state, wait until all characters in the damaged frame are transmitted.*/
    case STATE_RX_ERROR:
      RS485_SymbolTimerEnable();
      break;

    /* In the idle state, wait for a new character. If a character
     * is received the t1.5 and t3.5 timers are started and the
     * receiver is in the state STATE_RX_RECEIVE.
     */
    case STATE_RX_IDLE:
      m_usRxBufferIndex = 0;
      m_ucRTUBuf[m_usRxBufferIndex++] = ucByte;
      m_eRxState = STATE_RX_RCV;

      /* Enable t3.5 timers. */
      RS485_SymbolTimerEnable();
      break;

    /* We are currently receiving a frame. Reset the timer after
     * every character received. If more than the maximum possible
     * number of bytes in a modbus frame is received the frame is
     * ignored.
     */
    case STATE_RX_RCV:
      if(m_usRxBufferIndex < MB_SER_PDU_SIZE_MAX)
      {
        m_ucRTUBuf[m_usRxBufferIndex++] = ucByte;
      }
      else
      {
        m_eRxState = STATE_RX_ERROR;
      }
      RS485_SymbolTimerEnable();
      break;
  }
  return xTaskNeedSwitch;
}

/*******************************************************************************
 * @brief
 * @param None
 * @return eMBErrorCode
 *******************************************************************************/
bool xMBRTUTransmit_IT(void)
{
  bool            xNeedPoll = FALSE;
  static uint8_t ucTempTxByte;
  assert_param(m_eRxState == STATE_RX_IDLE);

  switch(m_eTxState)
  {
    /* We should not get a transmitter event if the transmitter is in
     * idle state.  */
    case STATE_TX_IDLE:
      /* enable receiver*/
      RS485_ReceiverEnable(TRUE);
      break;

    case STATE_TX_XMIT:
      /* check if we are finished. */
      if(m_usTxBufferLength != 0)
      {

        ucTempTxByte = (int8_t)*m_pucTxBufferCur;
        RS485_WriteByte(ucTempTxByte);
        //xMBPortSerialPutByte( (int8_t)*m_pucTxBufferCur );
        m_pucTxBufferCur++;  /* next byte in sendbuffer. */
        m_usTxBufferLength--;

        //check if more data have to be send
        if(m_usTxBufferLength != 0)
        {
          //disable TX complete interrupt
          UART3->CR2 &= (uint8_t)~UART3_CR2_TCIEN;

          //enable DR buffer empty interrupt
          UART3->CR2 |= UART3_CR2_TIEN;
        }
        else
        {
          //enable TX complete interrupt
          UART3->CR2 |= UART3_CR2_TCIEN;

          //disable DR buffer empty interrupt
          UART3->CR2 &= (uint8_t)~UART3_CR2_TIEN;
        }
      }
      else
      {
        //Disable transceiver transmitter
        RS485_TranceiverTxState(DISABLE);

        //disable TX interrupts
        UART3->SR  &= (uint8_t)~UART3_SR_TC;
        UART3->CR2 &= (uint8_t)~(UART3_CR2_TCIEN | UART3_CR2_TIEN);

        xNeedPoll = xMBPortEventPost(EV_FRAME_SENT);
        /* Disable transmitter. This prevents another transmit buffer
         * empty interrupt. */
        RS485_ReceiverEnable(TRUE);
        m_eTxState = STATE_TX_IDLE;
      }
      break;
  }

  return xNeedPoll;
}

/*******************************************************************************
 * @brief
 * @param None
 * @return eMBErrorCode
 *******************************************************************************/
bool xMBRTUTimerT35Expired_IT(void)
{
  bool xNeedPoll = FALSE;

  switch(m_eRxState)
  {
    /* Timer t35 expired. Startup phase is finished. */
    case STATE_RX_INIT:
      xNeedPoll = xMBPortEventPost(EV_READY);
      break;

    /* A frame was received and t35 expired. Notify the listener that
     * a new frame was received. */
    case STATE_RX_RCV:
      xNeedPoll = xMBPortEventPost(EV_FRAME_RECEIVED);
      break;

    /* An error occurred while receiving the frame. */
    case STATE_RX_ERROR:
      break;

    /* Function called in an illegal state. */
    default:
      assert_param((m_eRxState == STATE_RX_INIT) ||
                   (m_eRxState == STATE_RX_RCV) || (m_eRxState == STATE_RX_ERROR));
  }

  //vMBPortTimersDisable();
  RS485_SymbolTimerDisable();
  m_eRxState = STATE_RX_IDLE;

  return xNeedPoll;
}
