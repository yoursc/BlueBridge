#include "stm32f10x.h"
#include <stdio.h>
#include "lcd.h"

/*  B1-PA0   B2-PA8   B3-PB1   B4-PB2  */

#define B1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define B2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define B3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define B4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)

uint32_t msTimer=0;

void KEY_Init(void);
void LCD_Init(void);
void Delay_ms(uint32_t xMs);
uint8_t Key_Scan(void);

int main(void){
	uint8_t keyin;
	
	SysTick_Config(SystemCoreClock/1000);
	KEY_Init();
	LCD_Init();
	
	Delay_ms(500);
	LCD_DisplayStringLine(Line2,"++ Start  Success ++");
	Delay_ms(200);
	LCD_DisplayStringLine(Line4,"++Press any key...++");
	
	while (1){
		keyin = Key_Scan();
		switch(keyin){
			case 0xff:
				LCD_DisplayStringLine(Line6,"++      None      ++");
				break;
			case '1':
				LCD_DisplayStringLine(Line6,"++    Button 1    ++");
				break;
			case '2':
				LCD_DisplayStringLine(Line6,"++    Button 2    ++");
				break;
			case '3':
				LCD_DisplayStringLine(Line6,"++    Button 3    ++");
				break;
			case '4':
				LCD_DisplayStringLine(Line6,"++    Button 4    ++");
				break;
		}
		keyin=0;
  }
}

void KEY_Init(void){
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

void LCD_Init(void){
	STM3210B_LCD_Init();
	LCD_Clear(Black);
	LCD_SetTextColor(Green);
	LCD_SetBackColor(Black);
	LCD_DisplayStringLine(Line0,"====================");
	LCD_DisplayStringLine(Line1,"====================");
	LCD_DisplayStringLine(Line2,"++                ++");
	LCD_DisplayStringLine(Line3,"++                ++");
	LCD_DisplayStringLine(Line4,"++                ++");
	LCD_DisplayStringLine(Line5,"++                ++");
	LCD_DisplayStringLine(Line6,"++                ++");
	LCD_DisplayStringLine(Line7,"++                ++");
	LCD_DisplayStringLine(Line8,"====================");
	LCD_DisplayStringLine(Line9,"====================");
}

void Delay_ms(uint32_t xMs){
	msTimer=xMs;
	while(msTimer);
}

uint8_t Key_Scan(void){
	uint8_t key_value=0xff;
	if(B1 == 0){
		key_value='1';
	}
	if(B2 == 0){
		key_value='2';
	}
	if(B3 == 0){
		key_value='3';
	}
	if(B4 == 0){
		key_value='4';
	}
	return key_value;
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
