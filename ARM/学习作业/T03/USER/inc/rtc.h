#ifndef __RTC_H
#define __RTC_H

#include "stm32f10x.h"

extern uint32_t TimeDisplay; //RTC时间更新标志位

void Init_RTC(void);
void RTC_NVIC(void);

#endif
