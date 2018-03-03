#include <usart.h>
/***串口模块***
功能：完成串口USART1的数据双向收发
思路：
(1)串口时钟使能：RCC_APBxPeriphClockCmd();
    GPIO时钟使能：RCC_AHBxPeriphClockCmd();
(2)引脚复用映射：GPIO_PinAFConfig();
(3)GPIO端口模式配置：GPIO_Init(); 模式配置为GPIO_Mode_AF
(4)串口参数初始化：USART_Init();
(5)开启中断并且初始化NVIC（如果需要开启中断才需要这个步骤）
    NVIC_Init();
    USART_ITConfig();
(6)使能串口：USART_Cmd();
(7)编写中断处理函数：USARTx_IRQHandler();
(8)串口数据收发：
    void USART_SendData();//发送数据到串口，DR
    uint16_t USART_ReceiveData();//接收数据，从DR读取接收的数据
(9)串口传输状态获取：
    FlagStatus USART_GetFlagStatus();
    void USART_ClearITPendingBit()
*/
void usart_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART1, &USART_InitStruct);
    USART_Cmd(USART1, ENABLE);
}

void usart_SendString(USART_TypeDef* USARTx, uint8_t *TX_string)
{
    while(*TX_string != '\0')
    {
        USART_SendData(USARTx, *(TX_string++));
        while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
    }
}
