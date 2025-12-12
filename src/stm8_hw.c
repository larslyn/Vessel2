/*******************************************************************************
  $File: stm8_hw.c $
  $DateTime: 2025/10/13 10:32:06 $
  $Revision: $
  $Author: $
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
//#include "stm8s_type.h"
#include "stm8_hw.h"
#include "stm8s_gpio.h"
#include "stm8s_exti.h"
/* Defines -------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void initHW(void)
{
  /*Modbus ID pins ********************************/
  /*Input ID0 -- Port D0 (STM8S207Cx pin 41) */
  GPIO_Init(PORT_IDx, PIN_ID0, GPIO_MODE_IN_PU_NO_IT);
  
  /*Input ID1 -- Port D2 (STM8S105 pin 43) */
  GPIO_Init(PORT_IDx, PIN_ID1, GPIO_MODE_IN_PU_NO_IT);
  
  /*Input ID2 -- Port D3 (STM8S105 pin 44) */
  GPIO_Init(PORT_IDx, PIN_ID2, GPIO_MODE_IN_PU_NO_IT);
 
  /*Input ID3 -- Port D4 (STM8S105 pin 45) */
  GPIO_Init(PORT_IDx, PIN_ID3, GPIO_MODE_IN_PU_NO_IT);

  
  /* RS485 ****************************************/
  /*RS485 TX driver enable -- Port PD3 (STM8S207Rx pin 60) (SN65hvd3082 pin 3 -> DE)*/
  GPIO_Init(PORT_RS485_TX_ENABLE, PIN_RS485_TX_ENABLE, GPIO_MODE_OUT_PP_LOW_FAST);

  /*RS485 RX driver disable -- Port PD4 (STM8S207Rx pin 61) (SN65hvd3082 pin 2 -> /RE)*/
  GPIO_Init(PORT_RS485_RX_DISABLE, PIN_RS485_RX_DISABLE, GPIO_MODE_OUT_PP_HIGH_FAST);

  /*RS485 TX -- Port PD5 (STM8S207Rx pin 62) */
  GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);

  
  /* Power enables *********************************/
  /*ENA_24V_S1 -- Port PD7 (STM8S207Rx pin 64) */
  GPIO_Init(PORT_ENA_24V_S1, PIN_ENA_RELAY1, GPIO_MODE_OUT_PP_LOW_FAST);


  /* Led Tower *************************************/
  GPIO_Init(PORT_LED_TOWER, PIN_LED_TOWER_RED,    GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(PORT_LED_TOWER, PIN_LED_TOWER_YELLOW, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(PORT_LED_TOWER, PIN_LED_TOWER_GREEN,  GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(PORT_LED_TOWER, PIN_LED_TOWER_BLUE,   GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(PORT_LED_TOWER, PIN_LED_TOWER_WHITE,  GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(PORT_LED_TOWER, PIN_LED_TOWER_BUZZ,   GPIO_MODE_OUT_PP_LOW_FAST);

  /*input Tacho1 -- Port PB6 (STM8S207Cx pin 16) */
  //GPIO_Init(PORT_SENSOR_CHA,  PIN_SENSOR_CHA, GPIO_MODE_IN_PU_IT);    //Input pull-up
  
  /*input Tacho2 -- Port PB7 (STM8S207Cx pin 15) */
  //GPIO_Init(PORT_SENSOR_CHB,  PIN_SENSOR_CHB, GPIO_MODE_IN_PU_NO_IT);    //Input pull-up, external interrupt

  /* Initialize the Interrupt sensitivity */
	//EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOB, EXTI_SENSITIVITY_RISE_ONLY);



  /*Motor Control ***************************************************/
  /*output PIN_M_PWM -- Port D2 (STM8S105 pin 27) */
  //GPIO_Init(PORT_M_CTRL, PIN_M_PWM, GPIO_MODE_OUT_PP_LOW_FAST);
  /*output PIN_M_PWM -- Port D3 (STM8S105 pin 28) */
  //GPIO_Init(PORT_M_CTRL, PIN_M_DIR, GPIO_MODE_OUT_PP_LOW_FAST);
  /*output PIN_M_PWM -- Port D4 (STM8S105 pin 29) */
  //GPIO_Init(PORT_M_CTRL, PIN_M_ENA, GPIO_MODE_OUT_PP_LOW_FAST);

  /*Motor Control ** STM8S207Cx *************************************/
  
  /*output M_PWR_ENA -- Port PB2 (STM8S207Cx pin 20) */
  //GPIO_Init(PORT_M_PWR_ENA, PIN_M_PWR_ENA, GPIO_MODE_OUT_PP_LOW_FAST);  
  
  /*output PIN_M_IN1 -- Port PC1 (STM8S207Cx pin 26) */
  //GPIO_Init(PORT_M_CTRL, PIN_M_IN1, GPIO_MODE_OUT_PP_LOW_FAST);
  
  /*output PIN_M_IN1 -- Port PC2 (STM8S207Cx pin 27) */
  //GPIO_Init(PORT_M_CTRL, PIN_M_IN2, GPIO_MODE_OUT_PP_LOW_FAST);
  
  /*output PIN_M_IN1 -- Port PC3 (STM8S207Cx pin 28) */
  //GPIO_Init(PORT_M_CTRL, PIN_M_INH1, GPIO_MODE_OUT_PP_LOW_FAST);
  
  /*output PIN_M_IN1 -- Port PC4 (STM8S207Cx pin 29) */
  //GPIO_Init(PORT_M_CTRL, PIN_M_INH2, GPIO_MODE_OUT_PP_LOW_FAST);


  /*Inductive sensors ***********************************************/
  /*Input SENSOR_TOP -- Port PA1 (STM8S207Cx pin 2) */
  //GPIO_Init(PORT_SENSORx, PIN_SENSOR_TOP, GPIO_MODE_IN_PU_NO_IT);
  
  /*Input SENSOR_BOT -- Port PA2 (STM8S207Cx pin 3) */
  //GPIO_Init(PORT_SENSORx, PIN_SENSOR_BOT, GPIO_MODE_IN_FL_NO_IT);


  /*miscellaneous ***************************************************/
  /*Input ALERT -- Port A1 (STM8S105 pin 2) */
  //GPIO_Init(PORT_ALERT, PIN_ALERT, GPIO_MODE_IN_FL_NO_IT);

  /*Input WATER_LEVEL -- Port PB3 (STM8S207Cx pin 19) */
  //GPIO_Init(PORT_WATER_LEVEL, PIN_WATER_LEVEL, GPIO_MODE_IN_FL_NO_IT);

  /*Input TEMPERATURE -- Port PB4 (STM8S207Cx pin 18) */
  //GPIO_Init(PORT_TEMPERATURE, PIN_TEMPERATURE, GPIO_MODE_IN_FL_NO_IT);


  /*Output POWER_ENABLE -- Port PE6 (STM8S207Cx pin 24) */
  //GPIO_Init(PORT_POWER_ENABLE, PIN_POWER_ENABLE, GPIO_MODE_OUT_PP_LOW_FAST);


  /* Debug pin ******************************************************/
  /*output PIN_M_PWM -- Port A2 (STM8S105 pin 3) */
  //GPIO_Init(PORT_TP1, PIN_TP1, GPIO_MODE_OUT_PP_LOW_FAST);

  /*output LED1 -- Port PF3 (STM8S207Cx pin 17) */
  GPIO_Init(PORT_LED1, PIN_LED1, GPIO_MODE_OUT_PP_LOW_FAST);

  /*output LED2 -- Port PF0 (STM8S207Cx pin 22) */
  GPIO_Init(PORT_LED2, PIN_LED2, GPIO_MODE_OUT_PP_LOW_FAST);

}

/*******************************************************************************
 * @brief  Read state of TOP sensor, inverted NPN
 * @param  None
 * @retval state of TopSensor, return set if metal is placed infront of sensor
 ******************************************************************************/
void ena_24V_S1(FunctionalState state)
{
  if(state == ENABLE)
  {
    GPIO_WriteHigh(PORT_ENA_24V_S1, PIN_ENA_RELAY1);
  }
  else
  {
    GPIO_WriteLow(PORT_ENA_24V_S1, PIN_ENA_RELAY1);
  }
}



#if 0

/*******************************************************************************
 * @brief  Read state of TOP sensor, inverted NPN
 * @param  None
 * @retval state of TopSensor, return set if metal is placed infront of sensor
 ******************************************************************************/
BitStatus getTopSensorState(void)
{
  if(RESET == GPIO_ReadInputPin(PORT_SENSORx, PIN_SENSOR_TOP))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

/*******************************************************************************
 * @brief  Read state of TOP sensor, inverted NPN
 * @param  None
 * @retval state of BotSensor, return set if metal is placed infront of sensor
 ******************************************************************************/
BitStatus getBotSensorState(void)
{
  if(RESET == GPIO_ReadInputPin(PORT_SENSORx, PIN_SENSOR_BOT))
  {
    return SET;
  }
  else
  {
    return RESET;
  }
}

#endif