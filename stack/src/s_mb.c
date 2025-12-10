/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/stack/src/s_mb.c $
  $DateTime: 2024/05/28 10:31:02 $
  $Revision: #3 $
  $Author: llu $
*******************************************************************************/

/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"

/* ----------------------- Platform includes --------------------------------*/
#include "stm8s.h"
#include "eeprom.h"
#include "stm8s_rs485.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "s_mbconfig.h"
#include "s_mbproto.h"
#include "s_portevent.h"
#include "s_mb.h"
#include "s_mbrtu.h"
#include "s_od.h"
#include "s_mbfunc.h"
#include "s_mbcrc.h"
//#include "encoder.h"
//#include "motorbox.h"

#define _SW_RESET()  do {WWDG->CR = WWDG_CR_WDGA;} while(0)

extern const OD_InputRegistersEntry_t g_OD_INPUT_REGISTER[OD_NO_OF_READINPUTREGISTERS];

/* ----------------------- Static variables ---------------------------------*/

static uint8_t  m_ucSlaveID = 0;
static bool m_ReceivedFrameIsBroadcast = 0; //used in motorbox 
MB_t MBB;
MB_t *MB = &MBB;

static enum
{
  STATE_ENABLED,
  STATE_DISABLED,
  STATE_NOT_INITIALIZED
} eMBState = STATE_NOT_INITIALIZED;

//BOOL(*pxMBFrameCBReceiveFSMCur)(void);
//BOOL(*pxMBFrameCBTransmitFSMCur)(void);

/* An array of Modbus functions handlers which associates Modbus function
 * codes with implementing functions.
 */
static xMBFunctionHandler xFuncHandlers[MB_FUNC_HANDLERS_MAX] =
{

#if MB_FUNC_OTHER_REP_SLAVEID_ENABLED > 0
  {MB_FUNC_OTHER_REPORT_SLAVEID, eMBFuncReportSlaveID},
#endif

#if MB_FUNC_READ_INPUT_ENABLED > 0
  {MB_FUNC_READ_INPUT_REGISTER_X04, eMBFuncReadInputRegister_x04},
#endif

#if MB_FUNC_READ_HOLDING_ENABLED > 0
  {MB_FUNC_READ_HOLDING_REGISTER, eMBFuncReadHoldingRegister},
#endif

#if MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED > 0
  {MB_FUNC_WRITE_MULTIPLE_REGISTERS, eMBFuncWriteMultipleHoldingRegister},
#endif

#if MB_FUNC_WRITE_HOLDING_ENABLED > 0
  {MB_FUNC_WRITE_REGISTER_X06, eWriteSingleHoldingReg_x06},
#endif

#if MB_FUNC_READWRITE_HOLDING_ENABLED > 0
  {MB_FUNC_READWRITE_MULTIPLE_REGISTERS, eMBFuncReadWriteMultipleHoldingRegister},
#endif

#if MB_FUNC_READ_COILS_ENABLED > 0
  {MB_FUNC_READ_COILS, eMBFuncReadCoils},
#endif

#if MB_FUNC_WRITE_COIL_ENABLED > 0
  {MB_FUNC_WRITE_SINGLE_COIL, eMBFuncWriteCoil},
#endif

#if MB_FUNC_WRITE_MULTIPLE_COILS_ENABLED > 0
  {MB_FUNC_WRITE_MULTIPLE_COILS, eMBFuncWriteMultipleCoils},
#endif

#if MB_FUNC_READ_DISCRETE_INPUTS_ENABLED > 0
  {MB_FUNC_READ_DISCRETE_INPUTS, eMBFuncReadDiscreteInputs},
#endif
};

/*******************************************************************************
* @brief Initialize the Modbus
* @param ucSlaveAddress
* �param ulBaudRate
* @eParity
* @retval eMBErrorCode
*******************************************************************************/
eMBErrorCode eMBInit(uint8_t ucSlaveAddress,
                     uint8_t ucBaudRateIdx,
                     uint8_t ucParityIdx,
                     UART3_StopBits_TypeDef eStopBit)
{
  eMBErrorCode    eStatus = MB_ENOERR;

  //allocate memory for MB_RS485module_t
  MB->RS485module = (MB_RS485module_t*)calloc(1,sizeof(MB_RS485module_t));
  
  //allocate memory for MotorBox_t
  //MB->MotorBoxModule = (MotorBox_t*)calloc(1,sizeof(MotorBox_t));

  MB->RS485module->ucSlaveID     = ucSlaveAddress;
  MB->RS485module->ucBaudRateIdx = ucBaudRateIdx;
  MB->RS485module->ucParityIdx   = ucParityIdx;
  MB->RS485module->uart.eStopBit = eStopBit;

  MB->RS485module->ucUnlock = FALSE;

  /* check preconditions */
  if((ucSlaveAddress == MB_ADDRESS_BROADCAST) ||
      (ucSlaveAddress < MB_ADDRESS_MIN) || (ucSlaveAddress > MB_ADDRESS_MAX))
  {
    eStatus = MB_EINVAL;
  }
  else
  {
    m_ucSlaveID = ucSlaveAddress;
    eStatus = eMBRTUInit(MB->RS485module);

    if(eStatus == MB_ENOERR)
    {
      if(!xMBPortEventInit())
      {
        /* port dependent event module initalization failed. */
        eStatus = MB_EPORTERR;
      }
      else
      {
        eMBState = STATE_DISABLED;
      }
    }
  }
  return eStatus;
}

