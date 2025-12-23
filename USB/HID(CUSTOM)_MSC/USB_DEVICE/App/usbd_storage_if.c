///* USER CODE BEGIN Header */
///**
//  ******************************************************************************
//  * @file           : usbd_storage_if.c
//  * @version        : v2.0_Cube
//  * @brief          : Memory management layer.
//  ******************************************************************************
//  * @attention
//  *
//  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
//  * All rights reserved.</center></h2>
//  *
//  * This software component is licensed by ST under Ultimate Liberty license
//  * SLA0044, the "License"; You may not use this file except in compliance with
//  * the License. You may obtain a copy of the License at:
//  *                             www.st.com/SLA0044
//  *
//  ******************************************************************************
//  */
///* USER CODE END Header */

///* Includes ------------------------------------------------------------------*/
//#include "usbd_storage_if.h"

///* USER CODE BEGIN INCLUDE */
//#include "flash.h"
///* USER CODE END INCLUDE */

///* Private typedef -----------------------------------------------------------*/
///* Private define ------------------------------------------------------------*/
///* Private macro -------------------------------------------------------------*/

///* USER CODE BEGIN PV */
///* Private variables ---------------------------------------------------------*/

///* USER CODE END PV */

///** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
//  * @brief Usb device.
//  * @{
//  */

///** @defgroup USBD_STORAGE
//  * @brief Usb mass storage device module
//  * @{
//  */

///** @defgroup USBD_STORAGE_Private_TypesDefinitions
//  * @brief Private types.
//  * @{
//  */

///* USER CODE BEGIN PRIVATE_TYPES */

///* USER CODE END PRIVATE_TYPES */

///**
//  * @}
//  */

///** @defgroup USBD_STORAGE_Private_Defines
//  * @brief Private defines.
//  * @{
//  */

//#define STORAGE_LUN_NBR                  1
//#define STORAGE_BLK_NBR                  64
//#define STORAGE_BLK_SIZ                  0x200

///* USER CODE BEGIN PRIVATE_DEFINES */

///* USER CODE END PRIVATE_DEFINES */

///**
//  * @}
//  */

///** @defgroup USBD_STORAGE_Private_Macros
//  * @brief Private macros.
//  * @{
//  */

///* USER CODE BEGIN PRIVATE_MACRO */

///* USER CODE END PRIVATE_MACRO */

///**
//  * @}
//  */

///** @defgroup USBD_STORAGE_Private_Variables
//  * @brief Private variables.
//  * @{
//  */

///* USER CODE BEGIN INQUIRY_DATA_FS */
///** USB Mass storage Standard Inquiry Data. */
//const int8_t STORAGE_Inquirydata_FS[] = {/* 36 */
//  
//  /* LUN 0 */
//  0x00,
//  0x80,
//  0x02,
//  0x02,
//  (STANDARD_INQUIRY_DATA_LEN - 5),
//  0x00,
//  0x00,	
//  0x00,
//  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
//  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
//  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
//  '0', '.', '0' ,'1'                      /* Version      : 4 Bytes */
//}; 
///* USER CODE END INQUIRY_DATA_FS */

///* USER CODE BEGIN PRIVATE_VARIABLES */

///* USER CODE END PRIVATE_VARIABLES */

///**
//  * @}
//  */

///** @defgroup USBD_STORAGE_Exported_Variables
//  * @brief Public variables.
//  * @{
//  */

//extern USBD_HandleTypeDef hUsbDeviceFS;

///* USER CODE BEGIN EXPORTED_VARIABLES */

///* USER CODE END EXPORTED_VARIABLES */

///**
//  * @}
//  */

///** @defgroup USBD_STORAGE_Private_FunctionPrototypes
//  * @brief Private functions declaration.
//  * @{
//  */

//static int8_t STORAGE_Init_FS(uint8_t lun);
//static int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
//static int8_t STORAGE_IsReady_FS(uint8_t lun);
//static int8_t STORAGE_IsWriteProtected_FS(uint8_t lun);
//static int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
//static int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
//static int8_t STORAGE_GetMaxLun_FS(void);

///* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */

///* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

///**
//  * @}
//  */

//USBD_StorageTypeDef USBD_Storage_Interface_fops_FS =
//{
//  STORAGE_Init_FS,
//  STORAGE_GetCapacity_FS,
//  STORAGE_IsReady_FS,
//  STORAGE_IsWriteProtected_FS,
//  STORAGE_Read_FS,
//  STORAGE_Write_FS,
//  STORAGE_GetMaxLun_FS,
//  (int8_t *)STORAGE_Inquirydata_FS
//};

///* Private functions ---------------------------------------------------------*/
///**
//  * @brief  Initializes over USB FS IP
//  * @param  lun:
//  * @retval USBD_OK if all operations are OK else USBD_FAIL
//  */
//int8_t STORAGE_Init_FS(uint8_t lun)
//{
//  /* USER CODE BEGIN 2 */
//  return (USBD_OK);
//  /* USER CODE END 2 */
//}

///**
//  * @brief  .
//  * @param  lun: .
//  * @param  block_num: .
//  * @param  block_size: .
//  * @retval USBD_OK if all operations are OK else USBD_FAIL
//  */
//int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
//{
//  /* USER CODE BEGIN 3 */
//  *block_num  = STORAGE_BLK_NBR;
//  *block_size = STORAGE_BLK_SIZ;
//  return (USBD_OK);
//  /* USER CODE END 3 */
//}

