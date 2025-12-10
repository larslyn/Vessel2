/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/src/eeprom.c $
  $DateTime: 2024/07/05 13:17:52 $
  $Revision: #4 $
  $Author: llu $
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
//#include "stm8s_type.h"
#include "stm8s.h"
#include "s_od.h"
#include "eeprom.h"
//#include "stm8s_iwdg.h"
#include "stm8_hw.h"

/* Defines -------------------------------------------------------------------*/
#define EE_NO_OF_DEFAULT_OD_ENTRIES   4 //number of entries in EE_dafaultEntry
#define EE_NO_OF_SERIAL_NO_OD_ENTRIES 2 //number of entries in EE_dafaultEntry

/* Private variables ---------------------------------------------------------*/
uint8_t *m_pEeprom = (uint8_t*)EEPROM_BaseAddress;

/* Global variables ----------------------------------------------------------*/
extern const OD_InputRegistersEntry_t g_OD_WRITE_HOLDING[OD_NO_OF_WRITEHOLDINGS];

//Default Object dictionary values for restore or blank eeprom
const EE_OD_DefaultEntry_t EE_defaultEntry[EE_NO_OF_DEFAULT_OD_ENTRIES] =
{
  //Adrs in EE,        Default     min value,          max value,          Index in g_OD_WRITE_HOLDING
  //-----------------|----------|-------------------|--------------------|-----------------------------
  {RS485_SPEED_ADRS,   0x02,      RS485_SPEED_MIN,    RS485_SPEED_MAX,     0x01},  /*RS485 speed  1=9600, 2=19200 */
  {RS485_PARITY_ADRS,  0x03,      RS485_PARITY_MIN,   RS485_PARITY_MAX,    0x02},  /*RS485 parity 1=even, 2=odd, 3=noParity */
  {RS485_ID_ADRS,      0x0A,      RS485_ID_MIN,       RS485_ID_MAX,        0x03},  /*RS485 Slave ID */
  {RS485_TERM_ADRS,    0x01,      RS485_TERM_MIN,     RS485_TERM_MAX,      0x04},  /*RS485 Term   1=on,   2=off */
};

//Serial Number Object dictionary values for restore or blank eeprom
const EE_OD_SerialNoEntry_t EE_SerialNoEntry[EE_NO_OF_SERIAL_NO_OD_ENTRIES] =
{
  //Adrs in EE,          Index in g_OD_WRITE_HOLDING
  //-------------------|----------------------------|
  {EE_SERIAL_NO_LO_ADRS,   0x08},  /*Low value of Encoder serial number */
  {EE_SERIAL_NO_HI_ADRS,   0x09}   /*High value of Encoder serial number */
};


