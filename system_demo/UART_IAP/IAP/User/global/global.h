#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "stm32f10x.h"
#include <stdio.h>

#define RX1LEN 10
#define RX2LEN 10
#define RX3LEN 1500

#define delayTime_S(a)				a*4

extern u16 Rx1Num;	
extern u16 Rx2Num;
extern u16 Rx3Num;
extern u8 Rx1Buf[];
extern u8 Rx2Buf[];
extern u8 Rx3Buf[];

extern u8 volatile  rcv_usart1_str_flag;			//串口数据接收启动标记
extern u8 volatile  rcv_usart1_end_flag;			//串口数据接收结束标记
extern u8 volatile  rcv_usart1_over_count;		//数据接收时间溢出标记
extern u16 volatile  rcv_usart1_dat_length;		//串口数据接收长度
/*usart2 send start and end flags & send dwell time counter */
extern u8 volatile  rcv_usart2_str_flag;			//串口数据接收启动标记
extern u8 volatile  rcv_usart2_end_flag;			//串口数据接收结束标记
extern u8 volatile  rcv_usart2_over_count;		//数据接收时间溢出标记
extern u16 volatile  rcv_usart2_dat_length;		//串口数据接收长度
/*usart3 send start and end flags & send dwell time counter */
extern u8 volatile  rcv_usart3_str_flag;			//串口数据接收启动标记
extern u8 volatile  rcv_usart3_end_flag;			//串口数据接收结束标记
extern u8 volatile  rcv_usart3_over_count;		//数据接收时间溢出标记
extern u16 volatile  rcv_usart3_dat_length;		//串口数据接收长度

void Per250msEventHandler(void);
void DO_USART3_232(void);
#endif
