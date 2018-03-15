#include <delay.h>
/*
SysTick时钟完成精准延时
*/

//延时计数全局变量，在SysTick_Handler()中断函数中进行自减
__IO uint32_t Delay_Count;

//初始化SysTick时钟，全局计数归零，重载Reload值，配置中断优先级
void delay_Init(void)
{
	Delay_Count = 0;
	SysTick->LOAD = 9000 - 1;//重载Reload值，计数1ms需要计数9000次，即8999->0
	NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);
}

//延时n毫秒
void delay_nms(uint32_t nms)
{
	Delay_Count = nms;//全局计数传值
	SysTick->VAL = 0x00;//清空SysTick计数值
	SysTick->CTRL = 0x03;//bit2->0，使用外置晶振，72M/8=9M；bit1->1,开中断；bit0->1使能SysTick
	while(Delay_Count != 0);//等待全局计数归零
	SysTick->CTRL = 0x00;//bit0->0关闭SysTick
}
