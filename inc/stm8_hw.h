/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/inc/stm8_hw.h $
  $DateTime: 2024/04/30 10:47:54 $
  $Revision: #2 $
  $Author: llu $
*******************************************************************************/

#ifndef _stm8_hw_h
#define _stm8_hw_h

#include "stm8s.h"
#include "stm8s_iwdg.h"
#include "stm8s_gpio.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/


/* Exported macro ------------------------------------------------------------*/
#define USE_WATCHDOG 0

#if USE_WATCHDOG > 0
  #define WATCHDOG {IWDG_ReloadCounter();}
#else
  #define WATCHDOG {nop();}
#endif

/*Modbus ID pins ********************************/
#define PORT_IDx GPIOF
#define PIN_ID0 GPIO_PIN_4
#define PIN_ID1 GPIO_PIN_5
#define PIN_ID2 GPIO_PIN_6
#define PIN_ID3 GPIO_PIN_7

/* RS485 ****************************************/
#define PORT_RS485_TX_ENABLE GPIOD            //  DE -> Input Driver enable, active high
#define PIN_RS485_TX_ENABLE  GPIO_PIN_3

#define PORT_RS485_RX_DISABLE   GPIOD         // /RE -> Receiver enable, active low
#define PIN_RS485_RX_DISABLE    GPIO_PIN_4

/* Hoist Inputs*********************************/
#define PORT_HOIST GPIOB           
#define PIN_HOIST_IN0  GPIO_PIN_0
#define PIN_HOIST_IN1  GPIO_PIN_1
#define PIN_HOIST_IN2  GPIO_PIN_2
#define PIN_HOIST_IN3  GPIO_PIN_3
#define PIN_HOIST_IN4  GPIO_PIN_4
#define PIN_HOIST_IN5  GPIO_PIN_5
#define PIN_HOIST_IN6  GPIO_PIN_6
#define PIN_HOIST_IN7  GPIO_PIN_7

/* LED tower outputs ***************************/
#define PORT_LED_TOWER GPIOG           
#define PIN_LED_TOWER_RED    GPIO_PIN_0
#define PIN_LED_TOWER_YELLOW GPIO_PIN_1
#define PIN_LED_TOWER_GREEN  GPIO_PIN_2
#define PIN_LED_TOWER_BLUE   GPIO_PIN_3
#define PIN_LED_TOWER_WHITE  GPIO_PIN_4
#define PIN_LED_TOWER_BUZZ   GPIO_PIN_5
#define PIN_LED_TOWER_NC1    GPIO_PIN_6
#define PIN_LED_TOWER_NC2    GPIO_PIN_7

/* Power enables *******************************/
#define PORT_ENA_RELAY1 GPIOA           
#define PIN_ENA_RELAY1  GPIO_PIN_1

#define PORT_ENA_RELAY2 GPIOA           
#define PIN_ENA_RELAY2  GPIO_PIN_2

#define PORT_ENA_24V_S1 GPIOD           
#define PIN_ENA_24V_S1  GPIO_PIN_7

#define PORT_ENA_5V_S1  GPIOE           
#define PIN_ENA_5V_S1   GPIO_PIN_6

#define PORT_ENA_LIGHT GPIOE           
#define PIN_ENA_LIGHT  GPIO_PIN_7



/* Debug pin ************************************/

#define PORT_LED1 GPIOF
#define PIN_LED1  GPIO_PIN_3

#define PORT_LED2 GPIOF
#define PIN_LED2  GPIO_PIN_0


/* Exported functions ------------------------------------------------------- */
void initHW(void);
void ena_24V_S1(FunctionalState state);





#endif
