
#include "main.h"
#include "stm32f1xx_hal_flash.h"
#include <stdarg.h>

/* base address of the flash sectors */
#define ADDR_FLASH_SECTOR_0 ((uint32_t)0x08000000)  /* Base address of Sector 0, 16 K bytes   */
#define ADDR_FLASH_SECTOR_1 ((uint32_t)0x08004000)  /* Base address of Sector 1, 16 K bytes   */
#define ADDR_FLASH_SECTOR_2 ((uint32_t)0x08008000)  /* Base address of Sector 2, 16 K bytes   */
#define ADDR_FLASH_SECTOR_3 ((uint32_t)0x0800C000)  /* Base address of Sector 3, 16 K bytes   */
#define ADDR_FLASH_SECTOR_4 ((uint32_t)0x08010000)  /* Base address of Sector 4, 64 K bytes   */
#define ADDR_FLASH_SECTOR_5 ((uint32_t)0x08020000)  /* Base address of Sector 5, 128 K bytes  */
#define ADDR_FLASH_SECTOR_6 ((uint32_t)0x08040000)  /* Base address of Sector 6, 128 K bytes  */
#define ADDR_FLASH_SECTOR_7 ((uint32_t)0x08060000)  /* Base address of Sector 7, 128 K bytes  */
#define ADDR_FLASH_SECTOR_8 ((uint32_t)0x08080000)  /* Base address of Sector 8, 128 K bytes  */
#define ADDR_FLASH_SECTOR_9 ((uint32_t)0x080A0000)  /* Base address of Sector 9, 128 K bytes  */
#define ADDR_FLASH_SECTOR_10 ((uint32_t)0x080C0000) /* Base address of Sector 10, 128 K bytes */
#define ADDR_FLASH_SECTOR_11 ((uint32_t)0x080E0000) /* Base address of Sector 11, 128 K bytes */
#define ADDR_FLASH_SECTOR_12 ((uint32_t)0x08100000) /* Base address of Sector 12, 16 K bytes  */
#define ADDR_FLASH_SECTOR_13 ((uint32_t)0x08104000) /* Base address of Sector 13, 16 K bytes  */
#define ADDR_FLASH_SECTOR_14 ((uint32_t)0x08108000) /* Base address of Sector 14, 16 K bytes  */
#define ADDR_FLASH_SECTOR_15 ((uint32_t)0x0810C000) /* Base address of Sector 15, 16 K bytes  */
#define ADDR_FLASH_SECTOR_16 ((uint32_t)0x08110000) /* Base address of Sector 16, 64 K bytes  */
#define ADDR_FLASH_SECTOR_17 ((uint32_t)0x08120000) /* Base address of Sector 17, 128 K bytes */
#define ADDR_FLASH_SECTOR_18 ((uint32_t)0x08140000) /* Base address of Sector 18, 128 K bytes */
#define ADDR_FLASH_SECTOR_19 ((uint32_t)0x08160000) /* Base address of Sector 19, 128 K bytes */
#define ADDR_FLASH_SECTOR_20 ((uint32_t)0x08180000) /* Base address of Sector 20, 128 K bytes */
#define ADDR_FLASH_SECTOR_21 ((uint32_t)0x081A0000) /* Base address of Sector 21, 128 K bytes */
#define ADDR_FLASH_SECTOR_22 ((uint32_t)0x081C0000) /* Base address of Sector 22, 128 K bytes */
#define ADDR_FLASH_SECTOR_23 ((uint32_t)0x081E0000) /* Base address of Sector 23, 128 K bytes */


#define FLASH_SECTOR_0     0U  /*!< Sector Number 0   */
#define FLASH_SECTOR_1     1U  /*!< Sector Number 1   */
#define FLASH_SECTOR_2     2U  /*!< Sector Number 2   */
#define FLASH_SECTOR_3     3U  /*!< Sector Number 3   */
#define FLASH_SECTOR_4     4U  /*!< Sector Number 4   */
#define FLASH_SECTOR_5     5U  /*!< Sector Number 5   */
#define FLASH_SECTOR_6     6U  /*!< Sector Number 6   */
#define FLASH_SECTOR_7     7U  /*!< Sector Number 7   */
#define FLASH_SECTOR_8     8U  /*!< Sector Number 8   */
#define FLASH_SECTOR_9     9U  /*!< Sector Number 9   */
#define FLASH_SECTOR_10    10U /*!< Sector Number 10  */
#define FLASH_SECTOR_11    11U /*!< Sector Number 11  */
#define FLASH_SECTOR_12    12U /*!< Sector Number 12  */
#define FLASH_SECTOR_13    13U /*!< Sector Number 13  */
#define FLASH_SECTOR_14    14U /*!< Sector Number 14  */
#define FLASH_SECTOR_15    15U /*!< Sector Number 15  */


