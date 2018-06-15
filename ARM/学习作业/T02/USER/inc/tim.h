#ifndef __TIM_H
#define __TIM_H

#include "stm32f10x.h"

void Init_TIM(void);
void TIM_NVIC(void);
void TIM3_IRQHandler(void);

#endif