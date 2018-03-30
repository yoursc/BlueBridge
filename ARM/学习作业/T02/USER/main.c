#include "stm32f10x.h"
#include <stdio.h>
#include "led.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"

uint32_t msTimer;

/***************主函数区***************/

int main(void)
{
	SysTick_Config(SystemCoreClock/1000);  //滴答定时器设定

	Init_Led();
	KEY_Init();
	Init_Usart();
	STM3210B_LCD_Init();
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(Green);
	
	LED_Control(LEDALL,0);
	LED_Control(LED1,1);
	USART_SendString("Welcome to GXCT\r\n");
	while(1){			
	}
}

/**************子程序*****************/

void Delay_ms(uint32_t xMs){
	msTimer=xMs;
	while(msTimer);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