/*******************************************************************************
 * @brief Initialize Eeprom with default and Encoder's serial number, calibration
 * @param None
 * @return None
*******************************************************************************/
void EE_init(void)
{
  uint8_t uci;
  uint8_t ucEE_AdrsOffset;
  uint8_t ucTempData;
  uint16_t usTempData16;

  const OD_InputRegistersEntry_t* pOD_WriteHoldingenEntry;

  //check for Data EEPROM unlocked flag
  if(0x00 == (FLASH->IAPSR & FLASH_IAPSR_DUL))
  {
    FLASH->DUKR = 0xAE;
    nop();      //insert nop otherwise compiler optimizer will remove first write
    FLASH->DUKR = 0x56;
  }

  //============================================================================
  //loop through default Eeprom entries
  for(uci = 0; uci < EE_NO_OF_DEFAULT_OD_ENTRIES; ++uci)
  {
    //get Eeprom address
    ucEE_AdrsOffset = EE_defaultEntry[uci].ucEepromAddress;

    //read data from eeprom
    ucTempData = *(m_pEeprom + ucEE_AdrsOffset);

    //set pointer to g_OD_WRITE_HOLDING entry
    pOD_WriteHoldingenEntry = &g_OD_WRITE_HOLDING[EE_defaultEntry[uci].ucODentry];

    //check if the data is within range
    if((ucTempData >= EE_defaultEntry[uci].ucEepromDataMin) &&
        (ucTempData <= EE_defaultEntry[uci].ucEepromDataMax))
    {
      //write data to ram
      *((uint16_t*)pOD_WriteHoldingenEntry->pData) = ucTempData;

    }
    else //Eeprom value is outside range -> update eeprom
    {
      //store default value in Eeprom
      *(m_pEeprom + ucEE_AdrsOffset) = EE_defaultEntry[uci].ucEepromData;

      //write data to ram
      *((uint16_t*)pOD_WriteHoldingenEntry->pData) = EE_defaultEntry[uci].ucEepromData;
    }
  }//for loop

  //============================================================================
  //=============== handle Encoder Serial Number ===============================
  
  //if CTRL byte is not EE_SERIAL_NO_WRITTEN, serial no has not been written -> write all zeroes 
  if(EE_SERIAL_NO_WRITTEN != *(m_pEeprom + EE_SERIAL_NO_CTRL_ADRS))
  {
    //loop 2 times for reading 32 bits serial number 
    for(uci = 0; uci < EE_NO_OF_SERIAL_NO_OD_ENTRIES; ++uci)
    {
      //store default lsb of serial number in Eeprom
      *(m_pEeprom + EE_SerialNoEntry[uci].ucEepromAddress) = 0x00;
      
      //store default msb of serial number in Eeprom
      *(m_pEeprom + (uint8_t)(1 + EE_SerialNoEntry[uci].ucEepromAddress)) = 0x00;
      
      //set pOD_WriteHoldingenEntry to g_OD_WRITE_HOLDING serial no entry
      pOD_WriteHoldingenEntry = &g_OD_WRITE_HOLDING[EE_SerialNoEntry[uci].ucODentry];      
      *((uint16_t*)pOD_WriteHoldingenEntry->pData) = 0x0000;
    }
    
    //write to serial number control byte to written to serial number done
    *(m_pEeprom + EE_SERIAL_NO_CTRL_ADRS) = EE_SERIAL_NO_WRITTEN;
  }
  else //read serial no from Eeprom and store it in holding register
  {
    for(uci = 0; uci < EE_NO_OF_SERIAL_NO_OD_ENTRIES; ++uci)
    {
      //read lsb data from eeprom
      usTempData16 = *(m_pEeprom + EE_SerialNoEntry[uci].ucEepromAddress);

      //read msb data from eeprom
      ucTempData = *(m_pEeprom + EE_SerialNoEntry[uci].ucEepromAddress + 1);
      usTempData16 |= ucTempData << 8;

      //set pOD_WriteHoldingenEntry to g_OD_WRITE_HOLDING serial no entry
      pOD_WriteHoldingenEntry = &g_OD_WRITE_HOLDING[EE_SerialNoEntry[uci].ucODentry];
      *((uint16_t*)pOD_WriteHoldingenEntry->pData) = usTempData16;
    }
  }

  //============================================================================
  //=============== handling calibration register ==============================

  //set pointer to g_OD_WRITE_HOLDING entry for usCalibration (file s_od.h)
  pOD_WriteHoldingenEntry = &g_OD_WRITE_HOLDING[0x0A]; 

  //read lsbyte data from eeprom
  ucTempData   = *(m_pEeprom + EE_CALIBRATION_ADRS);
  usTempData16 = ucTempData;

  //read msbyte data from eeprom
  ucTempData = *(m_pEeprom + EE_CALIBRATION_ADRS + 1);
  usTempData16 |= ucTempData << 8;

  //check if calibration value is within min/max
  if( (usTempData16 >= RS485_CALIBRATION_MIN) && (usTempData16 <= RS485_CALIBRATION_MAX) )
  {
    //write data to ram
    *((uint16_t*)pOD_WriteHoldingenEntry->pData) = usTempData16;
  }
  else
  {
    *(m_pEeprom + EE_CALIBRATION_ADRS)   = (uint8_t)(RS485_CALIBRATION_DEFAULT & 0xFF);
    *(m_pEeprom + EE_CALIBRATION_ADRS+1) = (uint8_t)((RS485_CALIBRATION_DEFAULT & 0xFF00) >> 8);
    *((uint16_t*)pOD_WriteHoldingenEntry->pData) = RS485_CALIBRATION_DEFAULT;
  }

  FLASH->IAPSR &= (uint8_t)(~FLASH_IAPSR_DUL);
}

