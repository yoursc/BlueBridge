#include "stm32f10x_it.h"

extern u32 TimingDelay;


void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}


void Delay_Ms(u32 nTime)
{
	TimingDelay = nTime;
   while(TimingDelay != 0);
}

/*void PPP_IRQHandler(void)
{
}*/


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
