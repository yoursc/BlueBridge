#include "stm32f10x.h"
#include <stdio.h>
#include "led.h"
#include "key.h"
#include "usart.h"
#include "lcd.h"
#include "i2c.h"
#include "adc.h"
#include "rtc.h"
#include "tim.h"
#include "pwm.h"

uint32_t msTimer;
uint8_t LED2_Status = 0;
uint8_t Status_ADC = 0;
uint8_t Status_Usert = 0;

void Delay_ms(uint32_t xMs);
uint8_t x24c02_read(uint8_t address);
void x24c02_write(uint8_t address,uint8_t info);

/***************主函数区***************/

int main(void)
{
	uint8_t addr=0x00;
	uint8_t temp;
	uint8_t string[20];
	SysTick_Config(SystemCoreClock/1000);  //滴答定时器设定
	//外设初始化
	Init_Led();
	Init_KEY();
	Init_Usart();
	Init_Adc();
	i2c_init();
	Init_RTC();
	Init_TIM();
	Init_PWM();
	PWM_Ctrl(50,70);
	STM3210B_LCD_Init();
	LCD_Clear(Black);
	LCD_SetBackColor(Black);
	LCD_SetTextColor(Green);
	//初始化结束
	LED_Control(LEDALL,0);
	USART_SendString("Welcome to GXCT\r\n");
	while(1){
		if(Status_ADC>=4){
		sprintf(string,"%s%.3f","ADC Value:",Read_ADC());
		LCD_DisplayStringLine(Line7,string);
		Status_ADC = 0;
		}
		
		if(TimeDisplay == 1){
			uint32_t TimeVar = RTC_GetCounter();
			temp = x24c02_read(addr);
			sprintf(string,"ADDR:0x%d,EPROM:%2d",addr,temp);
			LCD_DisplayStringLine(Line6,string);
			addr++;
			
			sprintf(string,"Time: %0.2d:%0.2d:%0.2d",(TimeVar/3600), ((TimeVar%3600)/60), ((TimeVar%3600)%60));
			LCD_DisplayStringLine(Line8,string);
			TimeDisplay = 0;  //清除标志位
		}
		
		if(Status_Usert==1)
		{
			USART_SendString("Hellow World!\r\n");
			Status_Usert=0;
		}

	}
}

/**************子程序*****************/

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

void Delay_ms(uint32_t xMs){
	msTimer=xMs;
	while(msTimer);
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
