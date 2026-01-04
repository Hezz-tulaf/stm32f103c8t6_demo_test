#ifndef __SYS_PARA_H__
#define __SYS_PARA_H__

#include "stm32f10x.h"

typedef struct
{
	u8 hour;
	u8 min;
	u8 sec;
	u16 year;
	u8 month;
	u8 date;
}_s_Time;

//程序运行结构体
typedef struct _TASK_COMPONENTS
{
    __IO uint32_t Run;                 	//程序运行标志  		Run    0-不运行  1-运行
    __IO uint32_t Timer;               	//程序运行间隔时间
    __IO uint32_t ItvTimer;            	//重装载
    void (*TaskHook)(void);    					//要运行的任务函数
}TASK_COMPONENTS;


#endif


