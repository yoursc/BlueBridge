#include "usart.h"

void Init_Usart(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_NVIC();
  //Rx 输入端IO口初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  //Tx 输出端IO口初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	// 设置串口工作模式
	USART_InitStructure.USART_BaudRate = 19200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  //初始化串口
  USART_Init(USART2, &USART_InitStructure);
  //打开串口中断
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //接收中断
  //启动串口
  USART_Cmd(USART2, ENABLE);
}

void USART_NVIC(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

//**串口字符串发送程序*********************************
void USART_SendString(int8_t *str)
{
	uint8_t index = 0;
	do{
		USART_SendData(USART2, str[index]);
		while((USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET));
		index++;
	}
	while(str[index] != 0);  //检查结束符标志
}

//**串口接收中断程序**********************************
void USART2_IRQHandler(void){
	uint8_t temp;	
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET){
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);		
		temp = USART_ReceiveData(USART2);
		//处理接收数据的子程序

//		if((temp == 'x') || (RXCUNT == 20)){
//			RXCUNT = 0;
//			RXOVER = 1;  //接收完成标志位置位
//			USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);
//		}
//		else{
//			USART_RXBUF[RXCUNT] = temp;
//			++RXCUNT;			
//		}
		
		//子程序结束
	}
}

