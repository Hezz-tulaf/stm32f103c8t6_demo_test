#ifndef __BSP_CTR_H
#define __BSP_CTR_H

#include "stm32f10x.h"
#include "systick.h"

/*板级控制端口GPIO初始化*/
//LCD电源控制IO
#define LCD_CTR_GPIO_PIN  		GPIO_Pin_15
#define LCD_CTR_GPIO_PORT  		GPIOA
#define LCD_POWER_ON					GPIO_SetBits(LCD_CTR_GPIO_PORT, LCD_CTR_GPIO_PIN);
#define LCD_POWER_OFF   			GPIO_ResetBits(LCD_CTR_GPIO_PORT, LCD_CTR_GPIO_PIN);

//RS485EN IO
#define RS485_EN_GPIO_PIN  		GPIO_Pin_1
#define RS485_EN_GPIO_PORT  	GPIOA
#define RS485_TX_EN						{GPIO_SetBits(RS485_EN_GPIO_PORT, RS485_EN_GPIO_PIN);SysTick_Delay_Us(100);}
#define RS485_RX_EN   				{SysTick_Delay_Us(200);GPIO_ResetBits(RS485_EN_GPIO_PORT, RS485_EN_GPIO_PIN);}

//气动控制 IO
#define SW_START_GPIO_PIN  		GPIO_Pin_4	//下压检测IO口，默认外部上拉
#define SW_START_GPIO_PORT  	GPIOB
#define SW_STOP_GPIO_PIN  		GPIO_Pin_6	//急停检测IO口，默认外部上拉
#define SW_STOP_GPIO_PORT  		GPIOB
#define DCF_EN_GPIO_PIN  			GPIO_Pin_5	//气动启动IO口，输出
#define DCF_EN_GPIO_PORT  		GPIOB

#define READ_SW_START_STA			GPIO_ReadInputDataBit(SW_START_GPIO_PORT, SW_START_GPIO_PIN)
#define READ_SW_STOP_STA   		GPIO_ReadInputDataBit(SW_STOP_GPIO_PORT, SW_STOP_GPIO_PIN)
#define DCF_EN_HIGH						GPIO_SetBits(DCF_EN_GPIO_PORT, DCF_EN_GPIO_PIN);
#define DCF_EN_LOW   					GPIO_ResetBits(DCF_EN_GPIO_PORT, DCF_EN_GPIO_PIN);

//光电开关 IO
#define PhotoSwitch_GPIO_PIN  GPIO_Pin_14	//光电开关IO口，默认外部上拉
#define PhotoSwitch_GPIO_PORT GPIOB
#define READ_PhotoSwitch_STA	GPIO_ReadInputDataBit(PhotoSwitch_GPIO_PORT, PhotoSwitch_GPIO_PIN)

void BSP_CTR_Config(void);

#endif

