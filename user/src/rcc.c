#include <rcc.h>
/*
RCC时钟配置相关
*/
void rcc_Init(){
	//打开USART1,GPIOA,ADC1的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);
	//为DMA配置时钟
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	//为ADC1配置时钟（ADC要求不超过14M），采用72M/8=9M
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
}
