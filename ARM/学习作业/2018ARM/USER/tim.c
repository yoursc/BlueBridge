#include "tim.h"

extern uint8_t LED2_Status;

void Init_TIM(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	//中断向量配置
	TIM_NVIC();

	TIM_TimeBaseStructure.TIM_Period = 50000;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	//TIM3预分频设置:1MHZ,APB1分频系数2，TIM3时钟为36MHzx2 = 72MHz
	TIM_PrescalerConfig(TIM3,71, TIM_PSCReloadMode_Immediate);
	//通用定时器TIM3中断配置
	TIM_ITConfig(TIM3,TIM_IT_Update, ENABLE);
	//启用TIM3计数器
	TIM_Cmd(TIM3, ENABLE);
}

void TIM_NVIC(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	//启用TIM3全局中断
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}

void TIM3_IRQHandler(void)
{
	if(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update) == SET){
		//清除标志位
		TIM_ClearFlag(TIM3,TIM_FLAG_Update);

		//中断服务程序
		//if(++_50ms == 20){
		//	_50ms = 0;
		//	if(++leds == 9){
		//		leds = 1;
		//	}
		//}
		//中断服务结束
	}
}