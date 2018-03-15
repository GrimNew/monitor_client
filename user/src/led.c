#include <led.h>
/*
LED闪烁，心跳表征MCU内程序正常运行
*/
void led_Flash(){
	GPIO_SetBits(GPIOA ,GPIO_Pin_8);
	delay_nms(500);
	GPIO_ResetBits(GPIOA ,GPIO_Pin_8);
//	GPIO_SetBits(GPIOD ,GPIO_Pin_2);
//	delay_nms(1000);
//	GPIO_ResetBits(GPIOD ,GPIO_Pin_2);
}
