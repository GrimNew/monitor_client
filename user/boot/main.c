#include "stm32f10x.h"
#include <usart.h>
#include <delay.h>

int main(void)
{
	uint8_t sendbuffer[10] = "ABC";
	delay_Init();
	usart_Init();
    while(1)
    {
		usart_SendString(USART1, sendbuffer);
		delay_nms(1000);
    }
}
