/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO(R)
**                STMicroelectronics STM32F4xx Standard Peripherals Library
**
**  Distribution: The file is distributed “as is,” without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. Distribution of this file (unmodified or modified) is not
**  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
**  rights to distribute the assembled, compiled & linked contents of this
**  file as part of an application binary file, provided that it is built
**  using the Atollic TrueSTUDIO(R) toolchain.
**
**
*****************************************************************************
*/

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */
void GPIO_Config();

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{
  int i = 0;
  unsigned int ledState=0x1000;
  unsigned int portState;
  /**
  *  IMPORTANT NOTE!
  *  The symbol VECT_TAB_SRAM needs to be defined when building the project
  *  if code has been located to RAM and interrupts are used.
  *  Otherwise the interrupt table located in flash will be used.
  *  See also the <system_*.c> file and how the SystemInit() function updates
  *  SCB->VTOR register.
  *  E.g.  SCB->VTOR = 0x20000000;
  */

  GPIO_Config();

  GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
  /* Infinite loop */
  while (1)
  {
	if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)) {
		portState=GPIO_ReadOutputData(GPIOD);
		portState&=0x0FFF;
		GPIO_Write(GPIOD, portState | ledState);
		ledState=ledState<<1;
		if (ledState>0x8000)
			ledState=0x1000;
		for(i=0; i<200000; i++) __NOP();
	}
  }
}

void GPIO_Config() {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//LED 1,2,3,4
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType	= GPIO_OType_PP;

	GPIO_Init(GPIOD, &GPIO_InitStructure);

	//button USER
	GPIO_InitStructure.GPIO_Pin		= GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
