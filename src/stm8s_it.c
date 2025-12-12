/* Includes ------------------------------------------------------------------*/
#include "stm8s_it.h"
#include "stm8s_tim1.h"
#include "stm8s_gpio.h"
#include "stm8_hw.h"
#include "stm8s_vessel.h"
#include "s_mb.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/


@far @interrupt void TIM1_UPD_OVF_TRG_BRK_IRQHandler(void)
{
  /* In order to detect unexpected events during development,
     it is recommended to set a breakpoint on the following instruction.
  */
  /* Cleat Interrupt Pending bit */
  TIM1_ClearITPendingBit(TIM1_IT_UPDATE);
  IT_TIM1_callback_vessel();
  GPIO_WriteReverse(PORT_LED2, PIN_LED2);

  //IT_TIM1_Callback_motor();

}



