/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/inc/eeprom.h $
  $DateTime: 2025/02/25 10:41:16 $
  $Revision: #4 $
  $Author: llu $
*******************************************************************************/

#ifndef _EEPROM_H_
#define _EEPROM_H_

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Defines -------------------------------------------------------------------*/
#define EEPROM_BaseAddress   0x4000

#define RS485_SPEED_ADRS    (uint8_t)0x00
#define RS485_SPEED_MIN     (uint8_t)0x01
#define RS485_SPEED_MAX     (uint8_t)0x02

#define RS485_PARITY_ADRS   (uint8_t)0x01
#define RS485_PARITY_MIN    (uint8_t)0x01
#define RS485_PARITY_MAX    (uint8_t)0x03

#define RS485_ID_ADRS       (uint8_t)0x02
#define RS485_ID_MIN        (uint8_t)1
#define RS485_ID_MAX        (uint8_t)247

#define RS485_TERM_ADRS     (uint8_t)0x03
#define RS485_TERM_MIN      (uint8_t)0x01
#define RS485_TERM_MAX      (uint8_t)0x02

#define EE_SERIAL_NO_LO_ADRS    (uint8_t)0x08
#define EE_SERIAL_NO_HI_ADRS    (uint8_t)0x0A
#define EE_SERIAL_NO_CTRL_ADRS  (uint8_t)0x0C
#define EE_SERIAL_NO_WRITTEN     (uint8_t)0xAA
#define EE_SERIAL_NO_NOT_WRITTEN (uint8_t)0x55


#define RS485_CALIBRATION_MIN     (uint16_t)390
#define RS485_CALIBRATION_MAX     (uint16_t)410
#define RS485_CALIBRATION_DEFAULT (uint16_t)400 //this is the code disc
#define EE_CALIBRATION_ADRS       (uint8_t)0x0E //adrs for lsbyte of RS485_CALIBRATION_DEFAULT

/* Private typedef -----------------------------------------------------------*/
/***** Structure for needed values to restore EEPROM entry ********************/
typedef struct
{
  uint8_t   ucEepromAddress;    //Address in Eeprom
  uint8_t   ucEepromData;       //Eeprom data
  uint8_t   ucEepromDataMin;    //Eeprom data
  uint8_t   ucEepromDataMax;    //Eeprom data
  uint8_t   ucODentry;          //Entry number in g_OD_WRITE_HOLDING
} EE_OD_DefaultEntry_t;


typedef struct
{
  uint8_t   ucEepromAddress;    //Address in Eeprom
  uint8_t   ucODentry;          //Entry number in g_OD_WRITE_HOLDING
} EE_OD_SerialNoEntry_t;




/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



/*******************************************************************************
 * @brief Initialize Eeprom
 * @param None
 * @return None
*******************************************************************************/
void EE_init(void);
void EE_SaveAll(void);
void EE_RestoreAll(void);



/*******************************************************************************
 * @brief Read one byte from the eeprom
 * @param ucEE_AdrsOffset
 * @param pucData
 * @return None
*******************************************************************************/
void EE_ReadByte(uint8_t ucEE_AdrsOffset, uint8_t *pucData);

//void EE_ReadShort(uint8_t ucEE_AdrsOffset, uint16_t *pusData);

#endif