///**
//  * @brief  .
//  * @param  lun: .
//  * @retval USBD_OK if all operations are OK else USBD_FAIL
//  */
//int8_t STORAGE_IsReady_FS(uint8_t lun)
//{
//  /* USER CODE BEGIN 4 */
//  return (USBD_OK);
//  /* USER CODE END 4 */
//}

///**
//  * @brief  .
//  * @param  lun: .
//  * @retval USBD_OK if all operations are OK else USBD_FAIL
//  */
//int8_t STORAGE_IsWriteProtected_FS(uint8_t lun) 
//{
//  /* USER CODE BEGIN 5 */
//  return (USBD_OK);
//  /* USER CODE END 5 */
//}

///**
//  * @brief  .
//  * @param  lun: .
//  * @retval USBD_OK if all operations are OK else USBD_FAIL
//  */
//int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
//{
//  /* USER CODE BEGIN 6 */
//	uint32_t addr = blk_addr*STORAGE_BLK_SIZ;
//	FlashReadBuff(DEVICE_INFO_ADDRESS+addr,buf,blk_len*STORAGE_BLK_SIZ );
//	
//  return (USBD_OK);
//  /* USER CODE END 6 */
//}

///**
//  * @brief  .
//  * @param  lun: .
//  * @retval USBD_OK if all operations are OK else USBD_FAIL
//  */
//int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
//{
//  /* USER CODE BEGIN 7 */
//	uint32_t addr = blk_addr*STORAGE_BLK_SIZ;
//	FlashWriteBuff( DEVICE_INFO_ADDRESS+addr,buf,blk_len*STORAGE_BLK_SIZ );
//  return (USBD_OK);
//  /* USER CODE END 7 */
//}

///**
//  * @brief  .
//  * @param  None
//  * @retval .
//  */
//int8_t STORAGE_GetMaxLun_FS(void)
//{
//  /* USER CODE BEGIN 8 */
//  return (STORAGE_LUN_NBR - 1);
//  /* USER CODE END 8 */
//}

///* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

///* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

///**
//  * @}
//  */

///**
//  * @}
//  */

///************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


/**

参考：https://www.cnblogs.com/libra13179/p/7156363.html
*/


