/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
/* USER CODE BEGIN 0 */
#include "stdio.h"
#include "sys.h"
#include <stdlib.h>
#include <string.h>
#include "fifo.h"
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
uint8_t g_rx_buffer; // 全局变量，用于接收一个字符

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* USER CODE BEGIN USART1_MspInit 0 */

	/* USER CODE END USART1_MspInit 0 */
	/* USART1 clock enable */
	__HAL_RCC_USART1_CLK_ENABLE();

	__HAL_RCC_GPIOA_CLK_ENABLE();
	/**USART1 GPIO Configuration
	PA9     ------> USART1_TX
	PA10     ------> USART1_RX
	*/
	GPIO_InitStruct.Pin = GPIO_PIN_9;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USART1 interrupt Init */
	HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	/* USER CODE BEGIN USART1_MspInit 1 */

	/* USER CODE END USART1_MspInit 1 */
    
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
	/* USER CODE BEGIN USART1_MspDeInit 0 */

	/* USER CODE END USART1_MspDeInit 0 */
	/* Peripheral clock disable */
	__HAL_RCC_USART1_CLK_DISABLE();

	/**USART1 GPIO Configuration
	PA9     ------> USART1_TX
	PA10     ------> USART1_RX
	*/
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

	/* USART1 interrupt Deinit */

	HAL_NVIC_DisableIRQ(USART1_IRQn);
	/* USER CODE BEGIN USART1_MspDeInit 1 */

	/* USER CODE END USART1_MspDeInit 1 */
}

/* USER CODE BEGIN 1 */
//加入以下代码,支持printf函数,而不需要选择use MicroLIB
#if 1
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
    int handle;

};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
    x = x;
}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
    while((USART1->SR&0X40)==0);//循环发送,直到发送完毕
    USART1->DR = (u8) ch;
    return ch;
}
#endif

void uart1_init(u32 bound)
{
    //UART 初始化设置
    huart1.Instance = USART1;
    huart1.Init.BaudRate = bound;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }

    __HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	// 使用HAL库函数启动接收中断（但是会读取接收第一次的字符）
	HAL_UART_Receive_IT(&huart1, &g_rx_buffer, 1);
}

void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart1);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
