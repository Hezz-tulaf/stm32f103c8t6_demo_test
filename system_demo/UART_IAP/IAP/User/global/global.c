#include "global.h"
#include "bsp_ctr.h"
#include "main.h"
#include "usart.h"
#include "led.h"
#include "bsp_ctr.h"
#include "IAP.h"

u16 Rx1Num;
u16 Rx2Num;
u16 Rx3Num;
u8 Rx1Buf[RX1LEN];
u8 Rx2Buf[RX2LEN];
u8 Rx3Buf[RX3LEN];
/*usart1 send start and end flags & send dwell time counter */
u8 volatile  rcv_usart1_str_flag   = 0;			//串口数据接收启动标记
u8 volatile  rcv_usart1_end_flag   = 0;			//串口数据接收结束标记
u8 volatile  rcv_usart1_over_count = 0;			//数据接收时间溢出标记
u16 volatile  rcv_usart1_dat_length = 0;		//串口数据接收长度
/*usart2 send start and end flags & send dwell time counter */
u8 volatile  rcv_usart2_str_flag   = 0;			//串口数据接收启动标记
u8 volatile  rcv_usart2_end_flag   = 0;			//串口数据接收结束标记
u8 volatile  rcv_usart2_over_count = 0;			//数据接收时间溢出标记
u16 volatile  rcv_usart2_dat_length = 0;		//串口数据接收长度
/*usart3 send start and end flags & send dwell time counter */
u8 volatile  rcv_usart3_str_flag   = 0;			//串口数据接收启动标记
u8 volatile  rcv_usart3_end_flag   = 0;			//串口数据接收结束标记
u8 volatile  rcv_usart3_over_count = 0;			//数据接收时间溢出标记
u16 volatile  rcv_usart3_dat_length = 0;		//串口数据接收长度

u8 GreenLEDtick=0;
u8 RedLEDtick=0;
u16 OTA_RXlen=0;

//任务列队：串口3处理程序
void DO_USART3_232(void)
{
	if(rcv_usart3_end_flag)
	{
		rcv_usart3_end_flag=0;
		OTA_RXlen = Rx3Num;
		Rx3Num=0;
		Receive_Packet(Rx3Buf,OTA_RXlen);
	}
}

//任务列队：串口2处理程序
void DO_USART2_485(void)
{

}

//任务列队：串口1处理程序
void DO_USART1_LCD(void)
{

}

/*******************************************************************************
* Function Name  : Per250msEventHandler
* Description    : 250ms定时处理函数,主要处理一些定时执行的功能
* Input          : None.
* Return         : None.
*******************************************************************************/
void Per250msEventHandler(void)
{
	if(++GreenLEDtick >= 2)
	{
		GreenLEDtick = 0;
		LED_RUN2_TOGGLE;
	}

	if(++RedLEDtick >= 2)
	{
		RedLEDtick = 0;
		LED_RUN1_TOGGLE;
	} 
	
	IAP_Send_C();
}

