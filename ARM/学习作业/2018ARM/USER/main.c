#include "stm32f10x.h"
#include <stdio.h>
#include "i2c.h"
#include "lcd.h"

//自建头文件
#include "led.h"
#include "key.h"
#include "pwm.h"

//辅助变量
u32 TimingDelay = 0;

//核心变量
uint8_t Status_Clock = 1; //当前显示闹钟 1 2 3 4 5
u8 HH=0,MM=1,SS=0;
uint8_t Status_Status =0; //模式状态 0-停止 1-暂停 2-开始  3-设置
													//           STOP   PAUL   BEGIN   SET

//函数声明
void Delay_Ms(u32 nTime);
void Key_Deal(uint8_t key);
void Key_B1_S(void);
void Key_B2_S(void);
void Key_B3_S(void);
void Key_B4_S(void);
void Key_B1_L(void);
void Key_B2_L(void);
void Key_B3_L(void);
void Key_B4_L(void);

//*****************************//
//**********主函数*************//
//*****************************//
int main(void)
{
	//初始化
	SysTick_Config(SystemCoreClock/1000);
	Init_Led();
	Init_Key();
	Init_Pwm();
	
	STM3210B_LCD_Init();
	LCD_Clear(Black);
	LCD_SetTextColor(Green);
	LCD_SetBackColor(Black);
	
	LED_Control(LEDALL,0);
  while (1)
  {
		Key_Deal(Key_Scan());
		
  }
}

//*****************************//
//**********子函数*************//
//*****************************//
void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
	while(TimingDelay != 0);
}

//长短按键区分
void Key_Deal(uint8_t key)
{
	u16 Key_Num = 0;          //按键长按计数器
	u16 Key_Long_Set = 16 ;   //长按按键计数器阈值
	u32 Key_Long_Delay = 50 ; //长按按键计数器周期 ms

	//长按判断
	while(Key_Scan())
	{
		Delay_Ms(Key_Long_Delay);
		if(Key_Num >= Key_Long_Set)
			break;
		Key_Num += 1;
	}
	//判断已生效
	
	if(Key_Num >= Key_Long_Set){
		//长按键程序
		switch(key){
			case 0x01:
				Key_B1_L();
				break;
			case 0x02:
				Key_B2_L();
				break;
			case 0x03:
				Key_B3_L();
				break;
			case 0x04:
				Key_B4_L();
				break;
		}
	}
	else{
		//短按键程序
		switch(key){
			case 0x01:
				Key_B1_S();
				break;
			case 0x02:
				Key_B2_S();
				break;
			case 0x03:
				Key_B3_S();
				break;
			case 0x04:
				Key_B4_S();
				break;
		}
	}
	while( Key_Scan() );
	Key_Num=0;	
}

void Key_B1_S(void)
{
}
void Key_B2_S(void)
{
}
void Key_B3_S(void)
{
}
void Key_B4_S(void)
{
	LED_Control(LEDALL,0);
}
void Key_B1_L(void)
{
}
void Key_B2_L(void)
{
}
void Key_B3_L(void)
{
}
void Key_B4_L(void)
{
	LED_Control(LEDALL,0);
	LED_Control(LED1,1);	
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
