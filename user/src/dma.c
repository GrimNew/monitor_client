#include <dma.h>

void dma_Init()
{
	DMA_InitTypeDef DMA_InitStructure;
	
	//复位DMA1的通道1，DMA使用前必要步骤
	DMA_DeInit(DMA1_Channel1);
	
	//DMA参数配置
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;//DMA连接的外设地址，即ADC1的地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ResaultBuffer;//DMA数据存储地址，自定义静态全局变量ADC_ResaultBuffer的地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;//数据传输单方向，外设到DMA
	DMA_InitStructure.DMA_BufferSize = 3;//数据缓冲大小，3单位
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//外设地址不递增（仅有ADC1一个外设，且只有一个地址存储数据）
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//数据存储地址递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//外设数据大小，半字，即16bit
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//缓冲数据大小，半字，即16bit
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA模式正常，即非循环，存取一次
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMA等级设置为2高（优先级：最高3>高2>中1>低0）
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//关DMA缓冲区到缓冲区
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	//开启DMA1
	DMA_Cmd(DMA1_Channel1,ENABLE);
}

void dma_Judgement()
{
	//等待DMA完成并清除完成标志
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC1));
	DMA_ClearFlag(DMA1_FLAG_TC1);
	
	//关闭DMA后刷新缓冲区大小，否则非循环模式下DMA一次后，缓冲区3单位用完不能进行第二次DMA
	DMA_Cmd(DMA1_Channel1, DISABLE);
	DMA_SetCurrDataCounter(DMA1_Channel1, 3);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
}
