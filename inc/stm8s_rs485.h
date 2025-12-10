/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/inc/stm8s_rs485.h $
  $DateTime: 2024/05/28 10:31:02 $
  $Revision: #3 $
  $Author: llu $
*******************************************************************************/

#ifndef _RS485_H
#define _RS485_H

//#include "stm8s_type.h"
#include "stm8s.h"

/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//#include "stm8s_gpio.h"
//#include ""

/* Defines -------------------------------------------------------------------*/
//#define F_CPU 16000000

/**
  * @brief UART3 Word length possible values
  */
typedef enum
{
  UART3_WORDLENGTH_8D = (uint8_t)0x00,/**< 0x00 8 bits Data  */
  UART3_WORDLENGTH_9D = (uint8_t)0x10 /**< 0x10 9 bits Data  */
} UART3_WordLength_TypeDef;

/**
 * @brief UART3 stop bits possible values
 */

typedef enum
{
  UART3_STOPBITS_1   = (uint8_t)0x00,    /**< One stop bit is  transmitted at the end of frame*/
//  UART3_STOPBITS_0_5 = (uint8_t)0x10,    /**< Half stop bits is transmitted at the end of frame*/
  UART3_STOPBITS_2   = (uint8_t)0x20    /**< Two stop bits are  transmitted at the end of frame*/
                       //UART3_STOPBITS_1_5 = (uint8_t)0x30     /**< One and half stop bits*/
} UART3_StopBits_TypeDef;

/**
  * @brief UART3 parity possible values
  */
typedef enum
{
  UART3_PARITY_NO     = (uint8_t)0x00,      /**< No Parity*/


  /*Even Parity -> enable M-bit and parity control*/
  UART3_PARITY_EVEN   = (UART3_CR1_M | UART3_CR1_PCEN) ,

  /*ODD Parity -> enable M-bit, parity control, and parity selection*/
  UART3_PARITY_ODD    = (UART3_CR1_M | UART3_CR1_PCEN | UART3_CR1_PS)
} UART3_Parity_TypeDef;

/**
  * @brief UART3 Synchrone modes
  */
typedef enum
{
  UART3_SYNCMODE_CLOCK_DISABLE    = (uint8_t)0x80, /**< 0x80 Sync mode Disable, SLK pin Disable */
  UART3_SYNCMODE_CLOCK_ENABLE     = (uint8_t)0x08, /**< 0x08 Sync mode Enable, SLK pin Enable     */
  UART3_SYNCMODE_CPOL_LOW         = (uint8_t)0x40, /**< 0x40 Steady low value on SCLK pin outside transmission window */
  UART3_SYNCMODE_CPOL_HIGH        = (uint8_t)0x04, /**< 0x04 Steady high value on SCLK pin outside transmission window */
  UART3_SYNCMODE_CPHA_MIDDLE      = (uint8_t)0x20, /**< 0x20 SCLK clock line activated in middle of data bit     */
  UART3_SYNCMODE_CPHA_BEGINING    = (uint8_t)0x02, /**< 0x02 SCLK clock line activated at beginning of data bit  */
  UART3_SYNCMODE_LASTBIT_DISABLE  = (uint8_t)0x10, /**< 0x10 The clock pulse of the last data bit is not output to the SCLK pin */
  UART3_SYNCMODE_LASTBIT_ENABLE   = (uint8_t)0x01  /**< 0x01 The clock pulse of the last data bit is output to the SCLK pin */
} UART3_SyncMode_TypeDef;


/**
  * @brief UART3 Mode possible values
  */
typedef enum
{
  UART3_MODE_RX_ENABLE     = (uint8_t)0x08,  /**< 0x08 Receive Enable                     */
  UART3_MODE_TX_ENABLE     = (uint8_t)0x04,  /**< 0x04 Transmit Enable                    */
  UART3_MODE_TX_DISABLE    = (uint8_t)0x80,  /**< 0x80 Transmit Disable                   */
  UART3_MODE_RX_DISABLE    = (uint8_t)0x40,  /**< 0x40 Single-wire Half-duplex mode       */
  UART3_MODE_TXRX_ENABLE   = (uint8_t)0x0C  /**< 0x0C Transmit Enable and Receive Enable */
} UART3_Mode_TypeDef;



typedef struct
{
  uint32_t  ulBaudRate;
  uint8_t   ucBBR1;
  uint8_t   ucBBR2;
  uint16_t  usTprescaler;
  uint32_t  uiClkCycles_3_5bit;
  UART3_Parity_TypeDef   eParity;
  UART3_StopBits_TypeDef eStopBit;

} UART_Setup_t;

typedef struct
{

  UART_Setup_t uart;
  uint8_t ucBaudRateIdx;
  uint8_t ucParityIdx;
  uint8_t ucSlaveID;
  uint8_t ucTermination;
  uint8_t ucAESenabled;
  uint8_t *ucpAES_key;
  uint8_t ucUnlock; //default 0 = no writing allowed serial no register 
  //uint32_t  ulBaudRate;
  //uint8_t   ucRS485_BBR1;
  //uint8_t   ucRS485_BBR2;
  //uint16_t  usTprescaler;
  //uint32_t  uiClkCycles_3_5bit;
  //uint32_t  uiClkCycles_3_5bitParity;
} MB_RS485module_t;



/* external functions prototypes ---------------------------------------------*/
void RS485_Init(MB_RS485module_t *pRS485module);
//void RS485_Init(uint32_t BaudRate,
//                UART3_WordLength_TypeDef WordLength,
//                UART3_StopBits_TypeDef StopBits,
//                UART3_Parity_TypeDef Parity,
//                UART3_SyncMode_TypeDef SyncMode,
//                UART3_Mode_TypeDef Mode);


void RS485_ReceiverEnable(bool xRxEnable);
void RS485_ReadByte8(uint8_t *pucByte);
bool RS485_WriteByte(uint8_t ucData);
//void RS485_SymbolTimerInit(uint32_t ulBaudRate, UART3_Parity_TypeDef eParity, UART3_StopBits_TypeDef eStopBit);

void RS485_SymbolTimerInit(MB_RS485module_t *pRS485module);

void RS485_SymbolTimerEnable(void);
void RS485_SymbolTimerDisable(void);
void RS485_TranceiverRxState(FunctionalState eState);
void RS485_TranceiverTxState(FunctionalState eState);

@far @interrupt void UART3_RX_IRQHandler(void);
@far @interrupt void UART3_TX_IRQHandler(void);


#endif // RS485_H
