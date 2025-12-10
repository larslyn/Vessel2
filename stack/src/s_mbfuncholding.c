/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/stack/src/s_mbfuncholding.c $
  $DateTime: 2024/05/28 10:31:02 $
  $Revision: #2 $
  $Author: llu $
 *******************************************************************************/

/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"

/* ----------------------- Platform includes --------------------------------*/
//#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "s_mb.h"
#include "s_mbconfig.h"
#include "s_mbproto.h"
#include "s_od.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_PDU_FUNC_READ_ADDR_OFF               ( MB_PDU_DATA_OFF + 0)
#define MB_PDU_FUNC_READ_REGCNT_OFF             ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READ_SIZE                   ( 4 )
#define MB_PDU_FUNC_READ_REGCNT_MAX             ( 0x007D )  //max allowed register to read

#define MB_PDU_FUNC_WRITE_ADDR_OFF              ( MB_PDU_DATA_OFF + 0)
#define MB_PDU_FUNC_WRITE_VALUE_OFF             ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_WRITE_SIZE                  ( 4 )

#define MB_PDU_FUNC_WRITE_MUL_ADDR_OFF          ( MB_PDU_DATA_OFF + 0 )
#define MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF        ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF       ( MB_PDU_DATA_OFF + 4 )
#define MB_PDU_FUNC_WRITE_MUL_VALUES_OFF        ( MB_PDU_DATA_OFF + 5 )
#define MB_PDU_FUNC_WRITE_MUL_SIZE_MIN          ( 5 )
//#define MB_PDU_FUNC_WRITE_MUL_REGCNT_MAX        ( 0x0078 )
#define MB_PDU_FUNC_WRITE_MUL_REGCNT_MAX        ( 0x0002 )

#define MB_PDU_FUNC_READWRITE_READ_ADDR_OFF     ( MB_PDU_DATA_OFF + 0 )
#define MB_PDU_FUNC_READWRITE_READ_REGCNT_OFF   ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READWRITE_WRITE_ADDR_OFF    ( MB_PDU_DATA_OFF + 4 )
#define MB_PDU_FUNC_READWRITE_WRITE_REGCNT_OFF  ( MB_PDU_DATA_OFF + 6 )
#define MB_PDU_FUNC_READWRITE_BYTECNT_OFF       ( MB_PDU_DATA_OFF + 8 )
#define MB_PDU_FUNC_READWRITE_WRITE_VALUES_OFF  ( MB_PDU_DATA_OFF + 9 )
#define MB_PDU_FUNC_READWRITE_SIZE_MIN          ( 9 )

/* ----------------------- Static functions ---------------------------------*/
eMBException    prveMBError2Exception(eMBErrorCode eErrorCode);

/* ----------------------- Start implementation -----------------------------*/
/*
    |---------------------------------------------|
    |        Application Data Unit (ADU)          |     
    |---------------------------------------------|
    |  Adrs  |   FuncCode    |   Data   |   CRC   |
    |--------|--------------------------|---------|
             | Protocol Data Unit (PDU) |               
             |--------------------------|          
/*

/*******************************************************************************
 * @brief Handle reading of input registers.
 * @param pucPDU: pointer to Protocol Data Unit (PDU = Frame - adrs & CRC)
 * @param pusLengthPDU: pointer to length of Protocol Data Unit
 * @retval eMBException
 *******************************************************************************/
#if MB_FUNC_READ_INPUT_ENABLED > 0
eMBException eMBFuncReadInputRegister_x04(uint8_t *pucPDU, uint16_t *pusLengthPDU)
{
  uint16_t  usRegAddress;
  uint16_t  usRegCount;
  uint8_t   *pucFrameCur;

  eMBException    eStatus = MB_EX_NONE;
  eMBErrorCode    eRegStatus;

  //check length of Protocol Data Unit
  if(*pusLengthPDU == (MB_PDU_FUNC_READ_SIZE + MB_PDU_SIZE_MIN))
  {
    //get read start address
    usRegAddress = (uint16_t)(pucPDU[MB_PDU_FUNC_READ_ADDR_OFF] << 8);
    usRegAddress |= (uint16_t)(pucPDU[MB_PDU_FUNC_READ_ADDR_OFF + 1]);

    //get bytes to read
    usRegCount = (uint16_t)(pucPDU[MB_PDU_FUNC_READ_REGCNT_OFF] << 8);
    usRegCount = (uint16_t)(pucPDU[MB_PDU_FUNC_READ_REGCNT_OFF + 1]);

    /* Check if the number of registers to read is valid. 
       If not return Modbus illegal data value exception 0x3*/
    if((usRegCount >= 1) && (usRegCount <= MB_PDU_FUNC_READ_REGCNT_MAX))
    {
      /* Set the current PDU data pointer to the beginning. */
      pucFrameCur = &pucPDU[MB_PDU_FUNC_OFF];
      *pusLengthPDU = MB_PDU_FUNC_OFF;

      /* First byte contains the function code. */
      *pucFrameCur++ = MB_FUNC_READ_INPUT_REGISTER_X04;
      *pusLengthPDU += 1;

      /* Second byte in the response contain the number of bytes. */
      *pucFrameCur++ = (uint8_t)(usRegCount * 2);
      *pusLengthPDU += 1;

      /* Make callback to fill the buffer. */
      eRegStatus = eMB_0x04_ReadInputRegistersCB(pucFrameCur, usRegAddress, usRegCount, MB_REG_READ);

      /* If an error occurred convert it into a Modbus exception. */
      if(eRegStatus != MB_ENOERR)
      {
        eStatus = prveMBError2Exception(eRegStatus);
      }
      else
      {
        *pusLengthPDU += usRegCount * 2;
      }
    }
    else
    {
      eStatus = MB_EX_ILLEGAL_DATA_VALUE;
    }
  }
  else
  {
    /* Can't be a valid request because the length is incorrect. */
    eStatus = MB_EX_ILLEGAL_DATA_VALUE;
  }
  return eStatus;
}
#endif



