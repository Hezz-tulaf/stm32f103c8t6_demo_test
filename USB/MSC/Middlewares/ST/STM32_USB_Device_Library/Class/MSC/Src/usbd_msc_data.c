/**
  ******************************************************************************
  * @file    usbd_msc_data.c
  * @author  MCD Application Team
  * @brief   This file provides all the vital inquiry pages and sense data.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2015 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                      www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* BSPDependencies
- "stm32xxxxx_{eval}{discovery}{nucleo_144}.c"
- "stm32xxxxx_{eval}{discovery}_io.c"
- "stm32xxxxx_{eval}{discovery}{adafruit}_sd.c"
EndBSPDependencies */

/* Includes ------------------------------------------------------------------*/
#include "usbd_msc_data.h"


/** @addtogroup STM32_USB_DEVICE_LIBRARY
  * @{
  */


/** @defgroup MSC_DATA
  * @brief Mass storage info/data module
  * @{
  */

/** @defgroup MSC_DATA_Private_TypesDefinitions
  * @{
  */
/**
  * @}
  */


/** @defgroup MSC_DATA_Private_Defines
  * @{
  */
/**
  * @}
  */


/** @defgroup MSC_DATA_Private_Macros
  * @{
  */
/**
  * @}
  */


/** @defgroup MSC_DATA_Private_Variables
  * @{
  */


/* USB Mass storage Page 0 Inquiry Data */
const uint8_t  MSC_Page00_Inquiry_Data[] =
{
  0x00,
  0x00,
  0x00,
  (3),
  0x00,
  0x80,
  0x83
};
/* USB Mass storage sense 6  Data */
const uint8_t  MSC_Mode_Sense6_data[] =
{
  0x03,  // 模式数据长度 = 3字节（不包括本字节和下一页的字节）
  0x00,  // 介质类型 = 0（标准介质）
  0x00,  // 设备特定参数（如写保护等）
  0x08,  // 块描述符长度 = 8字节
  // 块描述符开始（8字节）
  0x00,  // 保留
  0x00,  // 保留
  0x00,  // 保留
  0x00,  // 保留
  0x00,  // 块数量（MSB）
  0x00,  // 块数量
  0x00,  // 块数量
  0x16,  // 块数量（LSB）- 设为0表示不指定
  0x02,  // 块大小（MSB）= 0x0200 = 512字节
  0x00   // 块大小（LSB）
};
/* USB Mass storage sense 10  Data */
const uint8_t  MSC_Mode_Sense10_data[] =
{
  0x00,  // 模式数据长度（MSB）
  0x0A,  // 模式数据长度（LSB）= 10字节
  0x00,  // 介质类型 = 0（标准介质）
  0x00,  // 设备特定参数
  0x00,  // 长LBA标志等
  0x00,  // 保留
  0x08,  // 块描述符长度 = 8字节
  // 块描述符开始（8字节）
  0x00,  // 保留
  0x00,  // 保留
  0x00,  // 保留
  0x00,  // 保留
  0x00,  // 块数量（MSB）
  0x00,  // 块数量
  0x00,  // 块数量
  0x16,  // 块数量（LSB）- 设为0表示不指定
  0x02,  // 块大小（MSB）= 0x0200 = 512字节
  0x00   // 块大小（LSB）
};
/**
  * @}
  */


/** @defgroup MSC_DATA_Private_FunctionPrototypes
  * @{
  */
/**
  * @}
  */


/** @defgroup MSC_DATA_Private_Functions
  * @{
  */

/**
  * @}
  */


/**
  * @}
  */


/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
