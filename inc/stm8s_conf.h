/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/inc/stm8s_conf.h $
  $DateTime: 2023/04/03 10:32:06 $
  $Revision: #1 $
  $Author: llu $
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM8S_CONF_H
#define __STM8S_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/



#ifdef  USE_FULL_ASSERT
  /**
    * @brief  The assert_param macro is used for function's parameters check.
    * @param expr: If expr is false, it calls assert_failed function
    *   which reports the name of the source file and the source
    *   line number of the call that failed.
    *   If expr is true, it returns no value.
    * @retval : None
    */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((u8 *)__FILE__, __LINE__))
  /* Exported functions ------------------------------------------------------- */
  void assert_failed(u8* file, u32 line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */


#endif /* __STM8S_CONF_H */

