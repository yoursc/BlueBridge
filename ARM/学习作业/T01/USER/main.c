#include "stm32f10x.h"
#include <stdio.h>
#include "lcd.h"
#include "led.h"

#define B1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define B2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define B3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define B4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)

uint32_t msTimer;
uint8_t PA1_ON=0,PA2_ON=0;    //两输出口开关标志位
uint8_t PWM_PA1=90,PWM_PA2=0; //pwm波占空比设定值 0 - 100
uint8_t t_h=23,t_m=59,t_s=50; //时间临时变量
uint8_t KEY_IN=0x00;          //按键待处理标志位
uint8_t user_string[20];

void Delay_ms(uint16_t time_ms);
void Init_lcd(void);
void Init_pwm(void);
void Init_usert(void);
void Init_clock(void);
void Init_all(void);
void Show(void);
void Scan_key(void);
void Handle_key(void);

/***********************/
/********主函数*********/
/***********************/
int main(void)
{
	Init_all();
	LED_Ctrl(LEDALL,0);
	sprintf(user_string,"        None        ");
	Show();
	while (1)
  {
		Scan_key();
		if(KEY_IN){
			Handle_key();
		}
  }
}

/*************************/
/********子函数区*********/
/*************************/
void Delay_ms(uint16_t time_ms){
	msTimer=time_ms;
	while(msTimer);
}
void Init_GPIO(void){
	/* 按键 B1  B2  B3  B4  共地  PWM1 PWM2
	   接口 PA0 PA8 PB1 PB2       PA1  PA2
	*/
	GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE );
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE );
	/***按键上拉输入***/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_0|GPIO_Pin_8;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_1|GPIO_Pin_2;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	/***PWM输出口***/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin  = LEDALL;
	GPIO_InitStruct.GPIO_Speed= GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
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
void Init_all(void){
	SysTick_Config(SystemCoreClock/1000); //1ms中断一次
	Init_GPIO();
	Init_LED();
	Init_pwm();
	Init_lcd();
	Init_usert();
	Init_clock();
}
void Show(void){//接收串口数据显示尚未更改
	uint8_t  string[20];
	
	sprintf(string," PWM_PA1:%3d%%",PWM_PA1);
	LCD_DisplayStringLine(Line1,string);
	sprintf(string," PWM_PA1:%3d%%",PWM_PA2);
	LCD_DisplayStringLine(Line2,string);
	
	sprintf(string," Time   :%2d:%2d:%2d",t_h,t_m,t_s);
	LCD_DisplayStringLine(Line4,string);
	
	LCD_DisplayStringLine(Line5," Channel:           ");
	
	LCD_DisplayStringLine(Line6," Commind:           ");
//	LCD_DisplayStringLine(Line7,user_string);
	/***刷新LED灯状态***/
	GPIO_SetBits(GPIOC, LEDALL);
	if(PA1_ON==0)
		GPIO_SetBits(GPIOC, LED1);
	else
		GPIO_ResetBits(GPIOC, LED1);
	
	if(PA2_ON==0)
		GPIO_SetBits(GPIOC, LED2);
	else
		GPIO_ResetBits(GPIOC, LED2);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_2);
  GPIO_ResetBits(GPIOD,GPIO_Pin_2);
}

void Scan_key(void){
	uint16_t Deviation_ms = 30;
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
	Delay_ms(100);
}
void Handle_key(void){
	switch(KEY_IN){
		case 0x01:
			PA1_ON = ~PA1_ON;
			break;
		case 0x02:
			PA2_ON = ~PA2_ON;
			break;
		case 0x03:
			PWM_PA1+=10;
			if(PWM_PA1>100)
				PWM_PA1=0;
			break;
		case 0x04:
			PWM_PA2+=10;
			if(PWM_PA2>100)
				PWM_PA2=0;
			break;
	}
	Show();
	KEY_IN=0x00;

}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
