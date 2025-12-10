/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/rtu/inc/s_mbcrc.h $
  $DateTime: 2023/04/03 10:32:06 $
  $Revision: #1 $
  $Author: llu $
*******************************************************************************/

#ifndef _MB_CRC_H
#define _MB_CRC_H

#include "stm8s.h"

//USHORT          usMBCRC16( UCHAR * pucFrame, USHORT usLen );

uint16_t usMBCRC16(uint8_t *pucFrame, uint16_t usLen);

#endif
