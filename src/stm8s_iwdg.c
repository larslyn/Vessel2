/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/src/stm8s_iwdg.c $
  $DateTime: 2023/04/03 10:32:06 $
  $Revision: #1 $
  $Author: llu $
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8s_iwdg.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/** @addtogroup IWDG_Public_Functions
  * @{
  */

/**
  * @brief Enables or disables write access to Prescaler and Reload registers.
  *
  * @par Full description:
  *  IWDG_WriteAccess: new state of write access to Prescaler and Reload registers.
  *  This parameter can be one of the following values:
  *  - IWDG_WriteAccess_Enable: Enable write access to
	* Prescaler and Reload registers
  * - IWDG_WriteAccess_Disable: Disable write access to
  * Prescaler and Reload registers
  * @param[in] IWDG_WriteAccess enable or disable the write access.
  * @retval None
  */
void IWDG_WriteAccessCmd(IWDG_WriteAccess_TypeDef IWDG_WriteAccess)
{

  /* Check the parameters */
  assert_param(IS_IWDG_WRITEACCESS_MODE_OK(IWDG_WriteAccess));

  IWDG->KR = (uint8_t)IWDG_WriteAccess; /* Write Access */

}

/**
  * @brief Sets IWDG Prescaler value.
  * @par Full description:
  * IWDG_Prescaler: specifies the IWDG Prescaler value.
  * This parameter can be one of the following values:
  *  - IWDG_Prescaler_4: IWDG prescaler set to 4
  *  - IWDG_Prescaler_8: IWDG prescaler set to 8
  *  - IWDG_Prescaler_16: IWDG prescaler set to 16
  *  - IWDG_Prescaler_32: IWDG prescaler set to 32
  *  - IWDG_Prescaler_64: IWDG prescaler set to 64
  *  - IWDG_Prescaler_128: IWDG prescaler set to 128
  *  - IWDG_Prescaler_256: IWDG prescaler set to 256
  * @param[in] IWDG_Prescaler set the value of the prescaler register.
  * @retval None
  * @par Required preconditions:
  * Write access enabled
  */
void IWDG_SetPrescaler(IWDG_Prescaler_TypeDef IWDG_Prescaler)
{
  /* Check the parameters */
  assert_param(IS_IWDG_PRESCALER_OK(IWDG_Prescaler));

  IWDG->PR = (uint8_t)IWDG_Prescaler;
}

/**
  * @brief Sets IWDG Reload value.
  * @param[in] IWDG_Reload Specifies the IWDG Reload value (from 0x00 to 0xFF)
  * @retval None
  * @par Required preconditions:
  * Write access enabled
  */
void IWDG_SetReload(uint8_t IWDG_Reload)
{
  IWDG->RLR = IWDG_Reload;
}

/**
  * @brief Reload IWDG counter
  * @par Full description:
  * Reloads IWDG counter with value defined in the reload register
  * (write access to Prescaler and Reload registers disabled).
  * @par Parameters:
  * None
  * @retval None
  * @par Required preconditions:
  * Write access enabled
  */
void IWDG_ReloadCounter(void)
{
  IWDG->KR = IWDG_KEY_REFRESH;
}

/**
  * @brief Enable IWDG registers access.
  * @par Full description:
  * Enables IWDG (write access to Prescaler and Reload registers disabled).
  * @par Parameters:
  * None
  * @retval None
  */
void IWDG_Enable(void)
{
  IWDG->KR = IWDG_KEY_ENABLE;
}

/**
  * @}
  */

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
