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
u8 hh[5]={1,2,3,4,5};
u8 mm[5]={11,12,13,14,15};
u8 ss[5]={21,22,23,24,25};
char Num_Table[10]={'0','1','2','3','4','5','6','7','8','9'};
char Strings[20];  //转义打印变量字符用

//核心变量
uint8_t Status_Clock = 1; //当前显示闹钟 1 2 3 4 5
u8 Now[3];
uint8_t Status_Mode =0; //模式状态 0-停止 1-暂停 2-开始  3-设置
													//           STOP   PAUL   BEGIN   SET
uint8_t Status_Setting = 0;//设置模式 0-非 1-时 2-分 3-秒

//函数声明
void Delay_Ms(u32 nTime);
void Show(u8 linex);
void Show_Warning(u8 *ptr);
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
	//硬件初始化
	SysTick_Config(SystemCoreClock/1000);
	Init_Led();
	Init_Key();
	Init_Pwm();
	//屏幕初始化
	STM3210B_LCD_Init();
	LCD_Clear(Black);
	LCD_SetTextColor(Green);
	LCD_SetBackColor(Black);
	//变量初始化
	Now[0]=hh[Status_Clock-1];
	Now[1]=mm[Status_Clock-1];
	Now[2]=ss[Status_Clock-1];

	//高级初始化程序
	LED_Control(LEDALL,0);
	Show(1);
	Show(2);
	Show(3);
	Show_Warning("   Hello  World  !   ");
//	LCD_DisplayChar(Line1,319-16*2,'F');
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

//短按B1***************************
void Key_B1_S(void)
{
	Status_Mode = 0;   //计时器停止
	Status_Setting = 0;//设置结束
	
	Status_Clock+=1; 
	if(Status_Clock == 6)
		Status_Clock = 1;

	Now[0]=hh[Status_Clock-1];
	Now[1]=mm[Status_Clock-1];
	Now[2]=ss[Status_Clock-1];

	Show(1);
	Show(2);
	Show(3);
}
//短按B2***************************
void Key_B2_S(void)
{
	if( (Status_Mode==0) || (Status_Mode==3) ){
		Status_Setting += 1;
		Status_Mode = 3;
		if(Status_Setting == 4){
			Status_Setting = 0;
			Status_Mode = 0;
		}
		Show(3);
		Show(4);
	}
	else
	{
		Show_Warning(" Please Stop Clock ! ");
	}	
}
//短按B3***************************
void Key_B3_S(void)
{
}
//短按B4***************************
void Key_B4_S(void)
{
	LED_Control(LEDALL,0);
}
//长按B1***************************
void Key_B1_L(void)
{
	Show_Warning("Def Key_B1_L is Empty");
}
//长按B2***************************
void Key_B2_L(void)
{
	if( (Status_Mode==0) || (Status_Mode==3) ){
		//将当前倒计时的设置时长保存到EPROM
		Status_Mode = 0;
		Show(2);
		Show(3);
		//此处待补充向EPROM存储的代码！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
		sprintf(Strings," Clock %d has saving ! ",Status_Clock);		
		Show_Warning(Strings);
	}
	else	{
		Show_Warning(" Please Stop Clock ! ");
	}	
}
//长按B3***************************
void Key_B3_L(void)
{
}
//长按B4***************************
void Key_B4_L(void)
{
	LED_Control(LEDALL,0);
	LED_Control(LED1,1);	
}

void Show(u8 linex)
{	
	switch(linex){
		
		case 1:
			sprintf(Strings,"  Clock : %1d       ",Status_Clock);
			LCD_DisplayStringLine(Line1,Strings);
			break;
		
		case 2:
			sprintf(Strings,"     %2d:%2d:%2d     ",Now[0],Now[1],Now[2]);
			LCD_DisplayStringLine(Line3,Strings);
			break;
		
		case 3:
			switch(Status_Mode)
			{
				case 0:
					sprintf(Strings,"       STOP       ");
					break;
				case 1:
					sprintf(Strings,"       PAUSE      ");
					break;
				case 2:
					sprintf(Strings,"      BEGING      ");
					break;
				case 3:
					sprintf(Strings,"      SETTING     ");
					break;
			}
			LCD_DisplayStringLine(Line5,Strings);
			break;
			
		case 4:
			Show(2);
			if(Status_Setting!=0)
			{
				LCD_SetBackColor(Blue);
				LCD_DisplayChar(Line3,319-16*(3*Status_Setting+2), Num_Table[ Now[Status_Setting-1]/10 ] );
				LCD_DisplayChar(Line3,319-16*(3*Status_Setting+3), Num_Table[ Now[Status_Setting-1]%10 ] );
				LCD_SetBackColor(Black);
			}
			break;
	}
}
//显示警告，在屏幕上打印提醒
// 等待时长 2s
void Show_Warning(u8 *ptr)
{
	LCD_SetTextColor(Red);
	LCD_DisplayStringLine(Line7,ptr);
	LCD_SetTextColor(Green);
	Delay_Ms(2000);
	LCD_ClearLine(Line7);
}

/******************* Edit By Yours <www.yoursc.cn> *****END OF FILE****/
