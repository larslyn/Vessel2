/* BASIC INTERRUPT VECTORS TABLE FOR STM8 devices
 * Copyright (c) 2014 STMicroelectronics
 */

/* Includes ------------------------------------------------------------------*/
//#include "encoder.h"
#include "stm8s_rs485.h"
#include "stm8s_it.h"

typedef void @far (*interrupt_handler_t)(void);
 
struct interrupt_vector 
{
  unsigned char interrupt_instruction;
	interrupt_handler_t interrupt_handler;
};
 
@far @interrupt void NonHandledInterrupt (void)
{
	/* in order to detect unexpected events during development, 
	   it is recommended to set a breakpoint on the following instruction
	*/
	return;
}
 
extern void _stext();     /* startup routine */
 
struct interrupt_vector const _vectab[] = 
{
  {0x82, (interrupt_handler_t)_stext}, 						/* RESET */
	{0x82, NonHandledInterrupt}, 		/* TRAP - Software interrupt */
	{0x82, NonHandledInterrupt}, 		/* irq0 - External Top Level interrupt (TLI) */
	{0x82, NonHandledInterrupt}, 		/* irq1 - Auto Wake Up from Halt interrupt */
	{0x82, NonHandledInterrupt}, 		/* irq2 - Clock Controller interrupt */
	{0x82, NonHandledInterrupt}, 	  /* irq3 - External interrupt 0 (GPIOA) */
	{0x82, NonHandledInterrupt}, 	  /* irq4 - External interrupt 0 (GPIOB) */
	{0x82, NonHandledInterrupt}, 	  /* irq5 - External interrupt 2 (GPIOC) */
	{0x82, NonHandledInterrupt}, 	  /* irq6 - External interrupt 3 (GPIOD) */
	{0x82, NonHandledInterrupt}, 	  /* irq7 - External interrupt 4 (GPIOE) */
	{0x82, NonHandledInterrupt}, 		/* irq8 - Reserved */
	{0x82, NonHandledInterrupt}, 		/* irq9 - Reserved */
	{0x82, NonHandledInterrupt}, 		/* irq10 - SPI End of transfer interrupt */
	{0x82, (interrupt_handler_t)TIM1_UPD_OVF_TRG_BRK_IRQHandler}, 	/* irq11 - TIM1 Update/Overflow/Trigger/Break interrupt */
	{0x82, NonHandledInterrupt}, 		/* irq12 - TIM1 Capture/Compare interrupt */
	{0x82, NonHandledInterrupt}, 		/* irq13 - TIM2 Update/Overflow/Break interrupt  */
	{0x82, NonHandledInterrupt}, 		/* irq14 - TIM2 Capture/Compare interrupt */
	{0x82, (interrupt_handler_t)UART3_RX_IRQHandler}, 		/* irq15 - TIM3 Update/Overflow/Break interrupt */
	{0x82, NonHandledInterrupt}, 		/* irq16 - TIM3 Capture/Compare interrupt */
	{0x82, NonHandledInterrupt}, 		/* irq17 - UART1 Tx complete interrupt */
	{0x82, NonHandledInterrupt}, 		/* irq18 - UART1 Rx interrupt */
	{0x82, NonHandledInterrupt}, 	  /* irq19 - I2C interrupt */
	{0x82, (interrupt_handler_t)UART3_TX_IRQHandler}, 		/* irq20 - UART3 Tx interrupt */
	{0x82, (interrupt_handler_t)UART3_RX_IRQHandler}, 		/* irq21 - UART3 Rx interrupt */
	{0x82, NonHandledInterrupt}, 		/* irq22 - ADC2 end of conversion interrupt */
	{0x82, NonHandledInterrupt}, 		/* irq23 - TIM4 Update/Overflow interrupt */
	{0x82, NonHandledInterrupt},  	/* irq24 - FLASH interrupt */
	{0x82, NonHandledInterrupt},		/* irq25 - Reserved */
	{0x82, NonHandledInterrupt}, 		/* irq26 - Reserved */
	{0x82, NonHandledInterrupt}, 		/* irq27 - Reserved */
	{0x82, NonHandledInterrupt}, 		/* irq28 - Reserved */
	{0x82, NonHandledInterrupt} 		/* irq29 - Reserved */
};
 
 /******************* (C) COPYRIGHT 2014 STMicroelectronics *****END OF FILE****/
 