#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>

void usart_Init();
void usart_SendString(USART_TypeDef* USARTx,u32 *Tx_string);