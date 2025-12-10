/*******************************************************************************
  $File: $
  $DateTime: $
  $Revision: $
  $Author: Lars $
*******************************************************************************/

//#include "stm8s_type.h"
#include "stm8s.h"
#include "s_od.h"
#include "s_mb.h"


/***** Definition for Input holding variables ***FuncCode 0x04 ****************/
struct sMB_OD_INPUTREG MB_OD_InputReg =
{
  0x0000,     //usCounterCCW_LO       /*0x0000 */
  0x0000,     //usCounterCCW_HI       /*0x0001 */
  0x0000,     //usCounterCW_LO        /*0x0002 */
  0x0000,     //usCounterCW_HI        /*0x0003 */
  0x0000,     //usPacketCount         /*0x0004 */
  0x0000,     //RS485_Speed           /*0x0005 */
  0x0000,     //RS485_Parity          /*0x0006 */
  0x0000,     //RS485_SlaveID         /*0x0007 */
  0x0000,     //RS485_Term            /*0x0008 */
  0x0000,     //Software version      /*0x0009 */
  0x0000,     //usSerialNo_LO         /*0x000A */
  0x0000,     //usSerialNo_HI         /*0x000B */
  0x0000,     //usCalibration         /*0x000C */

  0xbe00,     //usGet_MotorTBD;       /*0x000D */
  0xab00,     //usGet_MotorAlive;     /*0x000E */
  0x0000,     //usGet_MotorWaterLvl   /*0x000F */
  0x0000,     //usGet_MotorVoltageLvl /*0x0010 */
  
  0x0000,     //usGet_MpwrSample_0;   /*0x0011 */ 
  0x0000,     //usGet_MpwrSample_1;   /*0x0012 */ 
  0x0000,     //usGet_MpwrSample_2;   /*0x0013 */ 
  0x0000,     //usGet_MpwrSample_3;   /*0x0014 */ 
  0x0000,     //usGet_MpwrSample_4;   /*0x0015 */ 
  0x0000,     //usGet_MpwrSample_5;   /*0x0016 */ 
  0x0000,     //usGet_MpwrSample_6;   /*0x0017 */ 
  0x0000,     //usGet_MpwrSample_7;   /*0x0018 */ 
  0x0000,     //usGet_MpwrSample_8;   /*0x0019 */ 
  0x0000,     //usGet_MpwrSample_9;   /*0x001a */ 
  0xbeda,      //usGet_MpwrHeadTail;  /*0x001b */ 

  0x0000,     //usGet_TachoSample_0;  /*0x001c */ 
  0x0000,     //usGet_TachoSample_1;  /*0x001d */ 
  0x0000,     //usGet_TachoSample_2;  /*0x001e */ 
  0x0000,     //usGet_TachoSample_3;  /*0x001f */ 
  0x0000,     //usGet_TachoSample_4;  /*0x0020 */ 
  0x0000,     //usGet_TachoSample_5;  /*0x0021 */ 
  0x0000,     //usGet_TachoSample_6;  /*0x0022 */ 
  0x0000,     //usGet_TachoSample_7;  /*0x0023 */ 
  0x0000,     //usGet_TachoSample_8;  /*0x0024 */ 
  0x0000,     //usGet_TachoSample_9;  /*0x0025 */ 
  0xcafe      //usGet_TachoHeadTail;  /*0x0026 */ 
};

/***** Definition for Write holding registers *** FuncCode 0x06 ***************/
struct sMB_OD_WRITEHOLDINGS MB_OD_WrHoldingReg =
{
  0x0000,     //CounterReset
  0x0000,     //RS485_Speed
  0x0000,     //RS485_Parity
  0x0000,     //RS485_SlaveID
  0x0000,     //RS485_Term
  0x0000,     //RS485_Save
  0x0000,     //RS485_Load
  0x0000,     //RS485_Reset
  0xbeef,     //usSerialNo_LO
  0xdead,     //usSerialNo_HI
  0x0000,     //usCalibration

  0x0000,     //usSet_MotorParam
  0x0000      //usSet_MotorState
};

