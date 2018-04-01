#include "led.h"

//LED灯I/O口初始化
void Init_Led(void){
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin  = LEDALL;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
}

//LED控制函数
void LED_Control(uint16_t LED,uint8_t LED_Status){
	if(LED_Status == 0){
		GPIO_SetBits(GPIOC,LED);
		GPIO_SetBits(GPIOD,GPIO_Pin_2);
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);  //状态锁存
  }
	else{
		GPIO_ResetBits(GPIOC,LED);
		GPIO_SetBits(GPIOD,GPIO_Pin_2);
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);  //状态锁存
  }
}
/******************* Edit By Yours <www.yoursc.cn> *****END OF FILE****/
