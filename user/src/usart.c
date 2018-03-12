#include <usart.h>
/***串口模块***
功能：完成串口USART1的数据双向收发
思路：
(1)USART1和GPIOA时钟使能：RCC_APBxPeriphClockCmd()
(2)GPIO端口配置：PA9推挽复用输出，PA10浮空输入
(3)USAR1参数初始化：115200波特率，8b数据位，1停止位，收发模式
(4)SendString发送字符串：查询USART_FLAG_TXE位完成数据发送
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
