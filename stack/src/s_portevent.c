/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/stack/src/s_portevent.c $
  $DateTime: 2023/04/03 10:32:06 $
  $Revision: #1 $
  $Author: llu $
*******************************************************************************/

/* Modbus includes -----------------------------------------------------------*/


/* Includes ------------------------------------------------------------------*/
//#include "stm8s_type.h"
#include "s_portevent.h"

/* Variables -----------------------------------------------------------------*/
static eMBEventType m_eQueuedEvent;
static bool     m_xEventInQueue;

/*******************************************************************************
 * @brief Initialize m_eQueuedEvent
 * @param None
 * @param None
*******************************************************************************/
bool xMBPortEventInit(void)
{
  m_xEventInQueue = FALSE;
  return TRUE;
}

/*******************************************************************************
 * @brief Post an event to m_eQueuedEvent
 * @param eEvent
 * @param None
*******************************************************************************/
bool xMBPortEventPost(eMBEventType eEvent)
{
  m_xEventInQueue = TRUE;
  m_eQueuedEvent = eEvent;
  return TRUE;
}

/*******************************************************************************
 * @brief Get an event from m_eQueuedEvent
 * @param *eEvent
 * @param None
*******************************************************************************/
bool xMBPortEventGet(eMBEventType *eEvent)
{
  bool xEventHappened = FALSE;

  if(m_xEventInQueue)
  {
    *eEvent = m_eQueuedEvent;
    m_xEventInQueue = FALSE;
    xEventHappened = TRUE;
  }
  return xEventHappened;
}
