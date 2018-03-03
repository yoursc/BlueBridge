#include "stm32f10x_it.h"

extern uint32_t msTimer;
extern uint8_t EXTI_Status;

void SysTick_Handler(void){
	msTimer--;
}

void EXTI0_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line0) != RESET){
		EXTI_Status = 1;
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI9_5_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line8) != RESET){
		EXTI_Status = 2;
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
