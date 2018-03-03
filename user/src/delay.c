#include <delay.h>

__IO uint32_t Delay_Count;

void delay_Init(void)
{
	Delay_Count = 0;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
	SysTick_Config(9000);
}

void delay_nus(uint16_t nus)
{
	Delay_Count = 9 * nus;
}

void delay_nms(uint32_t nms)
{
	Delay_Count = 9000 * nms;
}