/*******************************************************************************
 * @brief
 * @param
 * @return
*******************************************************************************/
eMBErrorCode eMBClose(void)
{
  eMBErrorCode    eStatus = MB_ENOERR;

  if(eMBState == STATE_DISABLED)
  {
    eMBRTUStop();
  }
  else
  {
    eStatus = MB_EILLSTATE;
  }
  return eStatus;
}

/*******************************************************************************
 * @brief
 * @param None
 * @return eMBErrorCode
*******************************************************************************/
eMBErrorCode eMBEnable(void)
{
  eMBErrorCode eStatus = MB_ENOERR;

  if(eMBState == STATE_DISABLED)
  {
    /* Activate the protocol stack. */
    eMBRTUStart();
    eMBState = STATE_ENABLED;
  }
  else
  {
    eStatus = MB_EILLSTATE;
  }
  return eStatus;
}

/*******************************************************************************
 * @brief
 * @param None
 * @return eMBErrorCode
*******************************************************************************/
eMBErrorCode eMBDisable(void)
{
  eMBErrorCode    eStatus;

  if(eMBState == STATE_ENABLED)
  {
    //pvMBFrameStopCur(); //eMBRTUStop
    eMBRTUStop();
    eMBState = STATE_DISABLED;
    eStatus = MB_ENOERR;
  }
  else if(eMBState == STATE_DISABLED)
  {
    eStatus = MB_ENOERR;
  }
  else
  {
    eStatus = MB_EILLSTATE;
  }
  return eStatus;
}

/*******************************************************************************
 * @brief
 * @param None
 * @return eMBErrorCode
*******************************************************************************/
eMBErrorCode eMBPoll(void)
{
  static uint8_t  *pucMBFrame;
  static uint8_t  ucRcvAddress;
  static uint8_t  ucFunctionCode;
  static uint16_t usLength;
  static eMBException eException;

  uint8_t         uci;
  eMBErrorCode    eStatus = MB_ENOERR;
  eMBEventType    eEvent;

  /* Check if the protocol stack is ready. */
  if(eMBState != STATE_ENABLED)
  {
    return MB_EILLSTATE;
  }

  /* Check if there is a event available. If not return control to caller.
   * Otherwise we will handle the event. */
  if(xMBPortEventGet(&eEvent) == TRUE)
  {
    switch(eEvent)
    {
      /* No event in queue  ------------------------------*/
      case EV_READY:
        break;

      /* A frame has been received -----------------------*/
      case EV_FRAME_RECEIVED:

        eStatus = eMBRTUReceive(&ucRcvAddress, &pucMBFrame, &usLength);

        if(eStatus == MB_ENOERR)
        {
          COUNTER_PACKET++;
          /* Check if the frame is for us. If not ignore the frame. */
          if((ucRcvAddress == m_ucSlaveID) || (ucRcvAddress == MB_ADDRESS_BROADCAST))
          {
            if(usMBCRC16((uint8_t*)(pucMBFrame-MB_SER_PDU_PDU_OFF),
                         usLength+MB_SER_PDU_PDU_OFF+MB_SER_PDU_SIZE_CRC) == 0)
            {
              if(ucRcvAddress == MB_ADDRESS_BROADCAST)
              {
                m_ReceivedFrameIsBroadcast = TRUE;
              }
              else
              {
                m_ReceivedFrameIsBroadcast = FALSE;
              }
              (void)xMBPortEventPost(EV_EXECUTE);
            }
          }
        }
        break;

      /* Execute event  ---------------------------------*/
      case EV_EXECUTE:
        ucFunctionCode = pucMBFrame[MB_PDU_FUNC_OFF];
        eException = MB_EX_ILLEGAL_FUNCTION;

        for(uci = 0; uci < MB_FUNC_HANDLERS_MAX; uci++)
        {
          /* No more function handlers registered. Abort. */
          if(xFuncHandlers[uci].ucFunctionCode == 0)
          {
            break;
          }
          else if(xFuncHandlers[uci].ucFunctionCode == ucFunctionCode)
          {
            eException = xFuncHandlers[uci].pxHandler(pucMBFrame, &usLength);
            nop();
            nop();

            break;
          }
        }

        /* If the request was not sent to the broadcast address we
         * return a reply. */
        if(ucRcvAddress != MB_ADDRESS_BROADCAST)
        {
          if(eException != MB_EX_NONE)
          {
            /* An exception occurred. Build an error frame. */
            usLength = 0;
            pucMBFrame[usLength++] = (uint8_t)(ucFunctionCode | MB_FUNC_ERROR);
            pucMBFrame[usLength++] = eException;
          }
          eStatus = eMBRTUSend(m_ucSlaveID, pucMBFrame, usLength);
        }
        break;

      /* Frame sent event -------------------------------*/
      case EV_FRAME_SENT:
        break;
    }
  }
  return MB_ENOERR;
}

