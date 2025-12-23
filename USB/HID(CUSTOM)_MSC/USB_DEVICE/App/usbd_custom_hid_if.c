/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v2.0_Cube
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t KEYBOARD_CUSTOM_HID_ReportDesc_FS[KEYBOARD_USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  //-------------键盘部分报告描述符----------------  
    //表示用途页为通用桌面设备  
    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)  
  
    //表示用途为键盘  
    0x09, 0x06,                    // USAGE (Keyboard)   
       
    //表示应用集合，必须要以END_COLLECTION来结束它，见最后的END_COLLECTION  
    0xa1, 0x01,                    // COLLECTION (Application)  
       
    //报告ID（报告ID 0是保留的）  
//    0x85, 0x01, //Report ID (1)  
       
    //表示用途页为按键  
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)  
  
    //用途最小值，这里为左ctrl键  
    0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)  
    //用途最大值，这里为右GUI键，即window键  
    0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)  
    //逻辑最小值为0  
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)  
    //逻辑最大值为1  
    0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)  
    //报告大小（即这个字段的宽度）为1bit，所以前面的逻辑最小值为0，逻辑最大值为1  
    0x75, 0x01,                    //   REPORT_SIZE (1)  
    //报告的个数为8，即总共有8个bits  
    0x95, 0x08,                    //   REPORT_COUNT (8)  
    //输入用，变量，值，绝对值。像键盘这类一般报告绝对值，  
    //而鼠标移动这样的则报告相对值，表示鼠标移动多少  
    0x81, 0x02,                    //   INPUT (Data,Var,Abs)  
    //上面这这几项描述了一个输入用的字段，总共为8个bits，每个bit表示一个按键  
    //分别从左ctrl键到右GUI键。这8个bits刚好构成一个字节，它位于报告的第一个字节。  
    //它的最低位，即bit-0对应着左ctrl键，如果返回的数据该位为1，则表示左ctrl键被按下，  
    //否则，左ctrl键没有按下。最高位，即bit-7表示右GUI键的按下情况。中间的几个位，  
    //需要根据HID协议中规定的用途页表（HID Usage Tables）来确定。这里通常用来表示  
    //特殊键，例如ctrl，shift，del键等   
  
    //这样的数据段个数为1  
    0x95, 0x01,                    //   REPORT_COUNT (1)  
    //每个段长度为8bits  
    0x75, 0x08,                    //   REPORT_SIZE (8)  
    //输入用，常量，值，绝对值  
    0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)  
       
    //上面这8个bit是常量，设备必须返回0  
  
    //这样的数据段个数为5  
    0x95, 0x05,                    //   REPORT_COUNT (5)  
    //每个段大小为1bit  
    0x75, 0x01,                    //   REPORT_SIZE (1)  
    //用途是LED，即用来控制键盘上的LED用的，因此下面会说明它是输出用  
    0x05, 0x08,                    //   USAGE_PAGE (LEDs)  
    //用途最小值是Num Lock，即数字键锁定灯  
    0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)  
    //用途最大值是Kana，这个是什么灯我也不清楚^_^  
    0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)  
    //如前面所说，这个字段是输出用的，用来控制LED。变量，值，绝对值。  
    //1表示灯亮，0表示灯灭  
    0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)  
  
    //这样的数据段个数为1  
    0x95, 0x01,                    //   REPORT_COUNT (1)  
    //每个段大小为3bits  
    0x75, 0x03, 
    //   REPORT_SIZE (3)  
    //输出用，常量，值，绝对  
    0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)      
    //由于要按字节对齐，而前面控制LED的只用了5个bit，  
    //所以后面需要附加3个不用bit，设置为常量。  
    
  
    //报告个数为6  
    0x95, 0x06,                    //   REPORT_COUNT (6)  
    //每个段大小为8bits  
    0x75, 0x08,                    //   REPORT_SIZE (8)  
    //逻辑最小值0  
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)  
    //逻辑最大值255  
    0x25, 0xFF,                    //   LOGICAL_MAXIMUM (255)  
    //用途页为按键  
    0x05, 0x07,                    //   USAGE_PAGE (Keyboard)  
    //使用最小值为0  
    0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))  
    //使用最大值为0x65  
    0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)  
    //输入用，变量，数组，绝对值  
    0x81, 0x00,                    //   INPUT (Data,Ary,Abs)  
    //以上定义了6个8bit宽的数组，每个8bit（即一个字节）用来表示一个按键，所以可以同时  
    //有6个按键按下。没有按键按下时，全部返回0。如果按下的键太多，导致键盘扫描系统  
    //无法区分按键时，则全部返回0x01，即6个0x01。如果有一个键按下，则这6个字节中的第一  
    //个字节为相应的键值（具体的值参看HID Usage Tables），如果两个键按下，则第1、2两个  
    //字节分别为相应的键值，以次类推。  
  
    //关集合，跟上面的对应  
    0xc0 ,                          // END_COLLECTION  
    
    /*65  包含报告ID 65  不包含63*/
    

};

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t MOUSE_CUSTOM_HID_ReportDesc_FS[MOUSE_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
   
//  //相对模式  
//    //-----------------------鼠标部分报告描述符----------------------------  
// //每行开始的第一字节为该条目的前缀，前缀的格式为：
// //D7~D4：bTag。D3~D2：bType；D1~D0：bSize。以下分别对每个条目注释。
// 
// //这是一个全局（bType为1）条目，选择用途页为普通桌面Generic Desktop Page(0x01)
// //后面跟一字节数据（bSize为1），后面的字节数就不注释了，
// //自己根据bSize来判断。
// 0x05, 0x01, // USAGE_PAGE (Generic Desktop)
// 
// //这是一个局部（bType为2）条目，说明接下来的应用集合用途用于鼠标
// 0x09, 0x02, // USAGE (Mouse)
// 
// //这是一个主（bType为0）条目，开集合，后面跟的数据0x01表示
// //该集合是一个应用集合。它的性质在前面由用途页和用途定义为
// //普通桌面用的鼠标。
// 0xa1, 0x01, // COLLECTION (Application)    //1byte报告ID +按键(3bit)+填充行(5bit)=1byte ; 坐标（16bits*2个）=4bytes；所以上报数据就是6bytes； 
// 
////  0x85,0x02,   // 报告ID (2) 

// //这是一个局部条目。说明用途为指针集合
// 0x09, 0x01, //   USAGE (Pointer)
// 
// //这是一个主条目，开集合，后面跟的数据0x00表示该集合是一个
// //物理集合，用途由前面的局部条目定义为指针集合。
// 0xa1, 0x00, //   COLLECTION (Physical)
// 
// //这是一个全局条目，选择用途页为按键（Button Page(0x09)）
// 0x05, 0x09, //     USAGE_PAGE (Button)
// 
// //这是一个局部条目，说明用途的最小值为1。实际上是鼠标左键。
// 0x19, 0x01, //     USAGE_MINIMUM (Button 1)
// 
// //这是一个局部条目，说明用途的最大值为3。实际上是鼠标中键。
// 0x29, 0x03, //     USAGE_MAXIMUM (Button 3)
// 
// //这是一个全局条目，说明返回的数据的逻辑值（就是我们返回的数据域的值啦）
// //最小为0。因为我们这里用Bit来表示一个数据域，因此最小为0，最大为1。
// 0x15, 0x00, //     LOGICAL_MINIMUM (0)
// 
// //这是一个全局条目，说明逻辑值最大为1。
// 0x25, 0x01, //     LOGICAL_MAXIMUM (1)
// 
// //这是一个全局条目，说明数据域的数量为三个。
// 0x95, 0x03, //     REPORT_COUNT (3)
// 
// //这是一个全局条目，说明每个数据域的长度为1个bit。
// 0x75, 0x01, //     REPORT_SIZE (1)
// 
// //这是一个主条目，说明有3个长度为1bit的数据域（数量和长度
// //由前面的两个全局条目所定义）用来做为输入，
// //属性为：Data,Var,Abs。Data表示这些数据可以变动，Var表示  //Var可以任意大小数据但是最小值要从0开始   Abs只能一个字节  
// //这些数据域是独立的，每个域表示一个意思。Abs表示绝对值。
// //这样定义的结果就是，第一个数据域bit0表示按键1（左键）是否按下，
// //第二个数据域bit1表示按键2（右键）是否按下，第三个数据域bit2表示
// //按键3（中键）是否按下。
// 0x81, 0x02, //     INPUT (Data,Var,Abs)
// 
// //这是一个全局条目，说明数据域数量为1个
// 0x95, 0x01, //     REPORT_COUNT (1)
// 
// //这是一个全局条目，说明每个数据域的长度为5bit。
// 0x75, 0x05, //     REPORT_SIZE (5)
// 
// //这是一个主条目，输入用，由前面两个全局条目可知，长度为5bit，
// //数量为1个。它的属性为常量（即返回的数据一直是0）。
// //这个只是为了凑齐一个字节（前面用了3个bit）而填充的一些数据
// //而已，所以它是没有实际用途的。
// 0x81, 0x03, //     INPUT (Cnst,Var,Abs)
// 0x95,0x03, // 这是一个全局条目，说明数据域的个数为3个。
//0x75,0x08, // 这是一个全局条目，说明数据域的长度为8bit。

//0x05,0x01, // 这是一个全局条目，选择用途页为普通桌面Generic Desktop Page(0x01)
//0x09,0x30, // 这是一个局部条目，说明用途为X轴
//0x09,0x31, // 这是一个局部条目，说明用途为Y轴
//0x09,0x38, // 这是一个局部条目，说明用途为滚轴
//0x15,0x81, // 这是一个全局条目，说明返回的逻辑最小为-128。
//0x25,0x7f, // 这是一个全局条目，说明返回的逻辑最大为127。
//0x81,0x06, // 这是一个主条目。标识上面的3个数据是绝对值。
//0xc0,      // 我们开了两个集合，所以要关两次。bSize为0，所以后面没数据。

//0xc0       // END_COLLECTION  

///*54 包含报告ID54   不包52 */
///****************************单点描述符结束*********************/

////绝对模式
// //=============================================================================
////【鼠标】-顶层集合（报告ID=1，报告长度=6），描述符长度=58 + 12（滚轮增加的报告描述符长度）
//    0x05, 0x01,                // Usage Page (Generic Desktop)
//    0x09, 0x02,                // Usage (Mouse)
//    0xA1, 0x01,                // Collection (Application)        【通用桌面设备：鼠标】应用集合开始
//    0x09, 0x01,                //        Usage (Pointer)        指针设备
//    0xA1, 0x00,                //        Collection (Physical)        物理集合开始

//    0x85, 0x02,                //                Report ID (2)        报告ID =2
//   
//    0x05, 0x09,                //                Usage Page (Buttons)用途页为【按键】
//    0x19, 0x01,                //                Usage Minimum (01)        用途最小值1
//    0x29, 0x03,                //                Usage Maximum (03)用途最大值3（1=左键，2=右键，3=示中键）
//    0x15, 0x00,                //                Logical Minimum (0)        逻辑最小值0
//    0x25, 0x01,                //                Logical Maximum (1)        逻辑最大值1
//    0x75, 0x01,                //                Report Size (1)        字段大小为1bit
//    0x95, 0x03,                //                Report Count (3)        这样的字段数量为3
//    0x81, 0x02,                //                Input (Data, Var, Abs)输入（变量，数值，绝对值）

//    0x75, 0x05,                //                Report Size (5)
//    0x95, 0x01,                //                Report Count (1)        填充5个bit，补足一个字节
//    0x81, 0x01,                //                Input (Constant) for padding       

//    0x05, 0x01,                //                Usage Page (Generic Desktop)        用途页为【通用桌面】
// 
///**************************************************************/ 
////      0x09,0x38,  //  Usage (wheel)    用途为滚轮
////      0x15,0x81,  // LOGICAL_MINIMUM (-127)
////      0x25,0x7f,  // LOGICAL_MAXIMUM (127)
////      
////      0x75,0x08,  // REPORT_SIZE (8)
////      0x95,0x01,   //REPORT_COUNT (1)
////      0x81,0x06,   //INPUT (Data,Var,Rel)
///**************************************************************/     

//    0x09, 0x30,                //                Usage (X)                        用途为X
//    0x09, 0x31,                //                Usage (Y)                        用途为Y
//    

//    0x15, 0x00,                //                Logical Minimum (0)             【逻辑最小值=0】
//    0x26, 0xff, 0x7f,        //                Logical_Maximum (32767)        【逻辑最大值=32767】
//    0x35, 0x00,                //                PHYSICAL_Minimum (0)        【物理最小值=0】
//    0x46, 0xff, 0x7f,        //                PHYSICAL_Maximum (32767)        【物理最大值=32767】

//    0x75, 0x10,                //                Report Size (16)                【16位量】
//    0x95, 0x02,                //                Report Count (2)                【这样的字段数量为2】
//    0x81, 0x02,                //                 Input (Data, Var, Abs)        【输入（变量，数值，绝对值）】

//    0xC0,                //        End Collection (Physical) 物理集合结束
//    0xC0,                // End Collection (Application) 应用集合结束   




//相对模式
//第三方cim    5BYTE
0x05, 0x01, 
0x09, 0x02, 0xA1, 0x01, 0x85, 0x01, 
0x09, 0x01, 0xA1, 0x00, 0x05, 0x09, 0x19, 0x01, 
0x29, 0x03, 0x15, 0x00, 0x25, 0x01, 0x75, 0x01, 
0x95, 0x03, 0x81, 0x02, 0x75, 0x05, 0x95, 0x01, 
0x81, 0x01, 0x05, 0x01, 0x09, 0x30, 0x09, 0x31, 
0x09, 0x38, 0x15, 0x81, 0x25, 0x7F, 0x75, 0x08, 
0x95, 0x03, 0x81, 0x06, 0xC0, 0xC0, 


//绝对模式
//报告ID 1BYTE+按键 1BYTE   
0x05, 0x01, 
0x09, 0x02, 0xA1, 0x01, 0x85, 0x02, 0x09, 0x01, 
0xA1, 0x00, 0x05, 0x09, 0x19, 0x01, 0x29, 0x03, 
0x15, 0x00, 0x25, 0x01, 0x95, 0x03, 0x75, 0x01, 
0x81, 0x02, 0x95, 0x01, 0x75, 0x05, 0x81, 0x01,

//XY坐标  4BYTE
0x05, 0x01, 0x09, 0x30, 0x09, 0x31, 
0x16, 0x00, 0x00, 
0x26, 0xFF, 0x7F, 

0x36, 0x00, 0x00, 
0x46, 0xFF, 0x7F, 
0x66, 0x00, 0x00,

0x75, 0x10, 0x95, 0x02, 0x81, 0x22, 

//滚轮  1BTYE
0x05, 0x01, 0x09, 0x38, 
0x15, 0x81, 
0x25, 0x7F, 

0x35, 0x81, 
0x45, 0x7F, 

0x75, 0x08, 
0x95, 0x01, 
0x81, 0x06,
0xC0, 0xC0,  



};

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  KEYBOARD_CUSTOM_HID_ReportDesc_FS,
  MOUSE_CUSTOM_HID_ReportDesc_FS, 
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */
  return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
/*
static int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}
*/
/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
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

