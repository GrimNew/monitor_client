#include <delay.h>

__IO uint32_t Delay_Count;//

void delay_Init(void)
{
	Delay_Count = 0;//
	SysTick->LOAD = 9000 - 1;//
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);//
}

void delay_nms(uint32_t nms)
{
	Delay_Count = nms;//
	SysTick->VAL = 0x00;//
	SysTick->CTRL = 0x03;//
	while(Delay_Count != 0);//
	SysTick->CTRL = 0x00;//
}
