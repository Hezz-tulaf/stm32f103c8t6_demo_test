#ifndef	__LED_H
#define	__LED_H

#include "stm32f10x.h"

#define RUN1_GPIO_PIN  		GPIO_Pin_4
#define RUN1_GPIO_PORT  	GPIOA

#define RUN2_GPIO_PIN  		GPIO_Pin_5
#define RUN2_GPIO_PORT  	GPIOA

#define LED1_GPIO_PIN  		GPIO_Pin_8
#define LED1_GPIO_PORT  	GPIOA

#define LED2_GPIO_PIN  		GPIO_Pin_15
#define LED2_GPIO_PORT  	GPIOB

#define ON   1
#define OFF  0	

#define LED_RUN1(a)		if(a)GPIO_ResetBits(RUN1_GPIO_PORT, RUN1_GPIO_PIN);\
												else GPIO_SetBits(RUN1_GPIO_PORT, RUN1_GPIO_PIN);

#define LED_RUN2(a)		if(a)GPIO_ResetBits(RUN2_GPIO_PORT, RUN2_GPIO_PIN);\
												else GPIO_SetBits(RUN2_GPIO_PORT, RUN2_GPIO_PIN);
										
#define LED1(a)				if(a)GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);\
												else GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
										
#define LED2(a)				if(a)GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);\
												else GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
									
#define LED_RUN1_TOGGLE  	{RUN1_GPIO_PORT->ODR ^= RUN1_GPIO_PIN;}
#define LED_RUN2_TOGGLE  	{RUN2_GPIO_PORT->ODR ^= RUN2_GPIO_PIN;}
#define LED1_TOGGLE  			{LED1_GPIO_PORT->ODR ^= LED1_GPIO_PIN;}
#define LED2_TOGGLE  			{LED2_GPIO_PORT->ODR ^= LED2_GPIO_PIN;}

void LED_GPIO_Config(void);
#endif

