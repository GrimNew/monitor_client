#include <led.h>
void led_Init(){
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD, ENABLE);//

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;//
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
//	GPIO_Init(GPIOD, &GPIO_InitStruct);
}

//
void led_Flash(){
	GPIO_SetBits(GPIOA ,GPIO_Pin_8);
	delay_nms(200);
	GPIO_ResetBits(GPIOA ,GPIO_Pin_8);
//	GPIO_SetBits(GPIOD ,GPIO_Pin_2);
//	delay_nms(1000);
//	GPIO_ResetBits(GPIOD ,GPIO_Pin_2);
}
