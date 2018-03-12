#include "stm32f10x.h"
#include <usart.h>
#include <delay.h>
#include <led.h>

int main(void)
{
	uint8_t sendbuffer[10] = "ABC";
	delay_Init();
	led_Init();
	usart_Init();
	
    while(1)
    {
			usart_SendString(USART1, sendbuffer);
			led_Flash();
    }
}
