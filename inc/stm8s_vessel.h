/*******************************************************************************
  * @file    stm8s_vessel.h
  * @author  Zostera Marina
  * @version V1.0.0
  * @date    11-December-2025
  * @brief   This file contains all the prototypes/macros for the Vessel
 ******************************************************************************/

 /* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VESSEL_H
#define __VESSEL_H

#include "stm8s.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  LED_OFF   = (uint8_t)0,
  LED_ON    = (uint8_t)1,
  LED_BLINK = (uint8_t)2
}LedTowerState_TypeDef;


typedef enum
{
  LED_RED    = (uint8_t)0,
  LED_YELLOW = (uint8_t)1,
  LED_GREEN  = (uint8_t)2,
  LED_BLUE   = (uint8_t)3,
  LED_WHITE  = (uint8_t)4,
  LED_BUZZ   = (uint8_t)5
}LedTowerColor_TypeDef;

/* Exported functions ------------------------------------------------------- */
void init_vessel(void);
void set_LedTower_color(LedTowerColor_TypeDef color, LedTowerState_TypeDef state);
LedTowerState_TypeDef get_LedTower_color(LedTowerColor_TypeDef color);
void IT_TIM1_callback_vessel(void);





#endif