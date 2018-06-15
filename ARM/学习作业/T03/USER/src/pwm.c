#include "pwm.h"
// PA1        PA2       口输出PWM波
// TIM2_CH2   TIM2_CH3   时钟产生
//串口使用PA2,注意预防冲突

GPIO_InitTypeDef  GPIO_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;

void Init_PWM(void)
{
	//时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	//初始化IO口 PA1 PA2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void PWM_Ctrl(uint16_t PWM_VAL1, uint16_t PWM_VAL2)
{
	uint16_t fre = 1000;
  uint16_t TimerPeriod = (uint16_t)((SystemCoreClock/72/fre)-1);
  uint16_t PWM1Pulse = (uint16_t) (((uint32_t) PWM_VAL1 * (TimerPeriod - 1)) / 100);
  uint16_t PWM2Pulse = (uint16_t) (((uint32_t) PWM_VAL2 * (TimerPeriod - 1)) / 100);

	
	/* TIM2 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		

	TIM_TimeBaseStructure.TIM_Period = TimerPeriod;//周期长度
	TIM_TimeBaseStructure.TIM_Prescaler = 0;//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;//时钟分割
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	//TIM2预分频设置:1MHZ,APB1分频系数2，输入到TIM3时钟为36MHzx2 = 72MHz  
	TIM_PrescalerConfig(TIM2,71, TIM_PSCReloadMode_Immediate);		  //TIM2频率设置

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;            //TIM 脉冲宽度调制模式 2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//输出比较状态
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;     //输出比较极性低
	TIM_OCInitStructure.TIM_Pulse = PWM1Pulse;
	//初始化PWM1
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	//初始化PWM2
	TIM_OCInitStructure.TIM_Pulse = PWM2Pulse;
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM2, ENABLE);//使能TIM2定时计数器
	TIM_CtrlPWMOutputs(TIM2, ENABLE);//使能TIM2 PWM输出模式
}