#if 0
/*dummy function*/
void vMBPortTimersDelay(uint16_t usDummy)
{
  return;
}
#endif

/*******************************************************************************
 * @brief Read Input Registers, Function-code 0x04
 * @param *pucRegBuffer
 * @param usAddress
 * @param usNRegs
 * @param eMode
 * @return eMBErrorCode
*******************************************************************************/
eMBErrorCode eMB_0x04_ReadInputRegistersCB(uint8_t *pucRegBuffer, 
                                           uint16_t usAddress,  
                                           uint16_t usNRegs, 
                                           eMBRegisterMode eMode)
{
  uint16_t usi;
  uint16_t usTemp;

  const OD_InputRegistersEntry_t* pOD_InputHoldingenEntry;

  if(MB_REG_READ == eMode)
  {
    //check if start address + Numbers of Input register to read, is valid
    if((usAddress + usNRegs) > OD_NO_OF_READINPUTREGISTERS)
    {
      return MB_EINVAL;
    }


    //check for requested numbers of registers to read, is valid 
    if(usNRegs > MB_MAX_HOLDINGs_TO_READ)
    {
      return MB_EINVAL; //return exception 0x02 
    }

    //loop through register
    for(usi = usAddress; usi < (usAddress + usNRegs); ++usi)
    {

      //set pointer to g_OD_INPUTHOLDINGS entry
      pOD_InputHoldingenEntry = &g_OD_INPUT_REGISTER[usi];

      //read data
      disableInterrupts();
      usTemp = *(uint16_t*)pOD_InputHoldingenEntry->pData;
      enableInterrupts();

      *(uint16_t*)pucRegBuffer = usTemp;
      pucRegBuffer++;
      pucRegBuffer++;
    }
  }

  return MB_ENOERR;
}