/*******************************************************************************
 * @brief EE_SaveAll
 * @param None
 * @return None
*******************************************************************************/
void EE_SaveAll(void)
{
  uint8_t uci;
  uint8_t ucEE_AdrsOffset;
  uint8_t ucEEdata;
  uint16_t usRamData;

  const OD_InputRegistersEntry_t* pOD_WriteHoldingenEntry;

  //check for Data EEPROM unlocked flag
  if(0x00 == (FLASH->IAPSR & FLASH_IAPSR_DUL))
  {
    FLASH->DUKR = 0xAE;
    nop();      //insert nop otherwise compiler optimizer will remove first write
    FLASH->DUKR = 0x56;
  }

  WATCHDOG; //clear watchdog
  
  //============================================================================
  //loop through default Eeprom entries
  for(uci = 0; uci < EE_NO_OF_DEFAULT_OD_ENTRIES; ++uci)
  {
    //get Eeprom address
    ucEE_AdrsOffset = EE_defaultEntry[uci].ucEepromAddress;

    //read data from eeprom
    ucEEdata = *(m_pEeprom + ucEE_AdrsOffset);

    //set pointer to g_OD_WRITE_HOLDING entry
    pOD_WriteHoldingenEntry = &g_OD_WRITE_HOLDING[EE_defaultEntry[uci].ucODentry];
    usRamData = *((uint16_t*)pOD_WriteHoldingenEntry->pData);

    //compare Eeprom and ram values
    if(ucEEdata != (uint8_t)usRamData)
    {
      *(m_pEeprom + ucEE_AdrsOffset) = (uint8_t)usRamData;
    }
  }//for loop

  WATCHDOG; //clear watchdog

  //============================================================================
  //=============== handle Encoder Serial Number ===============================
  for(uci = 0; uci < EE_NO_OF_SERIAL_NO_OD_ENTRIES; ++uci)
  {
    //get Eeprom address for lsb byte
    ucEE_AdrsOffset = EE_SerialNoEntry[uci].ucEepromAddress;
      
    //read data from eeprom
    ucEEdata = *(m_pEeprom + ucEE_AdrsOffset);

    //set pointer to g_OD_WRITE_HOLDING entry
    pOD_WriteHoldingenEntry = &g_OD_WRITE_HOLDING[EE_SerialNoEntry[uci].ucODentry];
    
    //read data from holding register 
    usRamData = *((uint16_t*)pOD_WriteHoldingenEntry->pData);

    //compare lsbyte of holding register to Eeprom value
    if(ucEEdata != (uint8_t)usRamData)
    {
      *(m_pEeprom + ucEE_AdrsOffset) = (uint8_t)usRamData;
    }

    //compare msbyte of holding register to Eeprom value
    if( ucEEdata != (uint8_t)((usRamData & 0xFF00) >> 8) )
    {
      *(m_pEeprom + ucEE_AdrsOffset + 1) = (uint8_t)((usRamData & 0xFF00) >> 8);
    }

  }

  WATCHDOG; //clear watchdog

  //============================================================================  
  //=============== handling calibration register ==============================

  //read lsb of calibration register 
  ucEEdata = *(m_pEeprom + EE_CALIBRATION_ADRS);

  //compare lsbyte to check if it is necessary to write to EEprom
  if(ucEEdata != (uint8_t)(CALIBRATION & 0xFF) )
  {
    *(m_pEeprom + EE_CALIBRATION_ADRS)   = (uint8_t)(CALIBRATION & 0xFF);
    *(m_pEeprom + EE_CALIBRATION_ADRS+1) = (uint8_t)((CALIBRATION & 0xFF00) >> 8);
  }

  FLASH->IAPSR &= (uint8_t)(~FLASH_IAPSR_DUL);
}


