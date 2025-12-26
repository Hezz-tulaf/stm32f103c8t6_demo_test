
#include "main.h"

#define STM32_APP_BASE 0x08010000

typedef void (*pfunction)(void);
pfunction reset_handler;

// THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI
void WFI_SET(void)
{
	__ASM volatile("wfi");
}
//关闭所有中断(但是不包括fault和NMI中断)
void INTX_DISABLE(void)
{
	__ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");
}
//设置栈顶地址
// addr:栈顶地址
__asm void MSR_MSP(uint32_t addr)
{
	MSR MSP, r0 // set Main Stack value
				 BX r14
}

void iap_jump(uint32_t addr)
{
	printf("[%s] %d: \r\n", __func__, __LINE__);

	// 栈顶地址检查
	if (((*(uint32_t *)(addr)) & 0xff000000) == 0x20000000)
	{
		printf("[%s] %d: %x\r\n", __func__, __LINE__, ((*(uint32_t *)(addr)) & 0xff000000));

		if (((*(uint32_t *)(addr + 4)) & 0x0fff0000) == addr)
		{
			HAL_Delay(100);

			reset_handler = (pfunction)((*(uint32_t *)(addr + 4)));
			printf("[%s]%d: reset_handler=0x%x\r\n", __func__, __LINE__, reset_handler);
			MSR_MSP(*(uint32_t *)addr);

			printf("[%s] %d: reset!!!\r\n", __func__, __LINE__);
			reset_handler();
		}
	}
	else
	{
		printf("[%s] %d: err\r\n", __func__, __LINE__);
	}
}

extern void usb_stop(void);

int boot_flag = 0;

void bootloader_main(void)
{
	HAL_Delay(500);
	printf("[%s] %d: \r\n", __func__, __LINE__);

//	HAL_Delay(3000);
//	usb_stop();
//	HAL_Delay(500);
//	iap_jump(STM32_APP_BASE);

	printf("[%s] %d: ======================================\r\n", __func__, __LINE__);
	printf("[%s] %d:              Waiting for upgrade      \r\n", __func__, __LINE__);
	printf("[%s] %d: ======================================\r\n", __func__, __LINE__);
	while (1)
	{
		HAL_Delay(500);
		if (boot_flag)
		{
			usb_stop();
			HAL_Delay(500);

			printf("[%s] %d: ======================================\r\n", __func__, __LINE__);
			printf("[%s] %d:              Upgrade Complete         \r\n", __func__, __LINE__);
			printf("[%s] %d: ======================================\r\n", __func__, __LINE__);

			iap_jump(STM32_APP_BASE);
		}
	}
}
