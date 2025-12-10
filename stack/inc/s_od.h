/*******************************************************************************
  $File: //depot/sw/projects/oe15_01_LowCost/Modbus/cpr400_RTU_V2/stack/inc/s_od.h $
  $DateTime: 2024/05/28 10:31:02 $
  $Revision: #3 $
  $Author: llu $
*******************************************************************************/
#ifndef _S_OD_H
#define _S_OD_H


//#define OD_NO_OF_READINPUTREGISTERS (13)
//#define OD_NO_OF_WRITEHOLDINGS (11)

#define OD_NO_OF_READINPUTREGISTERS (39)
#define OD_NO_OF_WRITEHOLDINGS (13)
#define OD_FIRST_PWR_SAMPLE_OFFSET (0x11)
#define OD_SAMPLE_HEAD_TAIL (0x1b)

#define OD_FIRST_TACHO_SAMPLE_OFFSET (0x1C)
#define OD_TACHO_HEAD_TAIL (0x26)

typedef struct
{
  uint16_t  usIndex;
  void      *pData;
} OD_InputRegistersEntry_t;


/***** Structure for Input Registers (read only)*******************************/
struct sMB_OD_INPUTREG
{
  /*0x0000 */  uint16_t usCounterCCW_LO;
  /*0x0001 */  uint16_t usCounterCCW_HI;
  /*0x0002 */  uint16_t usCounterCW_LO;
  /*0x0003 */  uint16_t usCounterCW_HI;
  /*0x0004 */  uint16_t usPacketCount;
  /*0x0005 */  uint16_t usRS485_Speed;
  /*0x0006 */  uint16_t usRS485_Parity;
  /*0x0007 */  uint16_t usRS485_SlaveID;
  /*0x0008 */  uint16_t usRS485_Term;
  /*0x0009 */  uint16_t usSW_version;
  /*0x000A */  uint16_t usSerialNo_LO;
  /*0x000B */  uint16_t usSerialNo_HI;
  /*0x000C */  uint16_t usCalibration;

  /*0x000D */  uint16_t usGet_MotorTBD;   
  /*0x000E */  uint16_t usGet_MotorAlive; 
  /*0x000F */  uint16_t usGet_MotorWaterLvl;
  /*0x0010 */  uint16_t usGet_MotorVoltageLvl;
  
  /*0x0011 */  uint16_t usGet_MpwrSample_0;
  /*0x0012 */  uint16_t usGet_MpwrSample_1;
  /*0x0013 */  uint16_t usGet_MpwrSample_2;
  /*0x0014 */  uint16_t usGet_MpwrSample_3;
  /*0x0015 */  uint16_t usGet_MpwrSample_4;
  /*0x0016 */  uint16_t usGet_MpwrSample_5;
  /*0x0017 */  uint16_t usGet_MpwrSample_6;
  /*0x0018 */  uint16_t usGet_MpwrSample_7;
  /*0x0019 */  uint16_t usGet_MpwrSample_8;
  /*0x001a */  uint16_t usGet_MpwrSample_9;
  /*0x001b */  uint16_t usGet_MpwrHeadTail;

  /*0x001c */  uint16_t usGet_TachoSample_0;
  /*0x001d */  uint16_t usGet_TachoSample_1;
  /*0x001e */  uint16_t usGet_TachoSample_2;
  /*0x001f */  uint16_t usGet_TachoSample_3;
  /*0x0020 */  uint16_t usGet_TachoSample_4;
  /*0x0021 */  uint16_t usGet_TachoSample_5;
  /*0x0022 */  uint16_t usGet_TachoSample_6;
  /*0x0023 */  uint16_t usGet_TachoSample_7;
  /*0x0024 */  uint16_t usGet_TachoSample_8;
  /*0x0025 */  uint16_t usGet_TachoSample_9;
  /*0x0026 */  uint16_t usGet_TachoHeadTail;
};

/***** Structure for Write Holdings (write/read) ******************************/
struct sMB_OD_WRITEHOLDINGS
{
  /*0x0000 */  uint16_t usCounterReset;
  /*0x0001 */  uint16_t usRS485_Speed;
  /*0x0002 */  uint16_t usRS485_Parity;
  /*0x0003 */  uint16_t usRS485_SlaveID;
  /*0x0004 */  uint16_t usRS485_Term;
  /*0x0005 */  uint16_t usRS485_Save;
  /*0x0006 */  uint16_t usRS485_Load;
  /*0x0007 */  uint16_t usRS485_Reset;
  /*0x0008 */  uint16_t usSerialNo_LO;
  /*0x0009 */  uint16_t usSerialNo_HI;
  /*0x000A */  uint16_t usCalibration;

