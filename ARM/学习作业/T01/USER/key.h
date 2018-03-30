#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

#define B1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define B2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define B3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define B4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_2)

void Init_KEY(void);
uint8_t Scan_key(void);


#endif
