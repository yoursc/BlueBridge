#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED1   GPIO_Pin_8
#define LED2   GPIO_Pin_9
#define LED3   GPIO_Pin_10
#define LED4   GPIO_Pin_11
#define LED5   GPIO_Pin_12
#define LED6   GPIO_Pin_13
#define LED7   GPIO_Pin_14
#define LED8   GPIO_Pin_15
#define LEDALL LED1 | LED2 | LED3| LED4 | LED5 | LED6 | LED7 | LED8


void Init_LED(void);
void LED_Ctrl(uint16_t la,uint8_t lb);

#endif
