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
#include "uart.h"
#include "main.h"
#include "stdio.h"
#include "fifo.h"

UART_HandleTypeDef huart1;

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
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USART1 interrupt Init */
	HAL_NVIC_SetPriority(USART1_IRQn, 2, 2);
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
    //直到发送完毕
	while(__HAL_UART_GET_FLAG(&huart1, UART_FLAG_TC) == RESET){}

    huart1.Instance->DR = (unsigned char) ch;
    return ch;
}
#endif


//注意,读取USARTx->SR能避免莫名其妙的错误
unsigned char USART1_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.

unsigned char aRx1_Buffer[RXBUFFERSIZE];//HAL库使用的串口接收缓冲

//UART_HandleTypeDef UART1_Handler; //UART句柄

//初始化IO 串口1
//bound:波特率
void MX_UART_Init(void)
{
    //UART 初始化设置
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
        Error_Handler();
    }				    //HAL_UART_Init()会使能UART1
    __HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
    HAL_UART_Receive_IT(&huart1, (unsigned char *)aRx1_Buffer, RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}


void USART1_IRQHandler(void)
{
    /* USER CODE BEGIN USART1_IRQn 0 */
    unsigned char temp=0;
    if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_RXNE) != RESET)   //idle标志被置位
    {

        temp= huart1.Instance->DR;    //读取数据寄存器中的数据
        huart1.Instance->SR;    //清除状态寄存器SR,读取SR寄存器可以实现清除SR寄存器的功能

//        while(QRXIn(&uart1_RX_fifo,temp)!=1);
//---------------------------------------------------------------------------------
        U1_PutChar(temp);     //修改串口缓存区，2020/10/16
    } else if(__HAL_UART_GET_FLAG(&huart1,UART_FLAG_ORE) == SET)
    {
        __HAL_UART_CLEAR_FLAG(&huart1,UART_FLAG_ORE);
        huart1.Instance->DR;
    } else {
//---------------------------------------------------------------------------------
        /* USER CODE END USART1_IRQn 0 */
        HAL_UART_IRQHandler(&huart1);

        __HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
        HAL_UART_Receive_IT(&huart1, (unsigned char *)aRx1_Buffer, RXBUFFERSIZE);//该函数会开启接收中断：标志位UART_IT_RXNE，并且设置接收缓冲以及接收缓冲接收最大数据量
    }
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
