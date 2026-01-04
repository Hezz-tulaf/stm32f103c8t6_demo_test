/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x.h"
#include <stdio.h>
#include "global.h"
#include "main.h"
#include "IAP.h"

void NMI_Handler(void)
{
	
}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
#if DEBUG_MODE
	printf("Hard Fault!\r\n");
#endif
	NVIC_SystemReset();
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
}

// 串口中断服务函数
void USART1_IRQHandler(void)
{	
	if(USART_GetITStatus(USART1, USART_IT_RXNE)==SET)		   	//判断，一旦接收到数据
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);		   	//清除中断标志位

		rcv_usart1_str_flag=1;					               				//串口数据接收标志置1
		rcv_usart1_over_count=0;			                 				//每来一字节溢出计数标志清0

		if(Rx1Num < RX1LEN)
			Rx1Buf[Rx1Num++]= USART_ReceiveData(USART1);
		else
			Rx1Buf[RX1LEN-1]= USART_ReceiveData(USART1);
	}
	/*溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题*/
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(USART1,USART_FLAG_ORE);
		USART_ReceiveData(USART1);
	}
}

// 串口中断服务函数
void USART2_IRQHandler(void)
{
	if(USART_GetITStatus(USART2, USART_IT_RXNE)==SET)		   //判断，一旦接收到数据
	{
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);		   //清除中断标志位

		rcv_usart2_str_flag=1;					               //串口数据接收标志置1
		rcv_usart2_over_count=0;			                 //每来一字节，等待超时计数标志清0

		if(Rx2Num < RX2LEN)
			Rx2Buf[Rx2Num++] = USART_ReceiveData(USART2);
		else
			Rx2Buf[RX2LEN-1]= USART_ReceiveData(USART2);
	}
	/*溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题*/
	if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(USART2,USART_FLAG_ORE);
		USART_ReceiveData(USART2);
	}
}

//串口中断服务函数，接受上位机数据
void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3, USART_IT_RXNE)==SET)		   //判断，一旦接收到数据
	{
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);		   //清除中断标志位

		rcv_usart3_str_flag=1;					               //串口数据接收标志置1
		rcv_usart3_over_count=0;			                 //每来一字节，等待超时计数标志清0
		
		if(Rx3Num < RX3LEN)
			Rx3Buf[Rx3Num++] = USART_ReceiveData(USART3);
		else
			Rx3Buf[RX3LEN-1] = USART_ReceiveData(USART3);
	}
	/*溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题*/
	if(USART_GetFlagStatus(USART3,USART_FLAG_ORE)==SET)
	{
		USART_ClearFlag(USART3,USART_FLAG_ORE);
		USART_ReceiveData(USART3);
	}
}

void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

		if(rcv_usart1_str_flag)					      //接收到了串口数据
		{
			if(rcv_usart1_over_count < 10)
				rcv_usart1_over_count++;			    //每一个数据接收完了最多等待10ms
			else
			{
				rcv_usart1_str_flag=0;            //超过10ms，清标志位
				rcv_usart1_end_flag=1;				    //数据接收结束标志位置1
			}
		}
		if(rcv_usart2_str_flag)					      //接收到了串口数据
		{
			if(rcv_usart2_over_count < 10)
				rcv_usart2_over_count++;			    //每一个数据接收完了最多等待10ms
			else
			{
				rcv_usart2_str_flag=0;            //超过10ms，清标志位
				rcv_usart2_end_flag=1;				    //数据接收结束标志位置1
			}
		}
		if(rcv_usart3_str_flag)					      //接收到了串口数据
		{
			if(rcv_usart3_over_count < 10)
				rcv_usart3_over_count++;			    //每一个数据接收完了最多等待10ms
			else
			{
				rcv_usart3_str_flag=0;            //超过10ms，清标志位
				rcv_usart3_end_flag=1;				    //数据接收结束标志位置1
			}
		}

		if(IAP_Para.IAP_Status)
		{
			IAP_Para.IAP_Tick++;
			if(IAP_Para.IAP_Tick >= IAP_TIMEOUT)
			{
				Reset_IAP();
			}
		}
		
		//任务标志处理
    TaskReMarks();
  }
}


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
