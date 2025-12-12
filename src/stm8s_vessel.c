/*******************************************************************************
  * @file    stm8s_vessel.c
  * @author  Zostera Marina
  * @version V1.0.0
  * @date    11-December-2025
  * @brief   This file contains all the prototypes/macros for the Vessel
 ******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "stm8s_vessel.h"
#include "stm8_hw.h"


/* Private functions ---------------------------------------------------------*/
static void LedTowerPower(FunctionalState pwrOn);
static void LedTowerReset(void);

/* Private variables ---------------------------------------------------------*/
LedTowerState_TypeDef LedState_Red = LED_OFF;
FunctionalState LedBlink_Red = DISABLE;
LedTowerState_TypeDef LedState_Yellow = LED_OFF;
FunctionalState LedBlink_Yellow = DISABLE;
LedTowerState_TypeDef LedState_Green = LED_OFF;
FunctionalState LedBlink_Green = DISABLE;
LedTowerState_TypeDef LedState_Blue = LED_OFF;
FunctionalState LedBlink_Blue = DISABLE;
LedTowerState_TypeDef LedState_White = LED_OFF;
FunctionalState LedBlink_White = DISABLE;
LedTowerState_TypeDef LedState_Buzz = LED_OFF;
FunctionalState LedBlink_Buzz = DISABLE;

/*******************************************************************************
 * @brief Initialize Vessel
 * @param None
 * @return None
*******************************************************************************/
void init_vessel(void)
{
  LedTowerReset();
  LedTowerPower(ENABLE);
}

/*******************************************************************************
 * @brief Initialize Vessel
 * @param None
 * @return None
*******************************************************************************/
void LedTowerReset(void)
{
  GPIO_Write(PORT_LED_TOWER, 0x00);
  LedState_Red = LED_OFF;
  LedBlink_Red = DISABLE;
  LedState_Yellow = LED_OFF;
  LedBlink_Yellow = DISABLE;
  LedState_Green = LED_OFF;
  LedBlink_Green = DISABLE;
  LedState_Blue = LED_OFF;
  LedBlink_Blue = DISABLE;
  LedState_White = LED_OFF;
  LedBlink_White = DISABLE;
  LedState_Buzz = LED_OFF;
  LedBlink_Buzz = DISABLE;
}

/*******************************************************************************
 * @brief LedTowerPower
 * @param state enable = power on
 * @return None
*******************************************************************************/
void LedTowerPower(FunctionalState pwrOn)
{
  if(pwrOn == ENABLE)
  {
    ena_24V_S1(ENABLE);  
  }
  else
  {
    ena_24V_S1(DISABLE);  
  }
}

/*******************************************************************************
 * @brief set_LedTower_color
 * @param Led Color, Led state
 * @return None
*******************************************************************************/
void set_LedTower_color(LedTowerColor_TypeDef color, LedTowerState_TypeDef state)
{
  switch (color)
  {
    /* RED **************************/
    case LED_RED:
    LedState_Red = state;
    if(state == LED_OFF) 
    {
      GPIO_WriteLow(PORT_LED_TOWER, PIN_LED_TOWER_RED);
    }  
    else  
    {
      GPIO_WriteHigh(PORT_LED_TOWER, PIN_LED_TOWER_RED);
    }
    break;
  
    /* YELLOW ***********************/
    case LED_YELLOW:
    LedState_Yellow = state;
    if(state == LED_OFF) 
    {
      GPIO_WriteLow(PORT_LED_TOWER, PIN_LED_TOWER_YELLOW);
    }  
    else  
    {
      GPIO_WriteHigh(PORT_LED_TOWER, PIN_LED_TOWER_YELLOW);
    }
    break;

    /* GREEN ************************/
    case LED_GREEN:
    LedState_Green = state;
    if(state == LED_OFF) 
    {
      GPIO_WriteLow(PORT_LED_TOWER, PIN_LED_TOWER_GREEN);
    }  
    else  
    {
      GPIO_WriteHigh(PORT_LED_TOWER, PIN_LED_TOWER_GREEN);
    }
    break;

    /* BLUE *************************/
    case LED_BLUE:
    LedState_Blue = state;
    if(state == LED_OFF) 
    {
      GPIO_WriteLow(PORT_LED_TOWER, PIN_LED_TOWER_BLUE);
    }  
    else  
    {
      GPIO_WriteHigh(PORT_LED_TOWER, PIN_LED_TOWER_BLUE);
    }
    break;

    /* WHITE ************************/
    case LED_WHITE:
    LedState_White = state;
    if(state == LED_OFF) 
    {
      GPIO_WriteLow(PORT_LED_TOWER, PIN_LED_TOWER_WHITE);
    }  
    else  
    {
      GPIO_WriteHigh(PORT_LED_TOWER, PIN_LED_TOWER_WHITE);
    }
    break;

    /* BUZZ *************************/
    case LED_BUZZ:
    LedState_Buzz = state;
    if(state == LED_OFF) 
    {
      GPIO_WriteLow(PORT_LED_TOWER, PIN_LED_TOWER_BUZZ);
    }  
    else  
    {
      GPIO_WriteHigh(PORT_LED_TOWER, PIN_LED_TOWER_BUZZ);
    }
    break;

    default:
      break;
  }
}

/*******************************************************************************
 * @brief get_LedTower_state
 * @param Color
 * @return State of color
*******************************************************************************/
LedTowerState_TypeDef get_LedTower_color(LedTowerColor_TypeDef color)
{
  return LED_OFF;
}

/*******************************************************************************
 * @brief Interrupt callback function every 50ms
 * @param None
 * @return None
*******************************************************************************/
void IT_TIM1_callback_vessel(void)
{

}




/* Defines -------------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
