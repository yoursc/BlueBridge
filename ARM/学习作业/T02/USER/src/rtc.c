#include "rtc.h"

//初始时间设定
#define HH 10  //时
#define MM 59  //分
#define SS 50  //秒

uint32_t TimeDisplay; //RTC时间更新标志位

void RTC_Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

	PWR_BackupAccessCmd(ENABLE);
	BKP_DeInit();
	RCC_LSICmd(ENABLE);
	//等待LSE准备就绪
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);
	
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	RCC_RTCCLKCmd(ENABLE);

	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	//启用RTC秒
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	RTC_WaitForLastTask();
	//设置RTC预分频器：将RTC周期设置为1秒
	RTC_SetPrescaler(39999); /* RTC周期 = RTCCLK/RTC_PR = (40 KHz)/(39999+1) */
	//等到RTC寄存器的最后写入操作完成
	RTC_WaitForLastTask();
	
	RTC_SetCounter(HH*3600+MM*60+SS);
	RTC_WaitForLastTask();
}

void RTC_NVIC(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	/* Enable the RTC Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void RTC_IRQHandler(void)
{
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET){
		RTC_ClearITPendingBit(RTC_IT_SEC);
		TimeDisplay = 1;  //时间更新标志置位
		/* Wait until last write operation on RTC registers has finished */
		RTC_WaitForLastTask();
		/* 23:59:59 */
		if (RTC_GetCounter() == 0x00015180){
			RTC_SetCounter(0x0);
			RTC_WaitForLastTask();
		}
	}
}