/*******************************************************************************
   OBJECT DICTIONARY
*******************************************************************************/
const OD_InputRegistersEntry_t g_OD_INPUT_REGISTER[OD_NO_OF_READINPUTREGISTERS] =
{
  /*0x0000 */    {0x0000, (void*)&MB_OD_InputReg.usCounterCCW_LO},
  /*0x0001 */    {0x0001, (void*)&MB_OD_InputReg.usCounterCCW_HI},
  /*0x0002 */    {0x0002, (void*)&MB_OD_InputReg.usCounterCW_LO},
  /*0x0003 */    {0x0003, (void*)&MB_OD_InputReg.usCounterCW_HI},
  /*0x0004 */    {0x0004, (void*)&MB_OD_InputReg.usPacketCount},

  /*0x0005 */    {0x0005, (void*)&MB_OD_WrHoldingReg.usRS485_Speed},
  /*0x0006 */    {0x0006, (void*)&MB_OD_WrHoldingReg.usRS485_Parity},
  /*0x0007 */    {0x0007, (void*)&MB_OD_WrHoldingReg.usRS485_SlaveID},
  /*0x0008 */    {0x0008, (void*)&MB_OD_WrHoldingReg.usRS485_Term},

  /*0x0009 */    {0x0009, (void*)&MB_OD_InputReg.usSW_version},

  /*0x000A */    {0x000A, (void*)&MB_OD_WrHoldingReg.usSerialNo_LO},
  /*0x000B */    {0x000B, (void*)&MB_OD_WrHoldingReg.usSerialNo_HI},
  /*0x000C */    {0x000C, (void*)&MB_OD_WrHoldingReg.usCalibration},

  /*0x000D */    {0x000D, (void*)&MB_OD_InputReg.usGet_MotorTBD},
  /*0x000E */    {0x000E, (void*)&MB_OD_InputReg.usGet_MotorAlive},
  /*0x000F */    {0x000F, (void*)&MB_OD_InputReg.usGet_MotorWaterLvl},
  /*0x0010 */    {0x0010, (void*)&MB_OD_InputReg.usGet_MotorVoltageLvl},

  /*0x0011 */    {0x0011, (void*)&MB_OD_InputReg.usGet_MpwrSample_0},
  /*0x0012 */    {0x0012, (void*)&MB_OD_InputReg.usGet_MpwrSample_1},
  /*0x0013 */    {0x0013, (void*)&MB_OD_InputReg.usGet_MpwrSample_2},
  /*0x0014 */    {0x0014, (void*)&MB_OD_InputReg.usGet_MpwrSample_3},
  /*0x0015 */    {0x0015, (void*)&MB_OD_InputReg.usGet_MpwrSample_4},
  /*0x0016 */    {0x0016, (void*)&MB_OD_InputReg.usGet_MpwrSample_5},
  /*0x0017 */    {0x0017, (void*)&MB_OD_InputReg.usGet_MpwrSample_6},
  /*0x0018 */    {0x0018, (void*)&MB_OD_InputReg.usGet_MpwrSample_7},
  /*0x0019 */    {0x0019, (void*)&MB_OD_InputReg.usGet_MpwrSample_8},
  /*0x001a */    {0x001A, (void*)&MB_OD_InputReg.usGet_MpwrSample_9},
  /*0x001b */    {0x001B, (void*)&MB_OD_InputReg.usGet_MpwrHeadTail},

  /*0x0011 */    {0x001C, (void*)&MB_OD_InputReg.usGet_TachoSample_0},
  /*0x0012 */    {0x001D, (void*)&MB_OD_InputReg.usGet_TachoSample_1},
  /*0x0013 */    {0x001E, (void*)&MB_OD_InputReg.usGet_TachoSample_2},
  /*0x0014 */    {0x001F, (void*)&MB_OD_InputReg.usGet_TachoSample_3},
  /*0x0015 */    {0x0020, (void*)&MB_OD_InputReg.usGet_TachoSample_4},
  /*0x0016 */    {0x0021, (void*)&MB_OD_InputReg.usGet_TachoSample_5},
  /*0x0017 */    {0x0022, (void*)&MB_OD_InputReg.usGet_TachoSample_6},
  /*0x0018 */    {0x0023, (void*)&MB_OD_InputReg.usGet_TachoSample_7},
  /*0x0019 */    {0x0024, (void*)&MB_OD_InputReg.usGet_TachoSample_8},
  /*0x001a */    {0x0025, (void*)&MB_OD_InputReg.usGet_TachoSample_9},
  /*0x001b */    {0x0026, (void*)&MB_OD_InputReg.usGet_TachoHeadTail}
};


const OD_InputRegistersEntry_t g_OD_WRITE_HOLDING[OD_NO_OF_WRITEHOLDINGS] =
{
  /*0x0000 */    {0x0000, (void*)&MB_OD_WrHoldingReg.usCounterReset},
  /*0x0001 */    {0x0001, (void*)&MB_OD_WrHoldingReg.usRS485_Speed},
  /*0x0002 */    {0x0002, (void*)&MB_OD_WrHoldingReg.usRS485_Parity},
  /*0x0003 */    {0x0003, (void*)&MB_OD_WrHoldingReg.usRS485_SlaveID},
  /*0x0004 */    {0x0004, (void*)&MB_OD_WrHoldingReg.usRS485_Term},
  /*0x0005 */    {0x0005, (void*)&MB_OD_WrHoldingReg.usRS485_Save},
  /*0x0006 */    {0x0006, (void*)&MB_OD_WrHoldingReg.usRS485_Load},
  /*0x0007 */    {0x0007, (void*)&MB_OD_WrHoldingReg.usRS485_Reset},
  /*0x0008 */    {0x0008, (void*)&MB_OD_WrHoldingReg.usSerialNo_LO},
  /*0x0009 */    {0x0009, (void*)&MB_OD_WrHoldingReg.usSerialNo_HI},
  /*0x000A */    {0x000A, (void*)&MB_OD_WrHoldingReg.usCalibration},

  /*0x000B */    {0x000B, (void*)&MB_OD_WrHoldingReg.usSet_MotorMasterParam},
  /*0x000C */    {0x000C, (void*)&MB_OD_WrHoldingReg.usSet_MotorMasterCmd}
};









