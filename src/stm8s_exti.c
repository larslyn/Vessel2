/*******************************************************************************
 $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/src/stm8s_exti.c $
 $DateTime: 2023/04/03 10:32:06 $
 $Revision: #1 $
 $Author: llu $
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8s_exti.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  * @brief Set the external interrupt sensitivity of the selected port.
  * @warning
  * - The modification of external interrupt sensitivity is only possible when the interrupts are disabled.
  * - The normal behavior is to disable the interrupts before calling this function, and re-enable them after.
  * @param[in] Port The port number to access.
  * @param[in] SensitivityValue The external interrupt sensitivity value to set.
  * @retval None
  * @par Required preconditions:
  * Global interrupts must be disabled before calling this function.
  */
void EXTI_SetExtIntSensitivity(EXTI_Port_TypeDef Port, EXTI_Sensitivity_TypeDef SensitivityValue)
{

  /* Check function parameters */
  assert_param(IS_EXTI_PORT_OK(Port));
  assert_param(IS_EXTI_SENSITIVITY_OK(SensitivityValue));

  /* Set external interrupt sensitivity */
  switch(Port)
  {
    case EXTI_PORT_GPIOA:
      EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PAIS);
      EXTI->CR1 |= (uint8_t)(SensitivityValue);
      break;
    case EXTI_PORT_GPIOB:
      EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PBIS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(SensitivityValue) << 2);
      break;
    case EXTI_PORT_GPIOC:
      EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PCIS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(SensitivityValue) << 4);
      break;
    case EXTI_PORT_GPIOD:
      EXTI->CR1 &= (uint8_t)(~EXTI_CR1_PDIS);
      EXTI->CR1 |= (uint8_t)((uint8_t)(SensitivityValue) << 6);
      break;
//  case EXTI_PORT_GPIOE:
//    EXTI->CR2 &= (u8)(~EXTI_CR2_PEIS);
//    EXTI->CR2 |= (u8)(SensitivityValue);
//    break;
    default:
      break;
  }
}

