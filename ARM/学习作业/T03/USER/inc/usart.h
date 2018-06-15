#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"


void Init_Usart(void);
void USART_NVIC(void);
void USART_SendString(int8_t *str);

#endif
