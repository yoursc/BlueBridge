#include "LED.h"

void Init_LED(void){
	/* 小灯 LD1  -  LD8   LE 
	   接口 PC8  -  PC15  PD2
	*/
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE );
	/***LED灯推挽输出***/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin  = LEDALL;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	//LED灯控制锁存器
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_2;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
}

void LED_Ctrl(uint16_t ledx,uint8_t led_status){
	if(led_status==0)
		GPIO_SetBits(GPIOC, ledx);
	else
		GPIO_ResetBits(GPIOC, ledx);
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
  GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}