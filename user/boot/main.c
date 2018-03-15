#include <rcc.h>
#include <gpio.h>
#include <delay.h>
#include <usart.h>
#include <dma.h>
#include <adc.h>
#include <led.h>

__IO uint16_t ADC_ResaultBuffer[3];

int main(void)
{
	char *sendbuffer[10] = {"123","456","789"};
	int i;
	
	rcc_Init();
	gpio_Init();
	delay_Init();
	usart_Init();
	dma_Init();
	adc_Init();
	
	while(1)
	{
		adc_Convert();
		dma_Judgement();
		usart_Calculate(sendbuffer);
		for(i = 0; i < 3; i ++)
		{
			usart_SendString(USART1, sendbuffer[i]);
		}
		led_Flash();
		delay_nms(3000);
	}
}
