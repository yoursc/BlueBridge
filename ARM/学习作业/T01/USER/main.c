#include "stm32f10x.h"
#include <stdio.h>

void Init_key(void);
void Init_led(void);
void Init_pwm(void);
void Init_lcd(void);
void Init_usert(void);
void Init_clock(void);

int main(void)
{
	Init_key();
	Init_led();
	Init_pwm();
	Init_lcd();
	Init_usert();
	Init_clock();
  while (1)
  {
  }
}

/********子函数区*********/
void Init_key(void)
{
	/* 按键  B1   B2   B3   B4  共地
	** 接口 PA0  PA8  PB1  PB2    */
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOA, ENABLE );
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}
void Init_led(void)
{
	/* 小灯 LD1 LD2
	** 接口 PC8 PC9
	*/
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOA, ENABLE );
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}
void Init_pwm(void)
{
}
void Init_lcd(void)
{
}
void Init_usert(void)
{
}
void Init_clock(void)
{
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
