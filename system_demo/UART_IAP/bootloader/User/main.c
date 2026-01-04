#include "main.h"
#include "usart.h"
#include "stm32f10x_flash.h"

typedef  void (*pFunction)(void);
pFunction Jump_To_Application;
uint32_t JumpAddress;
uint32_t EraseCounter = 0x0;
uint32_t NbrOfPage = 0;
FLASH_Status FLASHStatus = FLASH_COMPLETE;
uint32_t FileSize=0;

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
/*
bootload   iap       app       total
 0x3000   0x6800    0x6800    0x10000
   12k      26k       26k       64k
*/

#define BOOTLOADER_SIZE 			0x3000
#define APP_SIZE 					0x6800

#define BootLoaderAddress			0x08000000
#define IAPAddr						(BootLoaderAddress + BOOTLOADER_SIZE)
#define ApplicationAddress          (IAPAddr + APP_SIZE)

#define UpdateFlagAddress			(IAPAddr-4)//升级标志位存储地址，BootLoader区域最后一个word
#define FileSizeAddress				(IAPAddr-8)//文件大小 地址为bootloader的倒数第二个word

#define UPDATE_FLAG_IMAGE					0xAAAAAAAA

uint32_t FLASH_PagesMask(__IO uint32_t Size)
{
  uint32_t pagenumber = 0x0;
  uint32_t size = Size;

  if ((size % PAGE_SIZE) != 0)
  {
    pagenumber = (size / PAGE_SIZE) + 1;
  }
  else
  {
    pagenumber = size / PAGE_SIZE;
  }
  return pagenumber;
}

u8 Copy_APP2_TO_APP1(void)
{
	uint32_t i=0, NumOfWord=0;
	uint32_t ReadAddress = ApplicationAddress;
	uint32_t WriteAddress = IAPAddr;

    //关闭全局中断
	__set_PRIMASK(1); 
	FLASH_Unlock();

	FileSize = *(__IO uint32_t*)FileSizeAddress;

	NbrOfPage = FLASH_PagesMask(FileSize);
	
	//擦除IAP区域
	for (EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++) {
		FLASHStatus = FLASH_ErasePage(IAPAddr + (PAGE_SIZE * EraseCounter));
	}
	
	if(FLASHStatus != FLASH_COMPLETE) {
		printf("FLASH_ErasePage error\r\n");
		return 0;
	}
	printf("FLASH_ErasePage OK\r\n");
	
	if(FileSize%4) {
		NumOfWord= FileSize/4+1;
	}
	else
	{
		NumOfWord= FileSize/4;
	}
	
	//读取APP2到APP1
	for(i = 0; i < NumOfWord; i++) {
		FLASH_ProgramWord(WriteAddress, *(uint32_t*)ReadAddress);
		//校验代码正确性
		if (*(uint32_t*)WriteAddress != *(uint32_t*)ReadAddress) {
			printf("Program Word ERROR %d\r\n",i);
			return 0;
		}
		WriteAddress += 4;
		ReadAddress += 4;
	}
	printf("ProgramWord OK\r\n");
	
	FLASH_Lock();
    __set_PRIMASK(0);
	return 1;
}
/*******************************************************************************
* Function Name  : main
* Description    : 主函数
* Input          : None.
* Return         : None.
*******************************************************************************/
int main(void)
{
	u8 retry=5;
	
	USART3_Config(115200);
	USART1_Config(115200);

	printf("DEBUG-->---------------------------\r\n");
	printf("DEBUG-->                           \r\n");
	printf("DEBUG-->       BOOTLOADER run!     \r\n");
	printf("DEBUG-->                           \r\n");
	printf("DEBUG-->---------------------------\r\n");
	
	printf("UpdateFlag : %08X    ",*(__IO uint32_t*)UpdateFlagAddress);
	//查看image flag释放需要升级APP
	if ((*(__IO uint32_t*)UpdateFlagAddress) == UPDATE_FLAG_IMAGE) {
		printf("need to update\r\n");
		//测试五次
		while(retry--) {
			if(Copy_APP2_TO_APP1()) {
				__set_PRIMASK(1); 
				FLASH_Unlock();
				FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
				//清除升级标志位
				FLASH_ErasePage(UpdateFlagAddress);
				FLASH_Lock();
				__set_PRIMASK(0);
				break;
			}
		}
	} else {
		printf("no update\r\n");
	}
	//简单检查可执行文件
	if (((*(__IO uint32_t*)IAPAddr) & 0x2FFE0000 ) == 0x20000000)
	{
		printf("DEBUG-->  Jump to APP!  	\r\n");
		/* Jump to user application */
		JumpAddress = *(__IO uint32_t*) (IAPAddr + 4);
		Jump_To_Application = (pFunction) JumpAddress;
		/* Initialize user application's Stack Pointer */
		__set_MSP(*(__IO uint32_t*) IAPAddr);
		Jump_To_Application();
	} else {
	    printf("No app need to run\r\n");
	}
	while(1){}
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
