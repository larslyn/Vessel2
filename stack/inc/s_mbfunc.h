/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/stack/inc/s_mbfunc.h $
  $DateTime: 2023/04/03 10:32:06 $
  $Revision: #1 $
  $Author: llu $
*******************************************************************************/

#ifndef _MB_FUNC_H
#define _MB_FUNC_H

#ifdef __cplusplus
PR_BEGIN_EXTERN_C
#endif

#if MB_FUNC_OTHER_REP_SLAVEID_BUF > 0
eMBException eMBFuncReportSlaveID(uint8_t * pucFrame, uint16_t * usLen);
#endif

#if MB_FUNC_READ_INPUT_ENABLED > 0
eMBException    eMBFuncReadInputRegister_x04(uint8_t * pucFrame, uint16_t * usLen);
#endif

#if MB_FUNC_READ_HOLDING_ENABLED > 0
eMBException    eMBFuncReadHoldingRegister(uint8_t * pucFrame, uint16_t * usLen);
#endif

#if MB_FUNC_WRITE_HOLDING_ENABLED > 0
eMBException    eWriteSingleHoldingReg_x06(uint8_t * pucFrame, uint16_t * usLen);
#endif

#if MB_FUNC_WRITE_MULTIPLE_HOLDING_ENABLED > 0
eMBException    eMBFuncWriteMultipleHoldingRegister(uint8_t * pucFrame, uint16_t * usLen);
#endif

#if MB_FUNC_READ_COILS_ENABLED > 0
eMBException    eMBFuncReadCoils(uint8_t * pucFrame, uint16_t * usLen);
#endif

#if MB_FUNC_WRITE_COIL_ENABLED > 0
eMBException    eMBFuncWriteCoil(uint8_t * pucFrame, uint16_t * usLen);
#endif

#if MB_FUNC_WRITE_MULTIPLE_COILS_ENABLED > 0
eMBException    eMBFuncWriteMultipleCoils(uint8_t * pucFrame, uint16_t * usLen);
#endif

#if MB_FUNC_READ_DISCRETE_INPUTS_ENABLED > 0
eMBException    eMBFuncReadDiscreteInputs(uint8_t * pucFrame, uint16_t * usLen);
#endif

#if MB_FUNC_READWRITE_HOLDING_ENABLED > 0
eMBException    eMBFuncReadWriteMultipleHoldingRegister(uint8_t * pucFrame, uint16_t * usLen);
#endif

#ifdef __cplusplus
PR_END_EXTERN_C
#endif
#endif
