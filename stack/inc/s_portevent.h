/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/stack/inc/s_portevent.h $
  $DateTime: 2023/04/03 10:32:06 $
  $Revision: #1 $
  $Author: llu $
*******************************************************************************/

#ifndef _S_PORTEVENT_H
#define _S_PORTEVENT_H

#include "stm8s.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum
{
  EV_READY,                   /*!< Startup finished. */
  EV_FRAME_RECEIVED,          /*!< Frame received. */
  EV_EXECUTE,                 /*!< Execute function. */
  EV_FRAME_SENT               /*!< Frame sent. */
} eMBEventType;

/* Public function prototypes ------------------------------------------------*/
bool xMBPortEventInit(void);
bool xMBPortEventPost(eMBEventType eEvent);
bool xMBPortEventGet(eMBEventType *eEvent);

#endif
