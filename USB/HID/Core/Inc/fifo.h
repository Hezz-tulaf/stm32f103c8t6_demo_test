#ifndef _FIFO_H_
#define _FIFO_H_

#include<stdio.h>
#include "string.h"
#include "main.h"

#define FIFO_SIZE 256

struct FIFOTypeDef
{
    uint8_t Buf[FIFO_SIZE];	    //定义缓冲区，大小用FIFO_SIZE定义
    volatile uint32_t Read;	//定义读取指针
    volatile uint32_t Write;   //定义写入指针
};

extern struct FIFOTypeDef USART1_fifo;
extern struct FIFOTypeDef USART2_fifo;

void FIFO_Init(struct FIFOTypeDef *FIFO);
void U1_PutChar(uint8_t c);
uint8_t U1_GetChar(uint8_t *c);
void U2_PutChar(uint8_t c);
uint8_t U2_GetChar(uint8_t *c);

#endif
