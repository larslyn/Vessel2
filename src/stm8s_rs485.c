/*******************************************************************************
 $File: $
 $DateTime: $
 $Revision: $
 $Author: $
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include <stdlib.h>
//#include "stm8s_type.h"
#include "stm8s.h"
#include "stm8s_gpio.h"

#include "stm8s_rs485.h"
#include "stm8_hw.h"

/* MODBUS includes -----------------------------------------------------------*/
#include "s_mbrtu.h"


/* Defines -------------------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

#define _UART_EnableRx()  do  { UART3->SR = 0;                \
                                UART3->CR2 |= UART3_CR2_REN;  \
                                UART3->CR2 |= UART3_CR2_RIEN; \
                              } while(0)

#define _UART_DisableRx() do  {UART3->CR2 &= (uint8_t)~UART3_CR2_RIEN;  \
                                UART3->CR2 &= (uint8_t)~UART3_CR2_REN;  \
                              }while(0)
//------------------------------------------------------------------------------
//#define _UART_GetData()  (UART3->DR)
//#define _UART_GetError() (UART3->SR & (UART3_SR_PE|UART3_SR_FE|UART3_SR_NF|UART3_SR_OR))
//#define _UART_SetData(_data) do { UART3->DR = (uint8_t)(_data); } while(0)
//------------------------------------------------------------------------------
#define _UART_CheckEventRx() (UART3->SR & (UART3_SR_RXNE|UART3_SR_PE|UART3_SR_FE|UART3_SR_NF|UART3_SR_OR))
#define _UART_CheckEventTx() (UART3->SR & UART3_SR_TC)
#define _UART_ResetEventRx() do { UART3->SR &= (uint8_t)~(UART3_SR_RXNE|UART3_SR_PE|UART3_SR_FE|UART3_SR_NF|UART3_SR_OR); } while (0)
#define _UART_ResetEventTx() do { UART3->SR &= (uint8_t)~(UART3_SR_TC|UART3_SR_TXE); } while (0)
//------------------------------------------------------------------------------
#define _IST_Enable()       do { TIM3->CR1 |= TIM3_CR1_CEN; }while (0)
#define _IST_Disable()      do { TIM3->CR1 &= (uint8_t)~TIM3_CR1_CEN; }while (0)

#define _IST_ResetCounter() do { TIM3->CNTRH = 0; \
                                 TIM3->CNTRL = 0; \
                               }while (0)

#define _IST_ResetStatus()  do { TIM3->SR1 = 0; \
                                 TIM3->SR2 = 0; \
                               }while (0)

#define _IST_CheckEvent()   (TIM3->SR1 & TIM3_SR1_UIF)

/* Private typedef -----------------------------------------------------------*/

const UART_Setup_t m_RS485_setup[3] =
{
//values for BBR1 and BBR2 see Table 54 page 334 in refmanual RM0016
// BaudRate, BBR1,   BBR2, prescale,  cycle3.5
  {9600,     0x68,   0x03, 0,         64166},
  {19200,    0x34,   0x01, 0,         32083},
  {57600,    0x11,   0x06, 0,         16000},
};

/*******************************************************************************
 * @brief RS485_Init
 * @param pRS485module
 * @param None
*******************************************************************************/
void RS485_Init(MB_RS485module_t *pRS485module)
{
  pRS485module->uart.ulBaudRate = m_RS485_setup[(pRS485module->ucBaudRateIdx)-1].ulBaudRate;
  pRS485module->uart.uiClkCycles_3_5bit = m_RS485_setup[(pRS485module->ucBaudRateIdx)-1].uiClkCycles_3_5bit;
  pRS485module->uart.ucBBR1     = m_RS485_setup[(pRS485module->ucBaudRateIdx)-1].ucBBR1;
  pRS485module->uart.ucBBR2     = m_RS485_setup[(pRS485module->ucBaudRateIdx)-1].ucBBR2;

  if(pRS485module->ucParityIdx == 0x01)               /*Even parity*/
  {
    pRS485module->uart.eParity = UART3_PARITY_EVEN;
  }
  else if(pRS485module->ucParityIdx == 0x02)          /*Odd parity*/
  {
    pRS485module->uart.eParity = UART3_PARITY_ODD;
  }
  else                                                /*No parity*/
  {
    pRS485module->uart.eParity  = UART3_PARITY_NO;

    /*According to MODBUS RTU standard two stop bits must be used when No parity
     * to ensure one character is always 11 bits   */
    pRS485module->uart.eStopBit = UART3_STOPBITS_2;
  }

  UART3->CR3 |= (uint8_t)pRS485module->uart.eStopBit;  /**< Set the STOP bits number according to UART3_StopBits value  */

  /*Parity*/
  //UART3->CR1 &= (uint8_t)(~(UART3_CR1_PCEN | UART3_CR1_PS  ));  /**< Clear the Parity Control bit */
  UART3->CR1 |= (uint8_t)pRS485module->uart.eParity;  /**< Set the Parity Control bit to UART3_Parity value */

  UART3->BRR2 = pRS485module->uart.ucBBR2;
  UART3->BRR1 = pRS485module->uart.ucBBR1;
}


