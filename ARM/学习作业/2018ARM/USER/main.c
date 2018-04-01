#include "stm32f10x.h"
#include <stdio.h>
#include "i2c.h"
#include "lcd.h"

//自建头文件
#include "led.h"
#include "key.h"
#include "pwm.h"

//辅助变量
u32 TimingDelay = 0;

//核心变量

//函数声明
void Delay_Ms(u32 nTime);

//*****************************//
//**********主函数*************//
//*****************************//
int main(void)
{
	//初始化
	SysTick_Config(SystemCoreClock/1000);
	Init_Led();
	Init_Key();
	Init_Pwm();
	
	STM3210B_LCD_Init();
	LCD_Clear(Black);
	LCD_SetTextColor(Green);
	LCD_SetBackColor(Black);
	
	LED_Control(LEDALL,0);
  while (1)
  {
		
  }
}

//*****************************//
//**********子函数*************//
//*****************************//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
