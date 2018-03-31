#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"

void Init_PWM(void);
void PWM_Ctrl(uint16_t PWM_VAL1, uint16_t PWM_VAL2);

#endif