/*
  ******************************************************************************
  * @file           : usbd_storage_if.c
  * @brief          : Memory management layer
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "usbd_storage_if.h"
/* USER CODE BEGIN INCLUDE */
/* USER CODE END INCLUDE */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @{
  */

/** @defgroup USBD_STORAGE
  * @brief usbd core module
  * @{
  */

/** @defgroup USBD_STORAGE_Private_TypesDefinitions
  * @{
  */
/* USER CODE BEGIN PRIVATE_TYPES */
/* USER CODE END PRIVATE_TYPES */
/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Defines
  * @{
  */
#define STORAGE_LUN_NBR                  1
#define STORAGE_BLK_NBR                  0x81000
#define STORAGE_BLK_SIZ                  0x200

/* USER CODE BEGIN PRIVATE_DEFINES */
/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_Macros
  * @{
  */
/* USER CODE BEGIN PRIVATE_MACRO */
/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_IF_Private_Variables
  * @{
  */
/* USER CODE BEGIN INQUIRY_DATA_FS */
/* USB Mass storage Standard Inquiry Data */
const int8_t  STORAGE_Inquirydata_FS[] =  /* 36 */
{

    /* LUN 0 */
    0x00,
    0x80,
    0x02,
    0x02,
    (STANDARD_INQUIRY_DATA_LEN - 5),
    0x00,
    0x00,
    0x00,
    'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
    'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
    '0', '.', '0' ,'1',                     /* Version      : 4 Bytes */
};
/* USER CODE END INQUIRY_DATA_FS */

/* USER CODE BEGIN PRIVATE_VARIABLES */
/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_IF_Exported_Variables
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;
/* USER CODE BEGIN EXPORTED_VARIABLES */
/* USER CODE END EXPORTED_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_STORAGE_Private_FunctionPrototypes
  * @{
  */
static int8_t STORAGE_Init_FS (uint8_t lun);
static int8_t STORAGE_GetCapacity_FS (uint8_t lun,
                                      uint32_t *block_num,
                                      uint16_t *block_size);
static int8_t  STORAGE_IsReady_FS (uint8_t lun);
static int8_t  STORAGE_IsWriteProtected_FS (uint8_t lun);
static int8_t STORAGE_Read_FS (uint8_t lun,
                               uint8_t *buf,
                               uint32_t blk_addr,
                               uint16_t blk_len);
static int8_t STORAGE_Write_FS (uint8_t lun,
                                uint8_t *buf,
                                uint32_t blk_addr,
                                uint16_t blk_len);
static int8_t STORAGE_GetMaxLun_FS (void);

/* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */
#include <stdint.h>
typedef uint8_t Byte;
typedef struct MasterBootRecord
{
    Byte    checkRoutionOnx86[446];
    struct
    {
        Byte    bootDescriptor;             /* 0x80: bootable device, 0x00: non-bootable */
        Byte    firstPartitionSector[3];    /* 1st sector number */
        Byte    fileSystemDescriptor;       /* 1:FAT12, 4:FAT16(less than 32MB), 5:Extended-DOS Partition,
                                                                                        6:FAT16(more 32MB), 0xb:FAT32(more 2GB),
                                                                                        0xc:FAT32 Int32h, 0xe:FAT16 Int32h,
                                                                                        0xf:5:Extended-DOS Partition Int32h */
        Byte    lastPartitionSector[3];
        Byte    firstSectorNumbers[4];      /* first sector number (link to BPB sector) */
        Byte    numberOfSectors[4];
    }   partitionTable[4];
    Byte    sig[2];                         /* 0x55, 0xaa */
}   MBRecord;

typedef struct FAT16BPB_t
{
    /* FAT16 or FAT12 BPB */
    Byte    jmpOpeCode[3];          /* 0xeb ?? 0x90 */
    Byte    OEMName[8];
    /* FAT16 */
    Byte    bytesPerSector[2];      /* bytes/sector */
    Byte    sectorsPerCluster;      /* sectors/cluster */
    Byte    reservedSectors[2];     /* reserved sector, beginning with sector 0 */
    Byte    numberOfFATs;           /* file allocation table */
    Byte    rootEntries[2];         /* root entry (512) */
    Byte    totalSectors[2];        /* partion total secter */
    Byte    mediaDescriptor;        /* 0xf8: Hard Disk */
    Byte    sectorsPerFAT[2];       /* sector/FAT (FAT32 always zero: see bigSectorsPerFAT) */
    Byte    sectorsPerTrack[2];     /* sector/track (not use) */
    Byte    heads[2];               /* heads number (not use) */
    Byte    hiddenSectors[4];       /* hidden sector number */
    Byte    bigTotalSectors[4];     /* total sector number */
    /* info */
    Byte    driveNumber;
    Byte    unused;
    Byte    extBootSignature;
    Byte    serialNumber[4];
    Byte    volumeLabel[11];
    Byte    fileSystemType[8];      /* "FAT16   " */
    Byte    loadProgramCode[448];
    Byte    sig[2];                 /* 0x55, 0xaa */
}   BPBlock; // BIOS Parameter Block

typedef struct DirEntry_t
{
    Byte    name[8];            /* file name */
    Byte    extension[3];       /* file name extension */
    Byte    attribute;          /* file attribute
                                                                bit 4    directory flag
                                                                bit 3    volume flag
                                                                bit 2    hidden flag
                                                                bit 1    system flag
                                                                bit 0    read only flag */
    Byte    reserved;           /* use NT or same OS */
    Byte    createTimeMs;       /* VFAT 10millsec (0   199) */
    Byte    createTime[2];      /* VFAT */
    Byte    createDate[2];      /* VFAT */
    Byte    accessDate[2];      /* VFAT */
    Byte    clusterHighWord[2]; /* FAT32 MSB 16 bits */
    Byte    updateTime[2];
    Byte    updateDate[2];
    Byte    cluster[2];         /* start cluster number */
    Byte    fileSize[4];        /* file size in bytes (directory is always zero) */
}   DirEntry;

#pragma anon_unions  //keil中默认是不支持匿名结构体的，需要编译指令#pragma anon_unions指名。
typedef struct _DirEntTime
{
    union
    {
        uint16_t W;
        struct
        {
            uint16_t second : 5;
            uint16_t minutes : 6;
            uint16_t hour : 5;
        } B;
    };
} DirEntTime;

typedef struct _DirEntDate
{
    union
    {
        uint16_t W;
        struct
        {
            uint16_t day : 5;
            uint16_t month : 4;
            uint16_t year : 7;
        } B;
    };
} DirEntDate;
#pragma no_anon_unions


const MBRecord sectMBR =
{
    .checkRoutionOnx86 = { 0x00 },
    .partitionTable = {
        {
            .bootDescriptor = 0x00,
            .firstPartitionSector = { 0x02, 0x21, 0x00 },
            .fileSystemDescriptor = 0x06, //FAT16
            .lastPartitionSector = { 0xC2, 0x22, 0x20 },
            .firstSectorNumbers = { 0x00, 0x08, 0x00, 0x00 },
            .numberOfSectors = { 0x00, 0x00, 0x08, 0x00 },
        },//[0]
        { 0 },//[1]
        { 0 },//[2]
        { 0 },//[3]
    },
    .sig = { 0x55, 0xAA },
 };
const BPBlock sectBPB =
{
    .jmpOpeCode = { 0xEB, 0x00, 0x90 },
    .OEMName = { ' ',' ',' ',' ',' ',' ',' ',' ' },
    .bytesPerSector = { 0x00, 0x02 },
    .sectorsPerCluster = 0x08, // 4KB/sectors
    .reservedSectors = { 0x08, 0x00 },
    .numberOfFATs = 0x02,
    .rootEntries = { 0x00, 0x02 },
    .totalSectors = { 0x00, 0x00 },
    .mediaDescriptor = 0xF8, // HDD
    .sectorsPerFAT = { 0x00, 0x01 },
    .sectorsPerTrack = { 0x3F,0x00 },
    .heads = { 0xFF,0x00 },
    .hiddenSectors = { 0x00, 0x08, 0x00, 0x00 },
    .bigTotalSectors = { 0x00,0x00,0x08, 0x00 },
    .driveNumber = 0x80,
    .unused = 0,
    .extBootSignature = 0x29,
    .serialNumber = { 0x78,0x56,0x34,0x12 },
    .volumeLabel = { 'N','O',' ','N','A','M','E',' ',' ',' ',' ' },
    .fileSystemType = { 'F','A','T','1','6',' ',' ',' ' },
    .loadProgramCode = { 0 },
    .sig = { 0x55, 0xAA },
};

#define SECTOR_MBR  (0x0000)
#define SECTOR_PBR  (0x0800)
#define SECTOR_FAT1 (0x0808)
#define SECTOR_FAT2 (0x0908)
#define SECTOR_ROOT (0x0A08)
#define SECTOR_DATA (0x0A28)

void _handleFatClusterChain(uint32_t sect_offset, uint8_t *buf)
{
    uint16_t *bufW = (uint16_t *)&buf[0];
    if (sect_offset == 0)
    {
        bufW[0] = 0xfff8;
        bufW[1] = 0xffff;
        bufW[2] = 0xffff; //结束第一个文件。1簇。
    }
}

void _handleRoot(uint32_t sect_offset, uint8_t *buf)
{
    // 1 sector(512bytes) has 16 entries
    DirEntry *pDir = (DirEntry *)buf;
    if (sect_offset == 0)
    {
        memset(pDir, 0x00, sizeof(DirEntry));
        sprintf((char *)pDir->name, "TEXT_123");
        pDir->extension[0] = 'T';
        pDir->extension[1] = 'X';
        pDir->extension[2] = 'T';
        pDir->attribute = 0x00;
        {
            DirEntTime *pT = (DirEntTime *)&pDir->updateTime[0];
            DirEntDate *pD = (DirEntDate *)&pDir->updateDate[0];
            pT->B.hour = 12;
            pT->B.minutes = 34;
            pT->B.second = 56 / 2;
            pD->B.year = 2017 - 1980;
            pD->B.month = 1;
            pD->B.day = 12;
        }

        *(uint16_t*)&pDir->cluster = 0x0002;
        *(uint32_t*)&pDir->fileSize = 123;
    }
}

void _handleData(uint32_t sect_offset, uint8_t *buf)
{
    memset(buf, 'A', 512);
    sprintf((char *)buf, "Hello World!\r\n");
    buf[14]='>';
}

uint32_t _ReadSector(uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
    switch (blk_addr)
    {
    case SECTOR_MBR:
        memcpy(buf, (const void *)&sectMBR, 512);
        break;
    case SECTOR_PBR:
        memcpy(buf, (const void *)&sectBPB, 512);
        break;
    default:
        memset(buf, 0x00, 512);
        //FAT cluster chain
        if ((SECTOR_FAT1 <= blk_addr) && (blk_addr < SECTOR_ROOT))//判断地址 SECTOR_FAT1~SECTOR_ROOT
        {
            if (blk_addr >= SECTOR_FAT2)//  >SECTOR_FAT2
            {
                blk_addr -= (SECTOR_FAT2 - SECTOR_FAT1);//blk_addr=blk_addr-(SECTOR_FAT2 - SECTOR_FAT1)
            }
            _handleFatClusterChain(blk_addr - SECTOR_FAT1, buf);//blk_addr=blk_addr-SECTOR_FAT2

        }
        else if ((SECTOR_ROOT <= blk_addr) && (blk_addr < SECTOR_DATA))//SECTOR_ROOT~SECTOR_DATA
        {
            _handleRoot(blk_addr - SECTOR_ROOT, buf);

        }
        else if (SECTOR_DATA <= blk_addr)//>SECTOR_DATA
        {
            _handleData(blk_addr - SECTOR_DATA, buf);

        }
        break;
    }
    return 0;
}
/* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

/**
  * @}
  */

USBD_StorageTypeDef USBD_Storage_Interface_fops_FS =
{
    STORAGE_Init_FS,
    STORAGE_GetCapacity_FS,
    STORAGE_IsReady_FS,
    STORAGE_IsWriteProtected_FS,
    STORAGE_Read_FS,
    STORAGE_Write_FS,
    STORAGE_GetMaxLun_FS,
    (int8_t *)STORAGE_Inquirydata_FS,
};

/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : STORAGE_Init_FS
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Init_FS (uint8_t lun)
{
    /* USER CODE BEGIN 2 */
    return (USBD_OK);
    /* USER CODE END 2 */
}

/*******************************************************************************
* Function Name  : STORAGE_GetCapacity_FS
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_GetCapacity_FS (uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
    /* USER CODE BEGIN 3 */
    *block_num  = STORAGE_BLK_NBR;
    *block_size = STORAGE_BLK_SIZ;
    return (USBD_OK);
    /* USER CODE END 3 */
}

/*******************************************************************************
* Function Name  : STORAGE_IsReady_FS
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t  STORAGE_IsReady_FS (uint8_t lun)
{
    /* USER CODE BEGIN 4 */
    return (USBD_OK);
    /* USER CODE END 4 */
}

/*******************************************************************************
* Function Name  : STORAGE_IsWriteProtected_FS
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t  STORAGE_IsWriteProtected_FS (uint8_t lun)
{
    /* USER CODE BEGIN 5 */
    return (USBD_OK);
    /* USER CODE END 5 */
}

/*******************************************************************************
* Function Name  : STORAGE_Read_FS
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Read_FS (uint8_t lun,
                        uint8_t *buf,
                        uint32_t blk_addr,
                        uint16_t blk_len)
{
    /* USER CODE BEGIN 6 */
    _ReadSector(buf, blk_addr, blk_len);
    return (USBD_OK);
    /* USER CODE END 6 */
}

