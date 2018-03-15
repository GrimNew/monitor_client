#include <adc.h>
/*
ADC配置及获取
*/

//ADC复位，ADC配置，ADC校准
void adc_Init()
{
	ADC_InitTypeDef ADC_InitStructure;
	
	//ADC复位，ADC使用前必要步骤
	ADC_DeInit(ADC1);
	
	//ADC初始化设置
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;//扫描开
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//循环转换关
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//事件关，采用软件启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = ADC_Channel_3;//ADC通道数目3
	ADC_Init(ADC1, &ADC_InitStructure);
	
	//开启内部温度传感器和供电电平检测
	ADC_TempSensorVrefintCmd(ENABLE);
	
	//ADC规则通道配置
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);//PA0的ADC采集使用通道0，采样顺序规则1，采样周期55.5个周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 2, ADC_SampleTime_55Cycles5);//MCU内部温度传感器使用通道16，采样顺序规则1，采样周期55.5个周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_17, 3, ADC_SampleTime_55Cycles5);//MCU内部电平使用通道17，采样顺序规则1，采样周期55.5个周期
	
	//开启ADC1的DMA，开启ADC1
	ADC_DMACmd(ADC1,ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
	//ADC校准
	ADC_ResetCalibration(ADC1);//复位校准并等待完成
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);//开始校准并等待完成
	while(ADC_GetCalibrationStatus(ADC1));
}

//ADC量化并存储结果
void adc_Convert()
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件启动转换
	//while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC));//等待转换完成 PS：仅ADC+DMA方式时，ADC_DR被读后EOC位自动重置，故而此步会导致死循环
}
