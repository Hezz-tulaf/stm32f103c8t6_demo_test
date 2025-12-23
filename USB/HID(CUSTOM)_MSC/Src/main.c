/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"
#include "gpio.h"
#include "usbd_customhid.h"

#include "usart.h"
#include "sys.h"
#include "delay.h"
#include "keyboard_mouse_uart.h"



void SystemClock_Config(void);
/* USER CODE BEGIN PFP */


extern USBD_HandleTypeDef hUsbDeviceFS;

/* 简单相对鼠标操作 */
typedef struct {
    uint8_t buttons;  // 按钮状态
    int8_t  x;        // X轴移动 (-127~127)
    int8_t  y;        // Y轴移动 (-127~127)
    int8_t  wheel;    // 滚轮 (-127~127)
} mouse_report_t;

void rel_mouse_send(uint8_t buttons, int8_t x, int8_t y, int8_t wheel) //x为左右   y为上下
{
    mouse_report_t report;
    report.buttons = buttons;
    report.x = x;
    report.y = y;
    report.wheel = wheel;

    USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&report, sizeof(report),2);
}

/* 简单键盘操作 */
typedef struct {
    uint8_t modifier;   // 修饰键 (BYTE0)
    uint8_t reserved;   // 保留 (BYTE1)
    uint8_t keycode[6]; // 按键码 (BYTE2-BYTE7)
} keyboard_report_t;

void keyboard_reset()
{
    keyboard_report_t report = {0};
    while(USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&report, 8, 1)!= USBD_OK);
}

void keyboard_send(int8_t key_sp,int8_t key1,int8_t key2,int8_t key3,int8_t key4,int8_t key5,int8_t key6)
{
    keyboard_report_t report;

    report.modifier = key_sp;
    report.reserved = 0;
    report.keycode[0] = key1;
    report.keycode[1] = key2;
    report.keycode[2] = key3;
    report.keycode[3] = key4;
    report.keycode[4] = key5;
    report.keycode[5] = key6;

    while(USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, (uint8_t*)&report, 8, 1)!= USBD_OK);

    HAL_Delay(2);  //延时是必要的
    keyboard_reset(); //发送0  表示键盘弹起 否则一直相应之前的键值
    HAL_Delay(2);
}


int main(void)
{
    HAL_Init();
    SystemClock_Config();//时钟需要根据所使用的模块配置 如看门狗，usb等

    MX_USB_DEVICE_Init();

    uart1_init(115200);


	printf("usb hid msc device\r\n");

    while (1)
    {
		parse_and_execute_command();
		HAL_Delay(1000);
		rel_mouse_send(0,10,10,0);
    }
}


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;//开启独立看门狗需要开启这个时钟LSI
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;//开启独立看门狗需要开启这个时钟
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

