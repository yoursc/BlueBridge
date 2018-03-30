#include "KEY.h"

extern void Delay_ms(uint16_t time_ms);

void Init_KEY(void){
	/* 按键 B1  B2  B3  B4  共地
	   接口 PA0 PA8 PB1 PB2
	*/
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE );
	/***按键上拉输入***/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_8;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

uint8_t Scan_key(void){
	uint8_t KEY_IN=0x00;
	uint16_t Deviation_ms = 30;  //消抖时长 ms
	
	if(B1 == 0){
		Delay_ms(Deviation_ms);
		if(B1 == 0)
			KEY_IN = 0x01;
	}
	if(B2 == 0){
		Delay_ms(Deviation_ms);
		if(B2 == 0)
			KEY_IN = 0x02;
	}
	if(B3 == 0){
		Delay_ms(Deviation_ms);
		if(B3 == 0)
			KEY_IN = 0x03;
	}
	if(B4 == 0){
		Delay_ms(Deviation_ms);
		if(B4 == 0)
			KEY_IN = 0x04;
	}
	return KEY_IN;
}

