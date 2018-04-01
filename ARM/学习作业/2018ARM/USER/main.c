#include "stm32f10x.h"
#include <stdio.h>
#include "i2c.h"
#include "lcd.h"

//自建头文件
#include "led.h"

//辅助变量


//核心变量


//函数声明
u32 TimingDelay = 0;

//*****************************//
//**********主函数*************//
//*****************************//
int main(void)
{
	SysTick_Config(SystemCoreClock/1000);

  while (1)
  {
  }
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
