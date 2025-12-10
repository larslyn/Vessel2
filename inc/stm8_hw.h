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

/* TACHO Sensor *********************************/
//#define PORT_SENSOR_CHA GPIOB           //Tacho 1
//#define PIN_SENSOR_CHA  GPIO_PIN_6

//#define PORT_SENSOR_CHB GPIOB           //Tacho 2
//#define PIN_SENSOR_CHB  GPIO_PIN_7

/*Motor Control ********************************/
//#define PORT_M_CTRL GPIOD              
//#define PIN_M_PWM   GPIO_PIN_2
//#define PIN_M_DIR   GPIO_PIN_3
//#define PIN_M_ENA   GPIO_PIN_4

/*Motor Control *** STM8S207 *******************/
//#define PORT_M_PWR_ENA GPIOB
//#define PIN_M_PWR_ENA GPIO_PIN_2

//#define PORT_M_CTRL GPIOC
//#define PIN_M_IN1  GPIO_PIN_1
//#define PIN_M_IN2  GPIO_PIN_2
//#define PIN_M_INH1 GPIO_PIN_3
//#define PIN_M_INH2 GPIO_PIN_4


/*Inductive sensors *****************************/
//#define PORT_SENSORx    GPIOA
//#define PIN_SENSOR_TOP  GPIO_PIN_1
//#define PIN_SENSOR_BOT  GPIO_PIN_2
//#define PIN_SENSOR_BAG  GPIO_PIN_2

/*miscellaneous *********************************/
//#define PORT_ALERT GPIOA
//#define PIN_ALERT  GPIO_PIN_1

//#define PORT_WATER_LEVEL GPIOB
//#define PIN_WATER_LEVEL  GPIO_PIN_3

//#define PORT_TEMPERATURE GPIOB
//#define PIN_TEMPERATURE  GPIO_PIN_4


//#define PORT_POWER_ENABLE GPIOE
//#define PIN_POWER_ENABLE  GPIO_PIN_6

/* Debug pin ************************************/
//#define PORT_TP1 GPIOA
//#define PIN_TP1  GPIO_PIN_2

#define PORT_LED1 GPIOF
#define PIN_LED1  GPIO_PIN_3

#define PORT_LED2 GPIOF
#define PIN_LED2  GPIO_PIN_0


/* Exported functions ------------------------------------------------------- */
void initHW(void);
//BitStatus getTopSensorState(void);
//BitStatus getBotSensorState(void);




#endif