/*******************************************************************************
* Function Name  : STORAGE_Write_FS
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_Write_FS (uint8_t lun,
                         uint8_t *buf,
                         uint32_t blk_addr,
                         uint16_t blk_len)
{
    /* USER CODE BEGIN 7 */
    return (USBD_OK);
    /* USER CODE END 7 */
}

/*******************************************************************************
* Function Name  : STORAGE_GetMaxLun_FS
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
int8_t STORAGE_GetMaxLun_FS (void)
{
    /* USER CODE BEGIN 8 */
    return (STORAGE_LUN_NBR - 1);
    /* USER CODE END 8 */
}

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */
/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

/**
  * @}
  */

/**
  * @}
  */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



///**
//  ******************************************************************************
//  * [url=home.php?mod=space&uid=288409]@file[/url]           : usbd_storage_if.c
//  * [url=home.php?mod=space&uid=895143]@version[/url]        : v2.0_Cube
//  * [url=home.php?mod=space&uid=247401]@brief[/url]          : Memory management layer.
//  ******************************************************************************
//  * This notice applies to any and all portions of this file
//  * that are not between comment pairs USER CODE BEGIN and
//  * USER CODE END. Other portions of this file, whether
//  * inserted by the user or by software development tools
//  * are owned by their respective copyright owners.
//  *
//  * Copyright (c) 2018 STMicroelectronics International N.V.
//  * All rights reserved.
//  *
//  * Redistribution and use in source and binary forms, with or without
//  * modification, are permitted, provided that the following conditions are met:
//  *
//  * 1. Redistribution of source code must retain the above copyright notice,
//  *    this list of conditions and the following disclaimer.
//  * 2. Redistributions in binary form must reproduce the above copyright notice,
//  *    this list of conditions and the following disclaimer in the documentation
//  *    and/or other materials provided with the distribution.
//  * 3. Neither the name of STMicroelectronics nor the names of other
//  *    contributors to this software may be used to endorse or promote products
//  *    derived from this software without specific written permission.
//  * 4. This software, including modifications and/or derivative works of this
//  *    software, must execute solely and exclusively on microcontroller or
//  *    microprocessor devices manufactured by or for STMicroelectronics.
//  * 5. Redistribution and use of this software other than as permitted under
//  *    this license is void and will automatically terminate your rights under
//  *    this license.
//  *
//  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
//  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
//  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
//  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
//  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
//  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
//  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
//  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  *
//  ******************************************************************************
//  */