/*******************************************************************************
 * @brief Enable timer 2
 * @param None
 * @param None
*******************************************************************************/
void RS485_SymbolTimerEnable(void)
{
  /* Clear all flags */
  _IST_ResetCounter();
  _IST_ResetStatus();

  _IST_Enable();
}


/*******************************************************************************
 * @brief Enable timer 2
 * @param None
 * @param None
*******************************************************************************/
void RS485_SymbolTimerDisable(void)
{
  /* Clear all flags */
  _IST_ResetCounter();
  _IST_ResetStatus();

  _IST_Disable();
}


//------------------------------------------------------------------------------
void RS485_SymbolTimerInit(MB_RS485module_t *pRS485module)
{

  uint16_t usAutoReloadVal; //auto reload variable

  // *************  Configure timer  *******************************************
  /* Set auto-reloader @see m_RS485_setup[] */
  TIM3->ARRH = (uint8_t)(pRS485module->uart.uiClkCycles_3_5bit >> 8);
  TIM3->ARRL = (uint8_t)(pRS485module->uart.uiClkCycles_3_5bit & 0xFF);

  /* Set prescaler @see m_RS485_setup[]*/
  TIM3->PSCR = (uint8_t)pRS485module->uart.usTprescaler;

  /* Disable all and enable one pulse mode */
  TIM3->CR1 = TIM3_CR1_OPM;

  /* Generate an update event to reload the Prescaler value immediately */
  TIM3->EGR |= TIM3_EGR_UG;

  /* Clear all flags */
  _IST_ResetCounter();
  _IST_ResetStatus();

  /* Enable update interrupt */
  TIM3->IER |= TIM3_IER_UIE;

  /* Clear all flags */
  _IST_ResetCounter();
  _IST_ResetStatus();
}

/*******************************************************************************
 * @brief Enable/disable serial RS485 interface
 * @param xRxEnable
 * @retval None
*******************************************************************************/
void RS485_ReceiverEnable(bool xRxEnable)
{
  if(xRxEnable)
  {
    RS485_TranceiverRxState(ENABLE);
    _UART_EnableRx();
  }
  else
  {
    RS485_TranceiverRxState(DISABLE);
    _UART_DisableRx();
  }
}


/*******************************************************************************
 * @brief Interrupt UART3 RX Interruption routine.
 * @param None
 * @param None
*******************************************************************************/
@far @interrupt void UART3_RX_IRQHandler(void)
{
  if(_IST_CheckEvent())
  {
    //GPIO_WriteReverse(PORT_INVOUT_CH1, PIN_INVOUT_CH1);
    xMBRTUTimerT35Expired_IT();
  }
  else
  {
    MBRTU_Receive_IT();
    _UART_ResetEventRx();

  }
}


/*******************************************************************************
 * @brief Interrupt UART3 TX Interruption routine.
 * @param None
 * @param None
*******************************************************************************/
@far @interrupt void UART3_TX_IRQHandler(void)
{
#if 0
  static bool x = FALSE;

  if(x==FALSE)
  {
    x = TRUE;
  }
  else
  {
    x = FALSE;
  }
#endif
  xMBRTUTransmit_IT();
  _UART_ResetEventTx();
}


/*******************************************************************************
 * @brief read one byte from the UD
 * @param pointer to data
 * @return TRUE always
*******************************************************************************/
void RS485_ReadByte8(uint8_t *pucByte)
{
  *pucByte = (uint8_t)UART3->DR;
}


/*******************************************************************************
 * @brief read one byte from the UD
 * @param pointer to data
 * @return TRUE always
*******************************************************************************/
bool RS485_WriteByte(uint8_t ucData)
{
  //RS485_TranceiverTxState(ENABLE);
  UART3->DR = ucData;
  //UART3->CR2 &= ~(uint8_t)UART3_CR2_TCIEN;
  //UART3->CR2 |= UART3_CR2_TIEN;      /*Transmitter Interrupt Enable mask  */
  return TRUE;
}

/*******************************************************************************
 * @brief
 * @param eState: set the RS485 transceiver input state. (PC6 = /RE)
 * @return None
*******************************************************************************/
void RS485_TranceiverRxState(FunctionalState eState)
{

  if(DISABLE == eState)
  {
    GPIO_WriteHigh(PORT_RS485_RX_DISABLE, PIN_RS485_RX_DISABLE);
  }
  else
  {
    GPIO_WriteLow(PORT_RS485_RX_DISABLE, PIN_RS485_RX_DISABLE);
  }
}


/*******************************************************************************
 * @brief
 * @param eState: set the RS485 transceiver output state. (PC1 = DE)
 * @return None
*******************************************************************************/
void RS485_TranceiverTxState(FunctionalState eState)
{
  if(DISABLE == eState)
  {
    //Transceiver output tristated
    GPIO_WriteLow(PORT_RS485_TX_ENABLE, PIN_RS485_TX_ENABLE);
  }
  else
  {
    //Transceiver output = DI
    GPIO_WriteHigh(PORT_RS485_TX_ENABLE, PIN_RS485_TX_ENABLE);
  }
}



