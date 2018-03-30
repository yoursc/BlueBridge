#include "stm32f10x.h"
#include <stdio.h>
#include "led.h"
#include "key.h"

uint32_t msTimer;


int main(void)
{
	SysTick_Config(SystemCoreClock/1000);
	Init_Led();
	KEY_Init();
	LED_Control(LEDALL,0);
	LED_Control(LED1,1);
  while (1)
  {
		if(Key_Scan()==0x02)
		{
			LED_Control(LED2,1);
		}
  }
}

void Delay_ms(uint32_t xMs){
	msTimer=xMs;
	while(msTimer);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
