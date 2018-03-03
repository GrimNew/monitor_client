#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void usart_Init(void);
void usart_SendString(USART_TypeDef* USARTx, uint8_t *TX_string);