/*******************************************************************************
 * @brief Handle writing of single holding registers.
 * @param pucPDU: pointer to Protocol Data Unit (PDU = Frame - adrs & CRC)
 * @param pusLengthPDU: pointer to length of Protocol Data Unit
 * @retval eMBException
 *******************************************************************************/
#if MB_FUNC_WRITE_HOLDING_ENABLED > 0
eMBException eWriteSingleHoldingReg_x06(uint8_t * pucPDU, uint16_t * pusLengthPDU)
{
  uint16_t        usRegAddress;
  eMBException    eStatus = MB_EX_NONE;
  eMBErrorCode    eRegStatus;

  if(*pusLengthPDU == (MB_PDU_FUNC_WRITE_SIZE + MB_PDU_SIZE_MIN))
  {
    usRegAddress = (uint16_t)(pucPDU[MB_PDU_FUNC_WRITE_ADDR_OFF] << 8);
    usRegAddress |= (uint16_t)(pucPDU[MB_PDU_FUNC_WRITE_ADDR_OFF + 1]);
    //usRegAddress++;

    /* Make callback to update the value. */
    eRegStatus = eMBRegHoldingCB(&pucPDU[MB_PDU_FUNC_WRITE_VALUE_OFF],
                                 usRegAddress, 1, MB_REG_WRITE);

    /* If an error occured convert it into a Modbus exception. */
    if(eRegStatus != MB_ENOERR)
    {
      eStatus = prveMBError2Exception(eRegStatus);
    }
  }
  else
  {
    /* Can't be a valid request because the length is incorrect. */
    eStatus = MB_EX_ILLEGAL_DATA_VALUE;
  }
  return eStatus;
}
#endif


/*******************************************************************************
 * @brief convert MBerror to RTU exception
 * @param eErrorCode: MB errorcode
 * @retval eMBException 
 *******************************************************************************/
eMBException prveMBError2Exception(eMBErrorCode eErrorCode)
{
  eMBException    eStatus;

  switch(eErrorCode)
  {
    case MB_ENOERR:
      eStatus = MB_EX_NONE;
      break;

    case MB_ENOREG:
      eStatus = MB_EX_ILLEGAL_FUNCTION;
      break;

    case MB_EINVAL:
      eStatus = MB_EX_ILLEGAL_DATA_ADDRESS;
      break;

    case MB_EPORTERR:
      eStatus = MB_EX_ILLEGAL_DATA_VALUE;
      break;

    case MB_ETIMEDOUT:
      eStatus = MB_EX_SLAVE_BUSY;
      break;

    default:
      eStatus = MB_EX_SLAVE_DEVICE_FAILURE;
      break;
  }

  return eStatus;
}


#if MB_FUNC_READWRITE_HOLDING_ENABLED > 0