///* Includes ------------------------------------------------------------------*/
//#include "usbd_storage_if.h"

///* USER CODE BEGIN INCLUDE */

///* USER CODE END INCLUDE */

///* Private typedef -----------------------------------------------------------*/
///* Private define ------------------------------------------------------------*/
///* Private macro -------------------------------------------------------------*/

///* USER CODE BEGIN PV */
///* Private variables ---------------------------------------------------------*/

///* USER CODE END PV */

///** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
//  * [url=home.php?mod=space&uid=247401]@brief[/url] Usb device.
//  * @{
//  */

///** @defgroup USBD_STORAGE
//  * @brief Usb mass storage device module
//  * @{
//  */

///** @defgroup USBD_STORAGE_Private_TypesDefinitions
//  * @brief Private types.
//  * @{
//  */

///* USER CODE BEGIN PRIVATE_TYPES */

///* USER CODE END PRIVATE_TYPES */

///**
//  * @}
//  */

///** @defgroup USBD_STORAGE_Private_Defines
//  * @brief Private defines.
//  * @{
//  */

//#define STORAGE_LUN_NBR                  1
//#define STORAGE_BLK_NBR                  25
//#define STORAGE_BLK_SIZ                  0x200

///* USER CODE BEGIN PRIVATE_DEFINES */
//#define mySTORAGE_BLK_NBR                  25
//uint8_t test[STORAGE_BLK_NBR*STORAGE_BLK_SIZ];//40K
///* USER CODE END PRIVATE_DEFINES */

///**
//  * @}
//  */

///** @defgroup USBD_STORAGE_Private_Macros
//  * @brief Private macros.
//  * @{
//  */

///* USER CODE BEGIN PRIVATE_MACRO */

///* USER CODE END PRIVATE_MACRO */

///**
//  * @}
//  */

///** @defgroup USBD_STORAGE_Private_Variables
//  * @brief Private variables.
//  * @{
//  */

///* USER CODE BEGIN INQUIRY_DATA_FS */
///** USB Mass storage Standard Inquiry Data. */
//const int8_t STORAGE_Inquirydata_FS[] = {/* 36 */
//  
//  /* LUN 0 */
//  0x00,
//  0x80,
//  0x02,
//  0x02,
//  (STANDARD_INQUIRY_DATA_LEN - 5),
//  0x00,
//  0x00,        
//  0x00,
//  'S', 'T', 'M', ' ', ' ', ' ', ' ', ' ', /* Manufacturer : 8 bytes */
//  'P', 'r', 'o', 'd', 'u', 'c', 't', ' ', /* Product      : 16 Bytes */
//  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
//  '0', '.', '0' ,'1'                      /* Version      : 4 Bytes */
//};
///* USER CODE END INQUIRY_DATA_FS */

///* USER CODE BEGIN PRIVATE_VARIABLES */

///* USER CODE END PRIVATE_VARIABLES */

///**
//  * @}
//  */

///** @defgroup USBD_STORAGE_Exported_Variables
//  * @brief Public variables.
//  * @{
//  */

//extern USBD_HandleTypeDef hUsbDeviceFS;

///* USER CODE BEGIN EXPORTED_VARIABLES */

///* USER CODE END EXPORTED_VARIABLES */

///**
//  * @}
//  */

///** @defgroup USBD_STORAGE_Private_FunctionPrototypes
//  * @brief Private functions declaration.
//  * @{
//  */

//static int8_t STORAGE_Init_FS(uint8_t lun);
//static int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size);
//static int8_t STORAGE_IsReady_FS(uint8_t lun);
//static int8_t STORAGE_IsWriteProtected_FS(uint8_t lun);
//static int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
//static int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
//static int8_t STORAGE_GetMaxLun_FS(void);

