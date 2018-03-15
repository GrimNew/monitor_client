#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stdio.h>

extern __IO uint16_t ADC_ResaultBuffer[3];

void usart_Init(void);
void usart_Calculate(char **buffer);
void usart_SendString(USART_TypeDef* USARTx, char *TX_string);
