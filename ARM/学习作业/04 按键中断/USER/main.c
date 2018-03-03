#include "stm32f10x.h"
#include <stdio.h>
#include "lcd.h"
/*  B1-PA0   B2-PA8   B3-PB1   B4-PB2  */

uint32_t msTimer=0;
uint8_t EXTI_Status = 0;

void LCD_Init(void);
void KEY_IT_Init(void);
void Delay_ms(uint32_t xMs);

int main(void){
	SysTick_Config(SystemCoreClock/1000);
	LCD_Init();
	KEY_IT_Init();

	Delay_ms(500);
	LCD_DisplayStringLine(Line2,"++ Start  Success ++");
	Delay_ms(200);
	LCD_DisplayStringLine(Line4,"++Press any key...++");
	while (1){
//		EXTI_Status=0;
		switch(EXTI_Status)
		{
			case 1:
				LCD_DisplayStringLine(Line7," Button1 pressed...");
				break;
			case 2:
				LCD_DisplayStringLine(Line7," Button2 pressed...");
				break;
		}
		Delay_ms(100);
  }
}

//*******中断初初始化******************
void KEY_IT_Init(void){
	EXTI_InitTypeDef  EXTI_InitStruct;
	GPIO_InitTypeDef  GPIO_InitStruct;
	NVIC_InitTypeDef  NVIC_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	//设置B1
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

	EXTI_InitStruct.EXTI_Line=EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x0F;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x0F;
	NVIC_Init(&NVIC_InitStruct);
	
	//设置B1
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource8);

	EXTI_InitStruct.EXTI_Line=EXTI_Line8;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel=EXTI9_5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0x0F;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0x0F;
	NVIC_Init(&NVIC_InitStruct);
}

//*******LCD屏幕初始化******************
void LCD_Init(void){
	STM3210B_LCD_Init();
	LCD_Clear(Black);
	LCD_SetTextColor(Green);
	LCD_SetBackColor(Black);
	LCD_DisplayStringLine(Line0,"====================");
	LCD_DisplayStringLine(Line1,"====================");
	LCD_DisplayStringLine(Line2,"++                ++");
	LCD_DisplayStringLine(Line3,"++                ++");
	LCD_DisplayStringLine(Line4,"++                ++");
	LCD_DisplayStringLine(Line5,"++                ++");
	LCD_DisplayStringLine(Line6,"++                ++");
	LCD_DisplayStringLine(Line7,"++                ++");
	LCD_DisplayStringLine(Line8,"====================");
	LCD_DisplayStringLine(Line9,"====================");
}

//*******延时函数初始化******************
void Delay_ms(uint32_t xMs){
	msTimer=xMs;
	while(msTimer);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
