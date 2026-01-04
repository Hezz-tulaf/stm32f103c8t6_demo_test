#ifndef _IAP_H_
#define _IAP_H_

#include "stm32f10x.h"

#if defined (STM32F10X_MD) || defined (STM32F10X_MD_VL)
 #define PAGE_SIZE                         (0x400)    /* 1 Kbyte */
 #define FLASH_SIZE                        (0x10000)  /* 64 KBytes */
#elif defined STM32F10X_CL
 #define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
 #define FLASH_SIZE                        (0x40000)  /* 256 KBytes */
#elif defined STM32F10X_HD || defined (STM32F10X_HD_VL)
 #define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
 #define FLASH_SIZE                        (0x80000)  /* 512 KBytes */
#elif defined STM32F10X_XL
 #define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
 #define FLASH_SIZE                        (0x100000) /* 1 MByte */
#else 
 #error "Please select first the STM32 device to be used (in stm32f10x.h)"    
#endif

#define BOOTLOADER_SIZE 			0x3000
#define APP_SIZE 					0x6800

#define BootLoaderAddress			0x08000000
#define IAPAddr						(BootLoaderAddress + BOOTLOADER_SIZE)
#define ApplicationAddress          (IAPAddr + APP_SIZE)

#define UpdateFlagAddress			(IAPAddr-4)//升级标志位存储地址，BootLoader区域最后一个word
#define FileSizeAddress				(IAPAddr-8)//文件大小 地址为bootloader的倒数第二个word

#define PACKET_SIZE             (128)
#define PACKET_1K_SIZE          (1024)

#define FILE_NAME_LENGTH        (256)
#define FILE_SIZE_LENGTH        (16)

#define SOH                     (0x01)  /* start of 128-byte data packet */
#define STX                     (0x02)  /* start of 1024-byte data packet */
#define EOT                     (0x04)  /* end of transmission */
#define ACK                     (0x06)  /* acknowledge */
#define NAK                     (0x15)  /* negative acknowledge */
#define CA                      (0x18)  /* two of these in succession aborts transfer */
#define CRC16                   (0x43)  /* 'C' == 0x43, request 16-bit CRC */

#define ABORT1                  (0x41)  /* 'A' == 0x41, abort by user */
#define ABORT2                  (0x61)  /* 'a' == 0x61, abort by user */

#define IAP_TIMEOUT             (10000)

typedef struct{
	u8 IAP_Status;		//OTA状态
	u8 IAP_PkN;				//OTA数据包编号
	u32 IAP_Tick;			//OTA超时计数器
}_iap_typedef;

extern _iap_typedef IAP_Para;

void Receive_Packet(u8* rbuf,u16 rlen);
void IAP_Get_Start_frame(u8* rbuf);
void IAP_Get_Data_frame(u8* rbuf,u16 size);
void IAP_Get_End_frame(void);
void Reset_IAP(void);
void IAP_Send_C(void);
uint32_t FLASH_PagesMask(__IO uint32_t Size);
uint8_t bsp_EraseCpuFlash(uint32_t _ulFlashAddr, uint32_t _ulSize);
uint8_t bsp_WriteCpuFlash(uint32_t _ulFlashAddr, uint32_t *_ucpSrc, uint32_t _ulSize);
#endif  /* _IAP_H_ */

