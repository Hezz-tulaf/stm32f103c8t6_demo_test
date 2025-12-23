#ifndef _ENCRYPTION_H_
#define _ENCRYPTION_H_

#include "sys.h"
#include "stm32f1xx_hal_flash.h" 

#define STM32_ID_D  352525   //任意的一个数
#define ID_FLASH_SAVE_ADDR  0X801FC00


void STM32_Read_ID(volatile u32 *p);
void STM32_Encrypted_ID(void);
u32 STM32_CMP_Encrypted_ID(void);



#endif 


