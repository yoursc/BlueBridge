#include "stm32f10x_it.h"

extern uint32_t msTimer;

void SysTick_Handler(void){
	msTimer--;
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