///* USER CODE BEGIN PRIVATE_FUNCTIONS_DECLARATION */
//const uint8_t MBK[]={
//0xEB, 0x3C, 0x90, 0x4D, 0x53, 0x44, 0x4F, 0x53, 0x35, 0x2E, 0x30, 0x00, 0x02, 0x01, 0x06, 0x00,
//0x02, 0x00, 0x02, 0x50, 0x00, 0xF8, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
//0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x29, 0x9D, 0x27, 0x98, 0x4C, 0x4E, 0x4F, 0x20, 0x4E, 0x41,
//0x4D, 0x45, 0x20, 0x20, 0x20, 0x20, 0x46, 0x41, 0x54, 0x31, 0x32, 0x20, 0x20, 0x20, 0x33, 0xC9,
//0x8E, 0xD1, 0xBC, 0xF0, 0x7B, 0x8E, 0xD9, 0xB8, 0x00, 0x20, 0x8E, 0xC0, 0xFC, 0xBD, 0x00, 0x7C,
//0x38, 0x4E, 0x24, 0x7D, 0x24, 0x8B, 0xC1, 0x99, 0xE8, 0x3C, 0x01, 0x72, 0x1C, 0x83, 0xEB, 0x3A,
//0x66, 0xA1, 0x1C, 0x7C, 0x26, 0x66, 0x3B, 0x07, 0x26, 0x8A, 0x57, 0xFC, 0x75, 0x06, 0x80, 0xCA,
//0x02, 0x88, 0x56, 0x02, 0x80, 0xC3, 0x10, 0x73, 0xEB, 0x33, 0xC9, 0x8A, 0x46, 0x10, 0x98, 0xF7,
//0x66, 0x16, 0x03, 0x46, 0x1C, 0x13, 0x56, 0x1E, 0x03, 0x46, 0x0E, 0x13, 0xD1, 0x8B, 0x76, 0x11,
//0x60, 0x89, 0x46, 0xFC, 0x89, 0x56, 0xFE, 0xB8, 0x20, 0x00, 0xF7, 0xE6, 0x8B, 0x5E, 0x0B, 0x03,
//0xC3, 0x48, 0xF7, 0xF3, 0x01, 0x46, 0xFC, 0x11, 0x4E, 0xFE, 0x61, 0xBF, 0x00, 0x00, 0xE8, 0xE6,
//0x00, 0x72, 0x39, 0x26, 0x38, 0x2D, 0x74, 0x17, 0x60, 0xB1, 0x0B, 0xBE, 0xA1, 0x7D, 0xF3, 0xA6,
//0x61, 0x74, 0x32, 0x4E, 0x74, 0x09, 0x83, 0xC7, 0x20, 0x3B, 0xFB, 0x72, 0xE6, 0xEB, 0xDC, 0xA0,
//0xFB, 0x7D, 0xB4, 0x7D, 0x8B, 0xF0, 0xAC, 0x98, 0x40, 0x74, 0x0C, 0x48, 0x74, 0x13, 0xB4, 0x0E,
//0xBB, 0x07, 0x00, 0xCD, 0x10, 0xEB, 0xEF, 0xA0, 0xFD, 0x7D, 0xEB, 0xE6, 0xA0, 0xFC, 0x7D, 0xEB,
//0xE1, 0xCD, 0x16, 0xCD, 0x19, 0x26, 0x8B, 0x55, 0x1A, 0x52, 0xB0, 0x01, 0xBB, 0x00, 0x00, 0xE8,
//0x3B, 0x00, 0x72, 0xE8, 0x5B, 0x8A, 0x56, 0x24, 0xBE, 0x0B, 0x7C, 0x8B, 0xFC, 0xC7, 0x46, 0xF0,
//0x3D, 0x7D, 0xC7, 0x46, 0xF4, 0x29, 0x7D, 0x8C, 0xD9, 0x89, 0x4E, 0xF2, 0x89, 0x4E, 0xF6, 0xC6,
//0x06, 0x96, 0x7D, 0xCB, 0xEA, 0x03, 0x00, 0x00, 0x20, 0x0F, 0xB6, 0xC8, 0x66, 0x8B, 0x46, 0xF8,
//0x66, 0x03, 0x46, 0x1C, 0x66, 0x8B, 0xD0, 0x66, 0xC1, 0xEA, 0x10, 0xEB, 0x5E, 0x0F, 0xB6, 0xC8,
//0x4A, 0x4A, 0x8A, 0x46, 0x0D, 0x32, 0xE4, 0xF7, 0xE2, 0x03, 0x46, 0xFC, 0x13, 0x56, 0xFE, 0xEB,
//0x4A, 0x52, 0x50, 0x06, 0x53, 0x6A, 0x01, 0x6A, 0x10, 0x91, 0x8B, 0x46, 0x18, 0x96, 0x92, 0x33,
//0xD2, 0xF7, 0xF6, 0x91, 0xF7, 0xF6, 0x42, 0x87, 0xCA, 0xF7, 0x76, 0x1A, 0x8A, 0xF2, 0x8A, 0xE8,
//0xC0, 0xCC, 0x02, 0x0A, 0xCC, 0xB8, 0x01, 0x02, 0x80, 0x7E, 0x02, 0x0E, 0x75, 0x04, 0xB4, 0x42,
//0x8B, 0xF4, 0x8A, 0x56, 0x24, 0xCD, 0x13, 0x61, 0x61, 0x72, 0x0B, 0x40, 0x75, 0x01, 0x42, 0x03,
//0x5E, 0x0B, 0x49, 0x75, 0x06, 0xF8, 0xC3, 0x41, 0xBB, 0x00, 0x00, 0x60, 0x66, 0x6A, 0x00, 0xEB,
//0xB0, 0x42, 0x4F, 0x4F, 0x54, 0x4D, 0x47, 0x52, 0x20, 0x20, 0x20, 0x20, 0x0D, 0x0A, 0x52, 0x65,
//0x6D, 0x6F, 0x76, 0x65, 0x20, 0x64, 0x69, 0x73, 0x6B, 0x73, 0x20, 0x6F, 0x72, 0x20, 0x6F, 0x74,
//0x68, 0x65, 0x72, 0x20, 0x6D, 0x65, 0x64, 0x69, 0x61, 0x2E, 0xFF, 0x0D, 0x0A, 0x44, 0x69, 0x73,
//0x6B, 0x20, 0x65, 0x72, 0x72, 0x6F, 0x72, 0xFF, 0x0D, 0x0A, 0x50, 0x72, 0x65, 0x73, 0x73, 0x20,
//0x61, 0x6E, 0x79, 0x20, 0x6B, 0x65, 0x79, 0x20, 0x74, 0x6F, 0x20, 0x72, 0x65, 0x73, 0x74, 0x61,
//0x72, 0x74, 0x0D, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xAC, 0xCB, 0xD8, 0x55, 0xAA
//};

