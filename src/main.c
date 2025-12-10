/*******************************************************************************
  $File: $
  $DateTime: $
  $Revision: $
  $Author: Lars $
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "eeprom.h"

#include "stm8s_rs485.h"

#include "s_mb.h"

#include "stm8_hw.h"
#include "s_od.h"

#include "stm8s_adc2.h"
//#include "stm8s_i2c.h"
#include "stm8s_tim1.h"



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void initIWDG_64ms(void);
static void TIM1_Config(void);
static uint8_t GetHwIdPinsAdrs(void);
//static void TIM2_Config(void);
//static void I2C_Config(void);
//extern MB_t *MB;

#define I2C_TEST 0


/*******************************************************************************
 * Main Loop
*******************************************************************************/
void main(void)
{
  uint8_t ucBaudRateIdx;
  uint8_t ucParityIdx;
  uint8_t ucSlaveId;
  uint8_t ucTermination;

  uint16_t usADCvalue = 0;
  uint16_t usi;
  uint32_t ul_dbgCnt = 0;

  #if I2C_TEST > 0
  float    BusVoltage = 0; 
#endif

  nop(); //do absolutely nothing
  
  initHW();  //setup hardware GPIOs
  
  SW_VERSION = 0x0100;  

  for(ucSlaveId=0; ucSlaveId < 0xf0; ucSlaveId++)
  {
    for(ucParityIdx=0; ucParityIdx < 0xA0; ucParityIdx++)
    {
      nop(); //do absolutely nothing
    }
  }


  /* Clear High speed internal clock prescaler */
  /* CPUDIV[2:0] and HSIDIV[1:0] cleared => 16Mhz */
  CLK->CKDIVR &= (uint8_t)(~CLK_CKDIVR_HSIDIV); //set internal clock to 16Mhz
  
  EE_init();        //initialize Eeprom

  //read SlaveID from eeprom
  EE_ReadByte(RS485_SPEED_ADRS,  &ucBaudRateIdx);
  EE_ReadByte(RS485_PARITY_ADRS, &ucParityIdx);
  //EE_ReadByte(RS485_ID_ADRS,     &ucSlaveId);
  EE_ReadByte(RS485_TERM_ADRS,   &ucTermination);

  //ucSlaveId = (uint8_t)(0x0A + GetHwIdPinsAdrs());
  ucSlaveId = 20;

#if 0
  //initialize ADC1
  /* De-Init ADC peripheral*/
  ADC2_DeInit();

  /* Init ADC2 peripheral */
  ADC2_Init(ADC2_CONVERSIONMODE_SINGLE,   //conversion mode
            ADC2_CHANNEL_3,               //channel to convert
            ADC2_PRESSEL_FCPU_D18,        //ADC1 prescaler
            ADC2_EXTTRIG_TIM,             //external trigger
            DISABLE,                      //external trigger new state
            ADC2_ALIGN_RIGHT,             //converted data alignment
            ADC2_SCHMITTTRIG_CHANNEL9,    //schmitt trigger channel
            DISABLE);                     //schmitt trigger state

  for(usi=0; usi<1000; usi++)
  {
    nop();
  }
#endif
  //ADC2_StartConversion();
  //turn ON/OFF bus termination
  
  TIM1_Config();        //Interrupt every 50ms 
  //I2C_Config();         //Initialize I2C, also set altenate function pins to I2C 
  //INA226_Init();        //set calibration register in INA226
  //MotorBox_Init(ucSlaveId);
  //Tacho_Init();



//  GPIO_WriteHigh(PORT_POWER_ENABLE, PIN_POWER_ENABLE);
//  GPIO_WriteHigh(PORT_LED1,PIN_LED1);
  GPIO_WriteHigh(PORT_LED2,PIN_LED2);


  //eMBInit(1, 2, 1, 0); //Baud = 19200, parity = Even, stopbit = 1
  //eMBInit(ucSlaveId, ucBaudRateIdx, ucParityIdx, UART2_STOPBITS_1);
  eMBInit(ucSlaveId, 3, ucParityIdx, UART3_STOPBITS_1);
  //eMBInit(12, ucBaudRateIdx, ucParityIdx, UART2_STOPBITS_1);

  /* Enable the Modbus Protocol Stack. */
  eMBEnable();

#if USE_WATCHDOG > 0
  initIWDG_64ms();
#endif
 
  //TIM2_SetCompare1(2000);

  //MainLoop - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  while(1)
  {
    /*reset watchdog*/
    WATCHDOG;
    
    /* Call the main polling loop of the Modbus protocol stack. */
    eMBPoll();
		//WATCHDOG;
    //motorBoxPoll();
   
  }
}

/*******************************************************************************
 * @brief  Initialize independant watchdog timer to 64ms
 * @param  None
 * @retval None
 ******************************************************************************/
static void initIWDG_64ms(void)
{
  // enable and start the wdog counter at first!
  IWDG_Enable();  //IWDG->KR = 0xCC

  // unlock wdog configuration registers
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //IWDG->KR = 0x55

  //Set maximum WDT timeout to 64ms
  IWDG_SetPrescaler(IWDG_Prescaler_16);   //IWDG->PR
  IWDG_SetReload(0xFF);                   //IWDG->RLR

  //lock wdog registers & reload the wdog counter
  IWDG_WriteAccessCmd(IWDG_KEY_REFRESH);  //IWDG->KR= 0xAA;
}


/*******************************************************************************
 * @brief  Initialize Timer 1.  Ticktimer every 50ms
 *         Timer is setup in main.c  
 * @param  None
 * @retval None
 ******************************************************************************/
static void TIM1_Config(void)
{
  /* TIM1 Peripheral Configuration */ 
  TIM1_DeInit();

  /* set interrupt every 50ms ((1/16000000) * 64 * (12499+1) = 0.050 sec. */ 
  /* Time Base configuration */ 
  TIM1_TimeBaseInit(64,                  //Prescaler value
                    TIM1_COUNTERMODE_UP,  //counter mode
                    12499,                //Period value
                    0);                   //Repetition counter value

  

  TIM1_CCPreloadControl(ENABLE);
  TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);  //enable Update Interrupt Enable

  /* TIM1 counter enable - set CR1.bit0 - page 188*/
  TIM1_Cmd(ENABLE);   
}

/*******************************************************************************
 * @brief  Get hardware ID modbus adrs pins 
 * @param  None
 * @retval the pins a translated to a value. No jumbers equals 0 
 ******************************************************************************/
uint8_t GetHwIdPinsAdrs(void)
{
  uint8_t tmp;

  //read port and mask out (pin PC5...PC2 => 0011.1100b)
  tmp = GPIO_ReadInputData(PORT_IDx);
	tmp ^= 0x3C;
	
  tmp = (uint8_t)((tmp >> 2) & 0x0F);

  return tmp;
}



#if 0
/*******************************************************************************
 * @brief  Initialize Timer 2
 * @param  None
 * @retval None
 ******************************************************************************/
static void TIM2_Config(void)
{
  /* TIM1 Peripheral Configuration */ 
  TIM2_DeInit();
  
  /* Time Base configuration */ 
  TIM2_TimeBaseInit(TIM2_PRESCALER_1, 16000);
  TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 0, TIM2_OCPOLARITY_LOW);
  TIM2_Cmd(ENABLE);   
}
#endif