/*
 * FreeModbus Libary: A portable Modbus implementation for Modbus ASCII/RTU.
 * Copyright (c) 2006 Christian Walter <wolti@sil.at>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * File: $Id: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/rtu/inc/s_mbrtu.h#1 $
 */

#ifndef _MB_RTU_H
#define _MB_RTU_H

#define MB_SER_PDU_SIZE_MIN     4       /* Minimum size of a Modbus RTU frame. */
#define MB_SER_PDU_SIZE_MAX     62      /* Maximum size of a Modbus RTU frame. */
#define MB_SER_PDU_SIZE_CRC     2       /* Size of CRC field in PDU. */
#define MB_SER_PDU_ADDR_OFF     0       /* Offset of slave address in Ser-PDU. */
#define MB_SER_PDU_PDU_OFF      1       /* Offset of Modbus-PDU in Ser-PDU. */
#define MB_MAX_HOLDINGs_TO_READ 25      /* Maximux numbers of holding regs to read*/

#include "s_mb.h"

eMBErrorCode eMBRTUInit(MB_RS485module_t *pRS485module);

void            eMBRTUStart(void);
void            eMBRTUStop(void);
eMBErrorCode    eMBRTUReceive(uint8_t * pucRcvAddress, uint8_t ** pucFrame, uint16_t * pusLength);
eMBErrorCode    eMBRTUSend(uint8_t slaveAddress, const uint8_t * pucFrame, uint16_t usLength);
bool            MBRTU_Receive_IT(void);
bool            xMBRTUTransmit_IT(void);
bool            xMBRTUTimerT15Expired(void);
bool            xMBRTUTimerT35Expired_IT(void);

#endif