////const uint8_t MBK[]={
////0xEB,0x3C,0x90,0x4D,0x53,0x44,0x4F,0x53,0x35,0x2E,0x30,0x00,0x02,0x01,0x04,0x00,
////        0x02,0x00,0x02,0x00,0x00,0xF8,0xFE,0x00,0x3F,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,
////        0x00,0x00,0x01,0x00,0x80,0x00,0x29,0x83,0xCB,0x31,0x2E,0x4E,0x4F,0x20,0x4E,0x41,
////        0x4D,0x45,0x20,0x20,0x20,0x20,0x46,0x41,0x54,0x31,0x36,0x20,0x20,0x20,0x33,0xC9,
////        0x8E,0xD1,0xBC,0xF0,0x7B,0x8E,0xD9,0xB8,0x00,0x20,0x8E,0xC0,0xFC,0xBD,0x00,0x7C,
////        0x38,0x4E,0x24,0x7D,0x24,0x8B,0xC1,0x99,0xE8,0x3C,0x01,0x72,0x1C,0x83,0xEB,0x3A,
////        0x66,0xA1,0x1C,0x7C,0x26,0x66,0x3B,0x07,0x26,0x8A,0x57,0xFC,0x75,0x06,0x80,0xCA,
////        0x02,0x88,0x56,0x02,0x80,0xC3,0x10,0x73,0xEB,0x33,0xC9,0x8A,0x46,0x10,0x98,0xF7,
////        0x66,0x16,0x03,0x46,0x1C,0x13,0x56,0x1E,0x03,0x46,0x0E,0x13,0xD1,0x8B,0x76,0x11,
////        0x60,0x89,0x46,0xFC,0x89,0x56,0xFE,0xB8,0x20,0x00,0xF7,0xE6,0x8B,0x5E,0x0B,0x03,
////        0xC3,0x48,0xF7,0xF3,0x01,0x46,0xFC,0x11,0x4E,0xFE,0x61,0xBF,0x00,0x00,0xE8,0xE6,
////        0x00,0x72,0x39,0x26,0x38,0x2D,0x74,0x17,0x60,0xB1,0x0B,0xBE,0xA1,0x7D,0xF3,0xA6,
////        0x61,0x74,0x32,0x4E,0x74,0x09,0x83,0xC7,0x20,0x3B,0xFB,0x72,0xE6,0xEB,0xDC,0xA0,
////        0xFB,0x7D,0xB4,0x7D,0x8B,0xF0,0xAC,0x98,0x40,0x74,0x0C,0x48,0x74,0x13,0xB4,0x0E,
////        0xBB,0x07,0x00,0xCD,0x10,0xEB,0xEF,0xA0,0xFD,0x7D,0xEB,0xE6,0xA0,0xFC,0x7D,0xEB,
////        0xE1,0xCD,0x16,0xCD,0x19,0x26,0x8B,0x55,0x1A,0x52,0xB0,0x01,0xBB,0x00,0x00,0xE8,
////        0x3B,0x00,0x72,0xE8,0x5B,0x8A,0x56,0x24,0xBE,0x0B,0x7C,0x8B,0xFC,0xC7,0x46,0xF0,
////        0x3D,0x7D,0xC7,0x46,0xF4,0x29,0x7D,0x8C,0xD9,0x89,0x4E,0xF2,0x89,0x4E,0xF6,0xC6,
////        0x06,0x96,0x7D,0xCB,0xEA,0x03,0x00,0x00,0x20,0x0F,0xB6,0xC8,0x66,0x8B,0x46,0xF8,
////        0x66,0x03,0x46,0x1C,0x66,0x8B,0xD0,0x66,0xC1,0xEA,0x10,0xEB,0x5E,0x0F,0xB6,0xC8,
////        0x4A,0x4A,0x8A,0x46,0x0D,0x32,0xE4,0xF7,0xE2,0x03,0x46,0xFC,0x13,0x56,0xFE,0xEB,
////        0x4A,0x52,0x50,0x06,0x53,0x6A,0x01,0x6A,0x10,0x91,0x8B,0x46,0x18,0x96,0x92,0x33,
////        0xD2,0xF7,0xF6,0x91,0xF7,0xF6,0x42,0x87,0xCA,0xF7,0x76,0x1A,0x8A,0xF2,0x8A,0xE8,
////        0xC0,0xCC,0x02,0x0A,0xCC,0xB8,0x01,0x02,0x80,0x7E,0x02,0x0E,0x75,0x04,0xB4,0x42,
////        0x8B,0xF4,0x8A,0x56,0x24,0xCD,0x13,0x61,0x61,0x72,0x0B,0x40,0x75,0x01,0x42,0x03,
////        0x5E,0x0B,0x49,0x75,0x06,0xF8,0xC3,0x41,0xBB,0x00,0x00,0x60,0x66,0x6A,0x00,0xEB,
////        0xB0,0x42,0x4F,0x4F,0x54,0x4D,0x47,0x52,0x20,0x20,0x20,0x20,0x0D,0x0A,0x52,0x65,
////        0x6D,0x6F,0x76,0x65,0x20,0x64,0x69,0x73,0x6B,0x73,0x20,0x6F,0x72,0x20,0x6F,0x74,
////        0x68,0x65,0x72,0x20,0x6D,0x65,0x64,0x69,0x61,0x2E,0xFF,0x0D,0x0A,0x44,0x69,0x73,
////        0x6B,0x20,0x65,0x72,0x72,0x6F,0x72,0xFF,0x0D,0x0A,0x50,0x72,0x65,0x73,0x73,0x20,
////        0x61,0x6E,0x79,0x20,0x6B,0x65,0x79,0x20,0x74,0x6F,0x20,0x72,0x65,0x73,0x74,0x61,
////        0x72,0x74,0x0D,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xAC,0xCB,0xD8,0x55,0xAA,
////};
///* USER CODE END PRIVATE_FUNCTIONS_DECLARATION */