static uint32_t stm32_get_sector(uint32_t address)
{
    uint32_t sector = 0;

    if ((address < ADDR_FLASH_SECTOR_1) && (address >= ADDR_FLASH_SECTOR_0))
    {
        sector = FLASH_SECTOR_0;
    }
    else if ((address < ADDR_FLASH_SECTOR_2) && (address >= ADDR_FLASH_SECTOR_1))
    {
        sector = FLASH_SECTOR_1;
    }
    else if ((address < ADDR_FLASH_SECTOR_3) && (address >= ADDR_FLASH_SECTOR_2))
    {
        sector = FLASH_SECTOR_2;
    }
    else if ((address < ADDR_FLASH_SECTOR_4) && (address >= ADDR_FLASH_SECTOR_3))
    {
        sector = FLASH_SECTOR_3;
    }
    else if ((address < ADDR_FLASH_SECTOR_5) && (address >= ADDR_FLASH_SECTOR_4))
    {
        sector = FLASH_SECTOR_4;
    }
    else if ((address < ADDR_FLASH_SECTOR_6) && (address >= ADDR_FLASH_SECTOR_5))
    {
        sector = FLASH_SECTOR_5;
    }
    else if ((address < ADDR_FLASH_SECTOR_7) && (address >= ADDR_FLASH_SECTOR_6))
    {
        sector = FLASH_SECTOR_6;
    }
    else if ((address < ADDR_FLASH_SECTOR_8) && (address >= ADDR_FLASH_SECTOR_7))
    {
        sector = FLASH_SECTOR_7;
    }
    else if ((address < ADDR_FLASH_SECTOR_9) && (address >= ADDR_FLASH_SECTOR_8))
    {
        sector = FLASH_SECTOR_8;
    }
    else if ((address < ADDR_FLASH_SECTOR_10) && (address >= ADDR_FLASH_SECTOR_9))
    {
        sector = FLASH_SECTOR_9;
    }
    else if ((address < ADDR_FLASH_SECTOR_11) && (address >= ADDR_FLASH_SECTOR_10))
    {
        sector = FLASH_SECTOR_10;
    }
    else if ((address < ADDR_FLASH_SECTOR_12) && (address >= ADDR_FLASH_SECTOR_11))
    {
        sector = FLASH_SECTOR_11;
    }
    else /*(address < FLASH_END_ADDR) && (address >= ADDR_FLASH_SECTOR_23))*/
    {
        sector = FLASH_SECTOR_11;
    }

    return sector;
}

/**
 * Get the sector size
 *
 * @param sector sector
 *
 * @return sector size
 */
static uint32_t stm32_get_sector_size(uint32_t sector)
{
    switch (sector)
    {
    case FLASH_SECTOR_0:
        return 16 * 1024;
    case FLASH_SECTOR_1:
        return 16 * 1024;
    case FLASH_SECTOR_2:
        return 16 * 1024;
    case FLASH_SECTOR_3:
        return 16 * 1024;
    case FLASH_SECTOR_4:
        return 64 * 1024;
    case FLASH_SECTOR_5:
        return 128 * 1024;
    case FLASH_SECTOR_6:
        return 128 * 1024;
    case FLASH_SECTOR_7:
        return 128 * 1024;
    case FLASH_SECTOR_8:
        return 128 * 1024;
    case FLASH_SECTOR_9:
        return 128 * 1024;
    case FLASH_SECTOR_10:
        return 128 * 1024;
    case FLASH_SECTOR_11:
        return 128 * 1024;
    default:
        return 128 * 1024;
    }
}

/**
 * Read data from flash.
 * @note This operation's units is word.
 *
 * @param addr flash address
 * @param buf buffer to store read data
 * @param size read bytes size
 *
 * @return result
 */
int flash_port_read(uint32_t addr, uint32_t *buf, size_t size)
{
    int result = 0;

    /* You can add your code under here. */
    uint8_t *buf_8 = (uint8_t *)buf;
    size_t i;

    /*copy from flash to ram */
    for (i = 0; i < size; i++, addr++, buf_8++)
    {
        *buf_8 = *(uint8_t *)addr;
    }
    return result;
}

/**
 * Erase data on flash.
 * @note This operation is irreversible.
 * @note This operation's units is different which on many chips.
 *
 * @param addr flash address
 * @param size erase bytes size
 *
 * @return result
 */
int flash_port_erase(uint32_t addr, size_t size)
{
    int result = 0;

    HAL_StatusTypeDef flash_status = 0;
    size_t erased_size = 0;
    uint32_t cur_erase_sector;

    /* start erase */
    HAL_FLASH_Unlock();

    /* it will stop when erased size is greater than setting size */
    while (erased_size < size)
    {
        cur_erase_sector = stm32_get_sector(addr + erased_size);
        FLASH_PageErase(cur_erase_sector);
        if (flash_status != 0)
        {
            result = -1;
            break;
        }
        erased_size += stm32_get_sector_size(cur_erase_sector);
    }
    HAL_FLASH_Lock();
    return result;
}
/**
 * Write data to flash.
 * @note This operation's units is word.
 * @note This operation must after erase. @see flash_erase.
 *
 * @param addr flash address
 * @param buf the write data buffer
 * @param size write bytes size
 *
 * @return result
 */
int flash_port_write(uint32_t addr, const uint32_t *buf, size_t size)
{
    int result = 0;

    /* You can add your code under here. */
    size_t i;
    uint32_t read_data;
    uint8_t *buf_8 = (uint8_t *)buf;

    HAL_FLASH_Unlock();

    for (i = 0; i < size; i++, buf_8++, addr++)
    {
        /* write data */
        HAL_FLASH_Program(0x00000000U, addr, *buf_8);
        read_data = *(uint8_t *)addr;
        /* check data */
        if (read_data != *buf_8)
        {
            result = -1;
            break;
        }
    }
    HAL_FLASH_Lock();
    return result;
}

