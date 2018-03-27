#include "stm32f10x.h"
#include <stdio.h>
#include <lcd.h>

#define LED1   GPIO_Pin_8
#define LED2   GPIO_Pin_9
#define LED3   GPIO_Pin_10
#define LED4   GPIO_Pin_11
#define LED5   GPIO_Pin_12
#define LED6   GPIO_Pin_13
#define LED7   GPIO_Pin_14
#define LED8   GPIO_Pin_15
#define LEDALL LED1 | LED2 | LED3| LED4 | LED5 | LED6 | LED7 | LED8

uint32_t msTimer;

void Init_all(void);
void Delay_ms(uint16_t time_ms);
void Init_key(void);
void Init_led(void);
void LED_Ctrl(uint16_t la,uint8_t lb);
void Init_lcd(void);
void Init_pwm(void);
void Init_usert(void);
void Init_clock(void);

/***********************/
/********主函数*********/
/***********************/
int main(void)
{
	Init_all();
  while (1)
  {
  }
}

/*************************/
/********子函数区*********/
/*************************/
void Init_all(void){
	SysTick_Config(SystemCoreClock/1000);
	Init_key();
	Init_led();
	Init_pwm();
	Init_lcd();
	Init_usert();
	Init_clock();
}
void Delay_ms(uint16_t time_ms){
	msTimer=time_ms;
	while(msTimer);
}
void Init_key(void){
	/* 按键  B1   B2   B3   B4  共地
	** 接口 PA0  PA8  PB1  PB2    */
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE );

	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}
{
	GPIO_ReadInputDataBit(GPIOx, uint16_t GPIO_Pin);
}
void Init_led(void){
	/* 小灯 LD1 LD2
	** 接口 PC8 PC9  */
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE );
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin  = LED1 | LED2 | LED3| LED4 | LED5 | LED6 | LED7 | LED8;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_2MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_2;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	LED_Ctrl(LEDALL,0);
}
void LED_Ctrl(uint16_t ledx,uint8_t led_status){
	if(led_status==1)
		GPIO_ResetBits(GPIOC, ledx);
	else
		GPIO_SetBits(GPIOC, ledx);
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
	GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}
void Init_lcd(void){
	STM3210B_LCD_Init();
	LCD_Clear(White);
	LCD_SetTextColor(Black);
	LCD_SetBackColor(White);
}
void Init_pwm(void)
{
}
void Init_usert(void)
{
}
void Init_clock(void)
{
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