///**
//  * @}
//  */

//USBD_StorageTypeDef USBD_Storage_Interface_fops_FS =
//{
//  STORAGE_Init_FS,
//  STORAGE_GetCapacity_FS,
//  STORAGE_IsReady_FS,
//  STORAGE_IsWriteProtected_FS,
//  STORAGE_Read_FS,
//  STORAGE_Write_FS,
//  STORAGE_GetMaxLun_FS,
//  (int8_t *)STORAGE_Inquirydata_FS
//};

///* Private functions ---------------------------------------------------------*/
///**
//  * @brief  Initializes over USB FS IP
//  * @param  lun:
//  * @retval USBD_OK if all operations are OK else USBD_FAIL
//  */
//int8_t STORAGE_Init_FS(uint8_t lun)
//{
//  /* USER CODE BEGIN 2 */
//        uint32_t i;
//        for(i=0;i<sizeof(MBK);i++)
//        {
//                test[i] = MBK[i];
//        }
//  return (USBD_OK);
//  /* USER CODE END 2 */
//}

///**
//  * @brief  .
//  * @param  lun: .
//  * @param  block_num: .
//  * @param  block_size: .
//  * @retval USBD_OK if all operations are OK else USBD_FAIL
//  */
//int8_t STORAGE_GetCapacity_FS(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
//{
//  /* USER CODE BEGIN 3 */
//  *block_num  = mySTORAGE_BLK_NBR;
//  *block_size = STORAGE_BLK_SIZ;
//  return (USBD_OK);
//  /* USER CODE END 3 */
//}

///**
//  * @brief  .
//  * @param  lun: .
//  * @retval USBD_OK if all operations are OK else USBD_FAIL
//  */
//int8_t STORAGE_IsReady_FS(uint8_t lun)
//{
//  /* USER CODE BEGIN 4 */
//  return (USBD_OK);
//  /* USER CODE END 4 */
//}

///**
//  * @brief  .
//  * @param  lun: .
//  * @retval USBD_OK if all operations are OK else USBD_FAIL
//  */
//int8_t STORAGE_IsWriteProtected_FS(uint8_t lun)
//{
//  /* USER CODE BEGIN 5 */
//  return (USBD_OK);
//  /* USER CODE END 5 */
//}

///**
//  * @brief  .
//  * @param  lun: .
//  * @retval USBD_OK if all operations are OK else USBD_FAIL
//  */
//int8_t STORAGE_Read_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
//{
//  /* USER CODE BEGIN 6 */
//        uint32_t i,j,n=0;
//  if((blk_addr+blk_len)*STORAGE_BLK_SIZ<sizeof(test))
//        {
//                for(i=0;i<blk_len;i++)
//                {
//                        for(j=0;j<STORAGE_BLK_SIZ;j++)
//                        {
//                                buf[n++] = test[(blk_addr+i)*STORAGE_BLK_SIZ+j];
//                        }
//                }
//        }
//  return (USBD_OK);
//  /* USER CODE END 6 */
//}

///**
//  * @brief  .
//  * @param  lun: .
//  * @retval USBD_OK if all operations are OK else USBD_FAIL
//  */
//int8_t STORAGE_Write_FS(uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
//{
//  /* USER CODE BEGIN 7 */
//        uint32_t i,j,n=0;
//  if((blk_addr+blk_len)*STORAGE_BLK_SIZ<sizeof(test))
//        {
//                for(i=0;i<blk_len;i++)
//                {
//                        for(j=0;j<STORAGE_BLK_SIZ;j++)
//                        {
//                                 test[(blk_addr+i)*STORAGE_BLK_SIZ+j] = buf[n++];
//                        }
//                }
//        }
//  return (USBD_OK);
//  /* USER CODE END 7 */
//}

///**
//  * @brief  .
//  * @param  None
//  * @retval .
//  */
//int8_t STORAGE_GetMaxLun_FS(void)
//{
//  /* USER CODE BEGIN 8 */
//  return (STORAGE_LUN_NBR - 1);
//  /* USER CODE END 8 */
//}

///* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

///* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */

///**
//  * @}
//  */

///**
//  * @}
//  */

///************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

