#ifndef _BSP_FLASH_H_
#define _BSP_FLASH_H_

#include <stm32f10x.h>

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

#define FLASH_BASE_ADDR			0x08000000
#define SECTOR_MASK					0xFFFFF800
#define DEV_INFO_ADDR				(0x08000000 + 0x10000 - 0x800)
#define DEV_INFO_SN         (0x08000000 + 0x10000 - 0x400)
#define FLASH_IS_EQU				0   /* Flash内容和待写入的数据相等，不需要擦除和写操作 */
#define FLASH_REQ_WRITE			1	/* Flash不需要擦除，直接写 */
#define FLASH_REQ_ERASE			2	/* Flash需要先擦除,再写 */
#define FLASH_PARAM_ERR			3	/* 函数参数错误 */

uint8_t bsp_ReadCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpDst, uint32_t _ulSize);
uint8_t bsp_WriteCpuFlash(uint32_t _ulFlashAddr, uint32_t *_ucpSrc, uint32_t _ulSize);
uint8_t bsp_CmpCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpBuf, uint32_t _ulSize);
uint8_t bsp_EraseCpuFlash(uint32_t _ulFlashAddr, uint32_t _ulSize);
uint32_t FLASH_ReadWord(uint32_t faddr);
#endif