  /*0x000B */  uint16_t usSet_MotorMasterParam;
  /*0x000C */  uint16_t usSet_MotorMasterCmd;
};


/***** Declaration of Object Dictionary variables *****************************/
extern struct sMB_OD_INPUTREG MB_OD_InputReg;
extern struct sMB_OD_WRITEHOLDINGS  MB_OD_WrHoldingReg;

#define COUNTER_CCW_LO  MB_OD_InputReg.usCounterCCW_LO
#define COUNTER_CCW_HI  MB_OD_InputReg.usCounterCCW_HI
#define COUNTER_CW_LO   MB_OD_InputReg.usCounterCW_LO
#define COUNTER_CW_HI   MB_OD_InputReg.usCounterCW_HI
#define COUNTER_PACKET  MB_OD_InputReg.usPacketCount

#define SW_VERSION      MB_OD_InputReg.usSW_version

#define MOTOR_ALIVE     MB_OD_InputReg.usGet_MotorAlive
#define MOTOR_WATER_LVL MB_OD_InputReg.usGet_MotorWaterLvl
#define MOTOR_VOLTAGE   MB_OD_InputReg.usGet_MotorVoltageLvl  

#define MOTOR_PWR_SAMPLE_0  MB_OD_InputReg.usGet_MpwrSample_0  
#define MOTOR_PWR_SAMPLE_1  MB_OD_InputReg.usGet_MpwrSample_1  
#define MOTOR_PWR_SAMPLE_2  MB_OD_InputReg.usGet_MpwrSample_2  
#define MOTOR_PWR_SAMPLE_3  MB_OD_InputReg.usGet_MpwrSample_3  
#define MOTOR_PWR_SAMPLE_4  MB_OD_InputReg.usGet_MpwrSample_4  
#define MOTOR_PWR_SAMPLE_5  MB_OD_InputReg.usGet_MpwrSample_5  
#define MOTOR_PWR_SAMPLE_6  MB_OD_InputReg.usGet_MpwrSample_6  
#define MOTOR_PWR_SAMPLE_7  MB_OD_InputReg.usGet_MpwrSample_7  
#define MOTOR_PWR_SAMPLE_8  MB_OD_InputReg.usGet_MpwrSample_8  
#define MOTOR_PWR_SAMPLE_9  MB_OD_InputReg.usGet_MpwrSample_9  
#define MOTOR_PWR_HD_TL     MB_OD_InputReg.usGet_MpwrHeadTail  

#define MOTOR_TACHO_SAMPLE_0  MB_OD_InputReg.usGet_TachoSample_0  
#define MOTOR_TACHO_SAMPLE_1  MB_OD_InputReg.usGet_TachoSample_1  
#define MOTOR_TACHO_SAMPLE_2  MB_OD_InputReg.usGet_TachoSample_2  
#define MOTOR_TACHO_SAMPLE_3  MB_OD_InputReg.usGet_TachoSample_3  
#define MOTOR_TACHO_SAMPLE_4  MB_OD_InputReg.usGet_TachoSample_4  
#define MOTOR_TACHO_SAMPLE_5  MB_OD_InputReg.usGet_TachoSample_5  
#define MOTOR_TACHO_SAMPLE_6  MB_OD_InputReg.usGet_TachoSample_6  
#define MOTOR_TACHO_SAMPLE_7  MB_OD_InputReg.usGet_TachoSample_7  
#define MOTOR_TACHO_SAMPLE_8  MB_OD_InputReg.usGet_TachoSample_8  
#define MOTOR_TACHO_SAMPLE_9  MB_OD_InputReg.usGet_TachoSample_9  
#define MOTOR_TACHO_HD_TL     MB_OD_InputReg.usGet_TachoHeadTail  

#define COUNTER_RESET MB_OD_WrHoldingReg.usCounterReset
#define RS485_SPEED   MB_OD_WrHoldingReg.usRS485_Speed
#define RS485_PARITY  MB_OD_WrHoldingReg.usRS485_Parity
#define RS485_SLAVEID MB_OD_WrHoldingReg.usRS485_SlaveID
#define RS485_TERM    MB_OD_WrHoldingReg.usRS485_Term

#define RS485_LOAD    MB_OD_WrHoldingReg.usRS485_Load
#define RS485_SAVE    MB_OD_WrHoldingReg.usRS485_Save
#define RS485_RESET   MB_OD_WrHoldingReg.usRS485_Reset

#define SERIAL_NO_LO  MB_OD_WrHoldingReg.usSerialNo_LO
#define SERIAL_NO_HI  MB_OD_WrHoldingReg.usSerialNo_HI
#define CALIBRATION   MB_OD_WrHoldingReg.usCalibration

#endif
