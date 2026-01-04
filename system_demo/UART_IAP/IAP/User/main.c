#include "main.h"
#include "global.h"
#include "bsp_ctr.h"
#include "usart.h"
#include "timer.h"
#include "systick.h"
#include "clkconfig.h"
#include "led.h"

/*
bootload   app1      app2      total
 0x3000   0x6800    0x6800    0x10000
   12k      26k       26k       64k
*/

#define IAP_OFFSET 		0x3000
#define APP_SIZE		0x6800
#define APP2_OFFSET 	(IAP_OFFSET+APP_SIZE)

//函数运行结构体成员
static TASK_COMPONENTS TaskComps[] = 
{
	{0, 250, 	250,Per250msEventHandler},
	{0, 10, 	10,DO_USART3_232},
};

//时间标志处理
void TaskReMarks(void)
{
	unsigned char i = 0; 
	
	for(i = 0; i< TASKS_MAX; i++)
	{
		if(TaskComps[i].Timer)
		{
			TaskComps[i].Timer--;
			if(TaskComps[i].Timer == 0)
			{
				TaskComps[i].Timer = TaskComps[i].ItvTimer;
				TaskComps[i].Run = 1;   //任务可以运行
			}
		}
	}
}

//任务标志处理
void TaskProcess(void)
{
	unsigned char i = 0;

	for(i = 0;i < TASKS_MAX;i++)
	{
		if(TaskComps[i].Run)
		{
			TaskComps[i].TaskHook();
			TaskComps[i].Run = 0;
		}
	}
}

/*******************************************************************************
* Function Name  : Peripheral_Init
* Description    : 外设初始化，IO，USART,TIMER等
* Input          : None.
* Return         : None.
*******************************************************************************/
void Peripheral_Init(void)
{
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x3000);
	HSE_SetSysClock(RCC_PLLMul_9);
	BSP_CTR_Config();
	LED_GPIO_Config();
	Timer2_Config();				//1ms定时中断
	USART1_Config(115200);	//LCD_COM
	USART2_Config(115200);	//485_COM
	USART3_Config(115200);	//232_COM

#if DEBUG_MODE
  	printf("DEBUG-->  APP V1.0 run!  	\r\n");
#endif
} 

/*******************************************************************************
* Function Name  : main
* Description    : 主函数
* Input          : None.
* Return         : None.
*******************************************************************************/
int main(void)
{
	Peripheral_Init();				//外设初始化

	while (1)
	{
		TaskProcess();					//任务轮询主体
	}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/




