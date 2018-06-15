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
uint8_t hh[5];
uint8_t mm[5];
uint8_t ss[5];
u16 Key_Num = 0;          //按键长按计数器
u16 Key_Long_Set = 16 ;   //长按按键计数器阈值
u32 Key_Long_Delay = 50 ; //长按按键计数器周期 ms
char Num_Table[10]={'0','1','2','3','4','5','6','7','8','9'};
char Strings[20];  //转义打印变量字符用
unsigned char Addr_Head = 0xf0;// EPROM 存储首地址，后续共0x0e个字节数据

//核心变量
uint8_t Status_Clock = 1; //当前显示闹钟 1 2 3 4 5
uint8_t Now[3];
uint8_t Status_Mode =0; //模式状态 0-停止 1-暂停 2-开始  3-设置
uint8_t Status_Setting = 0;//设置模式 0-非 1-时 2-分 3-秒

//函数声明
void Delay_Ms(u32 nTime);
void Show(u8 linex);
void Show_Warning(u8 *ptr);
void Deal_Key(uint8_t key);
void Deal_Add(void);
void Deal_Set_Mode(uint8_t mode);
void Key_B1_S(void);
void Key_B2_S(void);
void Key_B3_S(void);
void Key_B4_S(void);
void Key_B1_L(void);
void Key_B2_L(void);
void Key_B3_L(void);
void Key_B4_L(void);
uint8_t x24c02_read(uint8_t address);
void x24c02_write(unsigned char address,unsigned char info);
void Time_Load(void);
void Time_Save(uint8_t clockx);

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
	i2c_init();	
	NVIC_Configuration();
	//屏幕初始化
	STM3210B_LCD_Init();
	LCD_Clear(Black);
	LCD_SetTextColor(Green);
	LCD_SetBackColor(Black);
	//变量初始化
	Time_Load();
	Now[0]=hh[Status_Clock-1];
	Now[1]=mm[Status_Clock-1];
	Now[2]=ss[Status_Clock-1];

	//高级初始化程序
	TIM_Cmd(TIM3, DISABLE);
	LED_Control(LEDALL,0);
	Show(1);
	Show(2);
	Show(3);
	Show_Warning("   Hello  World  !   ");
  while (1)
  {
		Deal_Key(Key_Scan());
		
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
void Deal_Key(uint8_t key)
{
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

void Deal_Add(void)
{
		switch(Status_Setting){
			case 0:
				Show_Warning(" Not in Set Mode !  ");
				break;
			case 1:
				Now[Status_Setting-1]++;
				if(	Now[Status_Setting-1]==24 )
					Now[Status_Setting-1] = 0;
				break;
			default:
				Now[Status_Setting-1]++;
				if(	Now[Status_Setting-1]==60 )
					Now[Status_Setting-1] = 0;
				break;
	}
}

void Deal_Set_Mode(uint8_t mode)
{
	Status_Mode = mode;
	LED_Control(LEDALL,0);
	switch(mode)
	{
		case 0:
			hh[Status_Clock-1]=Now[0];
			mm[Status_Clock-1]=Now[1];
			ss[Status_Clock-1]=Now[2];
			TIM_Cmd(TIM3, DISABLE);
			break;
		case 1:
			TIM_Cmd(TIM3, DISABLE);
			break;
		case 2:
			TIM_Cmd(TIM3, ENABLE);
			LED_Control(LEDALL,0);
			LED_Control(LED1,1);
			break;
	}
	Show(3);
}

//短按B1***************************
void Key_B1_S(void)
{
	Deal_Set_Mode(0);//计时器停止
	Status_Setting = 0;//设置结束
	
	Status_Clock+=1; 
	if(Status_Clock == 6)
		Status_Clock = 1;

	Now[0]=hh[Status_Clock-1];
	Now[1]=mm[Status_Clock-1];
	Now[2]=ss[Status_Clock-1];

	Show(1);
	Show(2);
}
//短按B2***************************
void Key_B2_S(void)
{
	if( (Status_Mode==0) || (Status_Mode==3) ){
		Status_Setting += 1;
		Deal_Set_Mode(3);
		if(Status_Setting == 4){
			Status_Setting = 0;
			Deal_Set_Mode(0);
		}
		Show(2);
	}
	else
	{
		Show_Warning(" Please Stop Clock ! ");
	}	
}
//短按B3***************************
void Key_B3_S(void)
{
	Deal_Add();
	hh[Status_Clock-1]=Now[0];
	mm[Status_Clock-1]=Now[1];
	ss[Status_Clock-1]=Now[2];
	Show(2);
}
//短按B4***************************
void Key_B4_S(void)
{
	switch(Status_Mode)
	{
		case 2:
			Deal_Set_Mode(1);
			break;
		case 3:
			Show_Warning("Please Exit Set Mode");
			break;
		default:
			Deal_Set_Mode(2);
			break;
	}
	Deal_Set_Mode(Status_Mode);
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
		Deal_Set_Mode(0);
		Status_Setting = 0;
		Show(2);
		Time_Save(Status_Clock);
		
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
	while( Key_Scan()!=0x00 )
	{
		Deal_Add();
		hh[Status_Clock-1]=Now[0];
		mm[Status_Clock-1]=Now[1];
		ss[Status_Clock-1]=Now[2];
		Show(2);
		Delay_Ms(100);
	}
}
//长按B4***************************
void Key_B4_L(void)
{
	Deal_Set_Mode(0);
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
			//设置模式时执行以下
			if(Status_Setting!=0)
			{
				LCD_SetBackColor(Blue);
				LCD_DisplayChar(Line3,319-16*(3*Status_Setting+2), Num_Table[ Now[Status_Setting-1]/10 ] );
				LCD_DisplayChar(Line3,319-16*(3*Status_Setting+3), Num_Table[ Now[Status_Setting-1]%10 ] );
				LCD_SetBackColor(Black);
			}		
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

uint8_t x24c02_read(uint8_t address)
{
	unsigned char val;
	
	I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();

	I2CSendByte(address);
	I2CWaitAck();

	I2CStart();
	I2CSendByte(0xa1);
	I2CWaitAck();
	val = I2CReceiveByte();
	I2CWaitAck();
	I2CStop();

	return(val);
}

void x24c02_write(unsigned char address,unsigned char info)
{
	I2CStart();
	I2CSendByte(0xa0);
	I2CWaitAck();

	I2CSendByte(address);
	I2CWaitAck();
	I2CSendByte(info);
	I2CWaitAck();
	I2CStop();
}

void Time_Load(void)
{
	u8 i;
	unsigned char addr = Addr_Head;
	for(i=0;i<=4;i++)
	{
		hh[i] = x24c02_read(addr);
		addr += 0x01;
		mm[i] = x24c02_read(addr);
		addr += 0x01;
		ss[i] = x24c02_read(addr);
		addr += 0x01;
	}
}

void Time_Save(uint8_t clockx)
{
	unsigned char addr = Addr_Head + 0x03*(clockx-1);
	x24c02_write(addr,hh[clockx-1]);
	Delay_Ms(20);
	addr+=1;
	x24c02_write(addr,mm[clockx-1]);
	Delay_Ms(20);
	addr+=1;
	x24c02_write(addr,ss[clockx-1]);
	Delay_Ms(20);
}

/******************* Edit By Yours <www.yoursc.cn> *****END OF FILE****/
