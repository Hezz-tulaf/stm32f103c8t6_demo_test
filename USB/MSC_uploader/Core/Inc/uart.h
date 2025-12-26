#ifndef __UART_H
#define __UART_H
#include "stdio.h"
#include "main.h" 

extern UART_HandleTypeDef huart1;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);

/* USER CODE BEGIN Prototypes */
#define USART_REC_LEN  			200  		//定义最大接收字节数 200
#define EN_USART1_RX 			1			//使能（1）/禁止（0）串口1接收

extern UART_HandleTypeDef UART1_Handler; 	//UART句柄

#define RXBUFFERSIZE   1 					//缓存大小
extern unsigned char aRx1_Buffer[RXBUFFERSIZE];			//HAL库USART接收Buffer

//如果想串口中断接收，请不要注释以下宏定义
void MX_UART_Init(void);
/* USER CODE END Prototypes */
void array_printf(unsigned char*data, unsigned int len);

#endif

