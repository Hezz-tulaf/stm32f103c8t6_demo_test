#include "led.h"

void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;									//配置为推挽输出
	GPIO_InitStruct.GPIO_Pin = RUN1_GPIO_PIN | RUN2_GPIO_PIN | LED1_GPIO_PIN;		//选择pin
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;								//速度50M
	GPIO_Init(RUN1_GPIO_PORT, &GPIO_InitStruct);									//初始化GPIO
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;									//配置为推挽输出
	GPIO_InitStruct.GPIO_Pin = LED2_GPIO_PIN;		//选择pin
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;								//速度50M
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStruct);									//初始化GPIO
	
	LED_RUN1(1);
	LED_RUN2(1);
	LED1(0);
	LED2(0);
}

