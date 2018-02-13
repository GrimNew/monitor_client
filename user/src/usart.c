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
void usart_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);//使能串口和输入输出时钟
}