#include "stm32f10x.h"
#include <stdio.h>

#define LED1    GPIO_Pin_8
#define LED2    GPIO_Pin_9
#define LED3    GPIO_Pin_10
#define LED4    GPIO_Pin_11
#define LED5    GPIO_Pin_12
#define LED6    GPIO_Pin_13
#define LED7    GPIO_Pin_14
#define LED8    GPIO_Pin_15
#define LEDALL	LED1|LED2|LED3|LED4|LED5|LED6|LED7|LED8

//****函数声明****
void Led_Init(void);
void Delay(void);
void LED_Control(uint16_t LED,uint8_t LED_Status);

//***主函数****
int main(void){
	Led_Init();
	LED_Control(LEDALL,0);
	while (1){
		LED_Control(LED1,1);
		Delay();
		LED_Control(LED1,0);
		Delay();
	}
}

//====子函数====================
//简单延时函数
void Delay(void){
	unsigned int i;
	for(i=0x1fffff;i>0;i--);
}
//LED灯I/O口初始化
void Led_Init(void){
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ;
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

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
