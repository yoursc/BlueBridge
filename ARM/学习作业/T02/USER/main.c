#include "stm32f10x.h"
#include <stdio.h>
#include "led.h"

int main(void)
{
	Init_Led();
	LED_Control(LEDALL,0);
	LED_Control(LED1,1);
  while (1)
  {
  }
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