/*******************************************************************************
 * @brief Read/Write Holding Registers, 0x6 write
 * @param *pucRegBuffer
 * @param usAddress
 * @param usNRegs
 * @param eMode
 * @return eMBErrorCode
*******************************************************************************/
eMBErrorCode eMBRegHoldingCB(uint8_t *pucRegBuffer,
                             uint16_t usAddress,
                             uint16_t usNRegs,
                             eMBRegisterMode eMode)
{
  uint16_t usi;
  uint16_t usTemp;
  eMBErrorCode eRetval = MB_ENOERR;

  if(MB_REG_WRITE == eMode)
  {
    if((usAddress + usNRegs) > OD_NO_OF_WRITEHOLDINGS)
    {
      return MB_ENOREG;
    }

    //loop through register
    for(usi = usAddress; usi < (usAddress + usNRegs); ++usi)
    {
      switch(usi)
      {
        /*clear CCW and CW counters*/
        case 0x0000:

          usTemp = *(uint16_t*)pucRegBuffer;

          if(0xFF == usTemp)
          {
            disableInterrupts();
            COUNTER_CCW_LO = 0;
            COUNTER_CCW_HI = 0;
            COUNTER_CW_LO  = 0;
            COUNTER_CW_HI  = 0;
            COUNTER_RESET = (uint16_t)pucRegBuffer[usi];
            //resetTachoCounters();
            enableInterrupts();
          }
          break;

        /*Write Modbus speed -------------------------------------------------*/
        case 0x0001:
          usTemp = *(uint16_t*)pucRegBuffer;
          //validate if write value are between MIN and MAX
          if(usTemp >= RS485_SPEED_MIN && usTemp <= RS485_SPEED_MAX)
          {
            RS485_SPEED = usTemp;
          }
          else
          {
            eRetval = MB_ENORES;
          }
          break;

        /*Write Modbus parity ------------------------------------------------*/
        case 0x0002:
          usTemp = *(uint16_t*)pucRegBuffer;

          //validate if write value are between MIN and MAX
          if(usTemp >= RS485_PARITY_MIN && usTemp <= RS485_PARITY_MAX)
          {
            RS485_PARITY = usTemp;
          }
          else
          {
            eRetval = MB_ENORES;
          }
          break;

        /*Write Modbus Slave ID ----------------------------------------------*/
        case 0x0003:
          usTemp = *(uint16_t*)pucRegBuffer;

          //validate if write value are between MIN and MAX
          if(usTemp >= RS485_ID_MIN && usTemp <= RS485_ID_MAX)
          {
            RS485_SLAVEID = usTemp;
          }
          else
          {
            eRetval = MB_ENORES;
          }
          break;

        /*Write Modbus 120ohm termination ------------------------------------*/
        /* 1=on 2=off*/
        case 0x0004:
          usTemp = *(uint16_t*)pucRegBuffer;

          //validate if write value are between MIN and MAX
          if(usTemp >= RS485_TERM_MIN && usTemp <= RS485_TERM_MAX)
          {
            RS485_TERM = usTemp;
          }
          else
          {
            eRetval = MB_ENORES;
          }
          break;

        /*Write save values to eeprom ----------------------------------------*/
        case 0x0005:
          usTemp = *(uint16_t*)pucRegBuffer;

          //validate if write value is 0x6F6C => "sa"ve
          if(usTemp == 0x6173)
          {
            EE_SaveAll();
          }
          break;

        /*Write load/restore default eeprom value ----------------------------*/
        case 0x0006:
          usTemp = *(uint16_t*)pucRegBuffer;

          //validate if write value is 0x6F6C => "lo"ad
          if(usTemp == 0x6F6C)
          {
            EE_RestoreAll();
          }
          break;

        /*Write reset and enable/Disable write to serial register ------------*/
        case 0x0007:
          usTemp = *(uint16_t*)pucRegBuffer;

          //validate if write value is 0xAAAA
          //if(usTemp == 0xAAAA)
          if(usTemp == 0x5330)
          {
            _SW_RESET();
            //RS485_RESET = 1;
          }
          
          //enable write to Serial No register
          if(usTemp == 0x0020)
          {
            MB->RS485module->ucUnlock = TRUE;            
          }

          //enable write to Serial No register
          if(usTemp == 0x0010)
          {
            MB->RS485module->ucUnlock = FALSE;            
          }

          break;

        /*Write Serial number low --------------------------------------------*/
        case 0x0008:
          usTemp = *(uint16_t*)pucRegBuffer;

          //check if write to Serial No register is enabled
          if(TRUE == MB->RS485module->ucUnlock)
          {
            SERIAL_NO_LO = usTemp;
          }
          else
          {
            eRetval = MB_ENORES;     //insufficient resources
          }
          break;



        /*Write Serial number high -------------------------------------------*/
        case 0x0009:
          usTemp = *(uint16_t*)pucRegBuffer;

          //check if write to Serial No register is enabled
          if(TRUE == MB->RS485module->ucUnlock)
          {
            SERIAL_NO_HI = usTemp;
          }
          else
          {
            eRetval = MB_ENORES;     //insufficient resources
          }
          break;

        /*Write calibration --------------------------------------------------*/
        case 0x000A:
          usTemp = *(uint16_t*)pucRegBuffer;

          //validate if write value are between MIN and MAX values
          if(usTemp >= RS485_CALIBRATION_MIN && usTemp <= RS485_CALIBRATION_MAX)
          {
            //check if it is allow to write to calibration register
            if(TRUE == MB->RS485module->ucUnlock)
            {
              CALIBRATION = usTemp;
            }
            else
            {
              eRetval = MB_ENORES;  
            }
          }
          else
          {
            eRetval = MB_ENORES;
          }
          break;

        /*Set_MotorParameters ------------------------------------------------*/
        case 0x000B:
          usTemp = *(uint16_t*)pucRegBuffer;
          //eRetval = motor_SetParameters(usTemp, m_ReceivedFrameIsBroadcast);
          break;
        
        /*Set_MotorState -----------------------------------------------------*/
        case 0x000C:
          usTemp = *(uint16_t*)pucRegBuffer;
          //eRetval = motor_SetState(usTemp, m_ReceivedFrameIsBroadcast);
          break;

        default:
          break;
      
      }//end of switch
      
      //increment pucRegBuffer more register might be written to 
      pucRegBuffer = pucRegBuffer + 2;
    }//for(usi = usAddress; usi < (usAddress + usNRegs); ++usi)

  }

  return eRetval;
}
