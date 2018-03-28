#include "stm32f10x.h"
#include <stdio.h>
#include "lcd.h"
//使用lcd屏幕时,使用了PC总线
//LED灯使用的也是PC总线
//访问LCD后再访问LED时
//锁存器外的PC上的数据已被修改，请注意
int main(void)
{
	STM3210B_LCD_Init();
	LCD_Clear(Black);

	LCD_SetTextColor(Green);
	LCD_SetBackColor(Black);

	LCD_DisplayStringLine(Line0,"     Hello world!   ");
	LCD_DisplayStringLine(Line2," Name  : Yours      ");
	LCD_DisplayStringLine(Line3," Age   : 22         ");
	LCD_DisplayStringLine(Line4," Web   : yoursc.cn  ");
	LCD_DisplayStringLine(Line5," E-Mail:            ");
	LCD_DisplayStringLine(Line6,"peiwencao@vip.qq.com");
	LCD_DisplayStringLine(Line7," Line 7 ----------  ");
	LCD_DisplayStringLine(Line8," Line 8 ----------  ");
	LCD_DisplayStringLine(Line9," Line 9 ----------  ");
  while (1)
  {
  }
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
