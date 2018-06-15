#include "key.h"

extern void Delay_ms(uint32_t xMs);

void Init_KEY(void){
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_8;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

uint8_t Key_Scan(void){
	uint8_t Deviation = 20; //消抖时长
	uint8_t key_value=0x00;

	if(B1 == 0){
		Delay_ms(Deviation);
		if(B1 == 0){
			key_value=0x01;
		}
	}

	if(B2 == 0){
		Delay_ms(Deviation);
		if(B2 == 0){
			key_value=0x02;
		}
	}

	if(B3 == 0){
		Delay_ms(Deviation);
		if(B3 == 0){
			key_value=0x03;
		}
	}

	if(B4 == 0){
		Delay_ms(Deviation);
		if(B4 == 0){
			key_value=0x04;
		}
	}
	return key_value;
}