/*******************************************************************************
 * @brief EE_RestoreAll
 * @param None
 * @return None
*******************************************************************************/
void EE_RestoreAll(void)
{
  uint8_t uci;
  //uint8_t ucEE_AdrsOffset;
  uint8_t ucEEdata;
  uint8_t ucEEdefaultData;

  const OD_InputRegistersEntry_t* pOD_WriteHoldingenEntry;

  //check for Data EEPROM unlocked flag
  if(0x00 == (FLASH->IAPSR & FLASH_IAPSR_DUL))
  {
    FLASH->DUKR = 0xAE;
    nop();      //insert nop otherwise compiler optimizer will remove first write
    FLASH->DUKR = 0x56;
  }
  WATCHDOG;

  //============================================================================
  //loop through default Eeprom entries
  for(uci = 0; uci < EE_NO_OF_DEFAULT_OD_ENTRIES; ++uci)
  {
    //read data from eeprom
    ucEEdata = *(m_pEeprom + EE_defaultEntry[uci].ucEepromAddress);

    //validate if default is different from eeprom
    if(ucEEdata != EE_defaultEntry[uci].ucEepromData)
    {
      //store default value in Eeprom
      *(m_pEeprom + EE_defaultEntry[uci].ucEepromAddress) = EE_defaultEntry[uci].ucEepromData;

      //write data to holding register
      //set pointer to g_OD_WRITE_HOLDING entry
      pOD_WriteHoldingenEntry = &g_OD_WRITE_HOLDING[EE_defaultEntry[uci].ucODentry];
      *((uint16_t*)pOD_WriteHoldingenEntry->pData) = EE_defaultEntry[uci].ucEepromData;
    }
  }//for loop
  
  WATCHDOG; //clear watchdog
    
  //============================================================================
  //=============== handle Encoder Serial Number ===============================
  //write to serial number control byte to indicate not written
  *(m_pEeprom + EE_SERIAL_NO_CTRL_ADRS) = EE_SERIAL_NO_NOT_WRITTEN;

  WATCHDOG; //clear watchdog
  
  //============================================================================
  //=============== handling calibration register ==============================
  *(m_pEeprom + EE_CALIBRATION_ADRS)   = (uint8_t)(RS485_CALIBRATION_DEFAULT & 0xFF);
  *(m_pEeprom + EE_CALIBRATION_ADRS+1) = (uint8_t)((RS485_CALIBRATION_DEFAULT & 0xFF00) >> 8);
  
  //set pointer to g_OD_WRITE_HOLDING entry
  pOD_WriteHoldingenEntry = &g_OD_WRITE_HOLDING[0x0A]; 
  *((uint16_t*)pOD_WriteHoldingenEntry->pData) = RS485_CALIBRATION_DEFAULT;

  FLASH->IAPSR &= (uint8_t)(~FLASH_IAPSR_DUL);
}


/*******************************************************************************
 * @brief Initialize Eeprom
 * @param None
 * @return None
*******************************************************************************/
void EE_ReadByte(uint8_t ucEE_AdrsOffset, uint8_t *pucData)
{
  //read data from eeprom
  *pucData = *(m_pEeprom + ucEE_AdrsOffset);
}

#if 0
/*******************************************************************************
 * @brief Initialize Eeprom
 * @param None
 * @return None
*******************************************************************************/
void EE_ReadShort(uint8_t ucEE_AdrsOffset, uint16_t *pusData)
{
  uint8_t ucTemp;
  //read low byte from eeprom
  ucTemp   = *(m_pEeprom + ucEE_AdrsOffset);
  *pusData = ucTemp;

  ucTemp   = *(m_pEeprom + ucEE_AdrsOffset + 1);
  *pusData |= (ucTemp << 8);
}
#endif