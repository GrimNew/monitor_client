#include <usart.h>
/*
USART配置以及串口收发
*/
void usart_Init(void)
{
	USART_InitTypeDef USART_InitStructure;
	
	//115200波特率，8b数据位，1停止位，收发模式
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
}

void usart_Calculate(char **buffer)
{
	float analog = 0.0;
	int i;

	for(i = 0; i < 3; i ++)
	{
		analog = ADC_ResaultBuffer[i] * (3.3 / 4096);//计算电压值
		sprintf(buffer[i], "%5.3f",analog);
	}
}

//SendString发送字符串：查询USART_FLAG_TXE位完成数据发送
void usart_SendString(USART_TypeDef* USARTx, char *TX_string)
{
	while(*TX_string != '\0')
	{
		USART_SendData(USARTx, *(TX_string++));
		while(!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));
	}
}