eMBException eMBFuncReadWriteMultipleHoldingRegister(uint8_t *pucPDU, uint16_t *pusLengthPDU)
{
  uint16_t          usRegReadAddress;
  uint16_t          usRegReadCount;
  uint16_t          usRegWriteAddress;
  uint16_t          usRegWriteCount;
  uint8_t           ucRegWriteByteCount;
  uint8_t          *pucFrameCur;

  eMBException    eStatus = MB_EX_NONE;
  eMBErrorCode    eRegStatus;

  if(*pusLengthPDU >= (MB_PDU_FUNC_READWRITE_SIZE_MIN + MB_PDU_SIZE_MIN))
  {
    usRegReadAddress = (uint16_t)(pucPDU[MB_PDU_FUNC_READWRITE_READ_ADDR_OFF] << 8U);
    usRegReadAddress |= (uint16_t)(pucPDU[MB_PDU_FUNC_READWRITE_READ_ADDR_OFF + 1]);
    usRegReadAddress++;

    usRegReadCount = (uint16_t)(pucPDU[MB_PDU_FUNC_READWRITE_READ_REGCNT_OFF] << 8U);
    usRegReadCount |= (uint16_t)(pucPDU[MB_PDU_FUNC_READWRITE_READ_REGCNT_OFF + 1]);

    usRegWriteAddress = (uint16_t)(pucPDU[MB_PDU_FUNC_READWRITE_WRITE_ADDR_OFF] << 8U);
    usRegWriteAddress |= (uint16_t)(pucPDU[MB_PDU_FUNC_READWRITE_WRITE_ADDR_OFF + 1]);
    usRegWriteAddress++;

    usRegWriteCount = (uint16_t)(pucPDU[MB_PDU_FUNC_READWRITE_WRITE_REGCNT_OFF] << 8U);
    usRegWriteCount |= (uint16_t)(pucPDU[MB_PDU_FUNC_READWRITE_WRITE_REGCNT_OFF + 1]);

    ucRegWriteByteCount = pucPDU[MB_PDU_FUNC_READWRITE_BYTECNT_OFF];

    if((usRegReadCount >= 1) && (usRegReadCount <= 0x7D) &&
        (usRegWriteCount >= 1) && (usRegWriteCount <= 0x79) &&
        ((2 * usRegWriteCount) == ucRegWriteByteCount))
    {
      /* Make callback to update the register values. */
      eRegStatus = eMBRegHoldingCB(&pucPDU[MB_PDU_FUNC_READWRITE_WRITE_VALUES_OFF],
                                   usRegWriteAddress, usRegWriteCount, MB_REG_WRITE);

      if(eRegStatus == MB_ENOERR)
      {
        /* Set the current PDU data pointer to the beginning. */
        pucFrameCur = &pucPDU[MB_PDU_FUNC_OFF];
        *pusLengthPDU = MB_PDU_FUNC_OFF;

        /* First byte contains the function code. */
        *pucFrameCur++ = MB_FUNC_READWRITE_MULTIPLE_REGISTERS;
        *pusLengthPDU += 1;

        /* Second byte in the response contain the number of bytes. */
        *pucFrameCur++ = (uint8_t)(usRegReadCount * 2);
        *pusLengthPDU += 1;

        /* Make the read callback. */
        eRegStatus =
          eMBRegHoldingCB(pucFrameCur, usRegReadAddress, usRegReadCount, MB_REG_READ);
        if(eRegStatus == MB_ENOERR)
        {
          *pusLengthPDU += 2 * usRegReadCount;
        }
      }
      if(eRegStatus != MB_ENOERR)
      {
        eStatus = prveMBError2Exception(eRegStatus);
      }
    }
    else
    {
      eStatus = MB_EX_ILLEGAL_DATA_VALUE;
    }
  }
  return eStatus;
}

#endif



#if MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED > 0
//Function code 0x10
eMBException eMBFuncWriteMultipleHoldingRegister(uint8_t * pucPDU, uint16_t * pusLengthPDU)
{
  uint16_t          usRegAddress;
  uint16_t          usRegCount;
  uint8_t           ucRegByteCount;

  eMBException    eStatus = MB_EX_NONE;
  eMBErrorCode    eRegStatus;

  //check PDU lenght
  if(*pusLengthPDU >= (MB_PDU_FUNC_WRITE_MUL_SIZE_MIN + MB_PDU_SIZE_MIN))
  {
    usRegAddress  = (uint16_t)(pucPDU[MB_PDU_FUNC_WRITE_MUL_ADDR_OFF] << 8);
    usRegAddress |= (uint16_t)(pucPDU[MB_PDU_FUNC_WRITE_MUL_ADDR_OFF + 1]);

    usRegCount = (uint16_t)(pucPDU[MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF] << 8);
    usRegCount |= (uint16_t)(pucPDU[MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF + 1]);

    ucRegByteCount = pucPDU[MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF];

    if((usRegCount >= 1) &&
        (usRegCount <= MB_PDU_FUNC_WRITE_MUL_REGCNT_MAX) &&
        (ucRegByteCount == (uint8_t)(2 * usRegCount)))
    {
      /* Make callback to update the register values. */
      eRegStatus = eMBRegHoldingCB(&pucPDU[MB_PDU_FUNC_WRITE_MUL_VALUES_OFF],
                   usRegAddress, usRegCount, MB_REG_WRITE);

      /* If an error occured convert it into a Modbus exception. */
      if(eRegStatus != MB_ENOERR)
      {
        eStatus = prveMBError2Exception(eRegStatus);
      }
      else
      {
        /* The response contains the function code, the starting
         * address and the quantity of registers. We reuse the
         * old values in the buffer because they are still valid.
         */
        *pusLengthPDU = MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF;
      }
    }
    else
    {
      eStatus = MB_EX_ILLEGAL_DATA_VALUE;
    }
  }
  else
  {
    /* Can't be a valid request because the length is incorrect. */
    eStatus = MB_EX_ILLEGAL_DATA_VALUE;
  }
  return eStatus;
}
#endif

