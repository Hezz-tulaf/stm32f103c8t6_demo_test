#include "IAP.h"
#include "usart.h"
#include "systick.h"
#include "common.h"
#include "bsp_flash.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
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

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t FlashDestination = ApplicationAddress; //文件备份区地址
char file_name[64];
char file_size[16];

uint32_t FileSize=0;
uint32_t UpdateFlag=0xAAAAAAAA;
u8 EOTcnt=0;
_iap_typedef IAP_Para;

static uint32_t Send_Byte (uint8_t c)
{
	Usart_SendByte( USART3, c);
	IAP_Para.IAP_Tick=0;
  return 0;
}

unsigned short CRC16_XMODEM(unsigned char *puchMsg, unsigned int usDataLen)
{
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x1021;
	unsigned char wChar = 0;
 
	while (usDataLen--) 
	{
		wChar = *(puchMsg++);
		wCRCin ^= (wChar << 8);
		for (int i = 0; i < 8; i++) 
		{
			if (wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin);
}

void IAP_Send_C(void)
{
	if(IAP_Para.IAP_Status == 0)
		Send_Byte(CRC16);
}
	
void Reset_IAP(void)
{
	FlashDestination = ApplicationAddress;
	memset(file_name,'\0',64);
	memset(file_size,'\0',16);
	FileSize=0;
	IAP_Para.IAP_PkN=0;
	IAP_Para.IAP_Status=0;
	IAP_Para.IAP_Tick=0;
	EOTcnt=0;
}

/*ymodem 协议
发送端                                        接收端
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 	C
SOH 00 FF "foo.c" "1064'' NUL[118] CRC CRC >>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 		ACK
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 		C
STX 01 FE data[1024] CRC CRC>>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 		ACK
STX 02 FD data[1024] CRC CRC>>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 		ACK
STX 03 FC data[1024] CRC CRC>>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 		ACK
STX 04 FB data[1024] CRC CRC>>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 		ACK
SOH 05 FA data[100] 1A[28] CRC CRC>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 		ACK
EOT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 		NAK
EOT>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 		ACK
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 		C
SOH 00 FF NUL[128] CRC CRC>>>>>>>>>>>>>>>>>>>>>>>>>
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< 		ACK
*/

void Receive_Packet(u8* rbuf, u16 rlen)
{
	u16 crcrec = 0,packet_size;
	u8 a,b,data_packet;
	
	/* check cmd */
	if((*rbuf != SOH) && (*rbuf != STX) && (*rbuf != EOT) && (*rbuf != CA)) {
		printf("------>iap packet head error\r\n");
		return;
	}
	
	if(((*rbuf == SOH) && (rlen != 133)) || ((*rbuf == STX) && (rlen != 1029))) {
		printf("------>iap packet len error %d\r\n",rlen);
		return;
	}
	
	if((*rbuf != EOT) && (*rbuf != CA))
	{
		a =* (rbuf+1);
		b =* (rbuf+2);

		if(a != (u8)~b) {
			printf("------>iap packet no. error\r\n");
			return;
		}

		IAP_Para.IAP_PkN = a;

		if(( a== 0) && (b == 0xFF)) {
			data_packet=0;
		} else {
			data_packet=1;
		}

		crcrec = (*(rbuf + rlen - 2) <<8) + *(rbuf + rlen - 1);

		if(crcrec != CRC16_XMODEM(rbuf + 3, rlen - 5)) {
			printf("------>iap packet crc error\r\n");
			return;
		}
	}
	
	if(*rbuf == SOH) {
		packet_size = PACKET_SIZE;
	} else if(*rbuf == STX) {
		packet_size = PACKET_1K_SIZE;
	}

	switch (*rbuf) {
		case SOH:
		case STX:
			if(data_packet == 0) {		//非数据帧
				if(*(rbuf+3) != 0) {	//起始帧，因为结束帧全部是0
					IAP_Get_Start_frame(rbuf+3);
				} else {								//结束帧
					IAP_Get_End_frame();
				}
			} else {									//数据帧，存储
				IAP_Get_Data_frame(rbuf+3,packet_size);
			}
			break;
		case EOT:
			printf("-----EOT数据帧\r\n");
			if(EOTcnt==0) {	//EOT发送2次确认
				EOTcnt++;
				Send_Byte(NAK);
			} else {
				Send_Byte(ACK);
				Send_Byte(CRC16);
			}
			break;
		case CA:
			printf("-----CA数据帧\r\n");
			Reset_IAP();
		break;

		default:
			Reset_IAP();
			break;
	}
}

void IAP_Get_Start_frame(u8* rbuf)
{
	u8 strlen,res;
	
	IAP_Para.IAP_Status=1;
	strlen = str_cpy1((u8*)file_name,rbuf);
	strlen = str_cpy2((u8*)file_size,rbuf+strlen+1);
	Str2Int((u8*)file_size, &FileSize);

	printf("file_name: %s  file_size: %d\r\n",file_name,FileSize);
	//擦除备份区的空间
	res = bsp_EraseCpuFlash(FlashDestination, FileSize);
	if(res)
	{
		Send_Byte(CA);
		Send_Byte(CA);
		Reset_IAP();
		printf("擦除备份区 失败！\r\n");
		return;
	}
	printf("擦除备份区 成功！\r\n");

	bsp_EraseCpuFlash(FileSizeAddress, 4);
	//把文件大小，写入flash中，地址为bootloader的倒数第二个word
	res = bsp_WriteCpuFlash(FileSizeAddress, &FileSize, 4);
	if(res)
	{
		Send_Byte(CA);
		Send_Byte(CA);
		Reset_IAP();
		printf("写入文件 失败！\r\n");
		return;
	}
	printf("写入文件 成功！\r\n");
	
	Send_Byte(ACK);
	Send_Byte(CRC16);
}

void IAP_Get_Data_frame(u8* rbuf,u16 size)
{
	u8 res;
	
	res = bsp_WriteCpuFlash(FlashDestination, (uint32_t *)rbuf, size);
	FlashDestination += size;
	if(res) {
		Send_Byte(CA);
		Send_Byte(CA);
		Reset_IAP();
		printf("flash存储错误，取消传输1\r\n");
		return;
	}
	
	if(size==PACKET_SIZE) {
		printf("-----SOH %d:数据保存成功\r\n",IAP_Para.IAP_PkN);
	} else if(size==PACKET_1K_SIZE) {
		printf("-----STX %d:数据保存成功\r\n",IAP_Para.IAP_PkN);
	}
	Send_Byte(ACK);
}

void IAP_Get_End_frame(void)
{
	u8 res;
	
	//写入升级标志位，地址为BOOTLOADER的最后一个word
	res = bsp_WriteCpuFlash(UpdateFlagAddress, &UpdateFlag, 4);
	if(res)
	{
		Send_Byte(CA);
		Send_Byte(CA);
		Reset_IAP();
		printf("升级标志写入 失败！\r\n");
		return;
	}
	
	Send_Byte(ACK);
	Reset_IAP();
	printf("-----升级成功，即将重启-----\r\n");
	SysTick_Delay_Ms(1000);
	NVIC_SystemReset();
}

