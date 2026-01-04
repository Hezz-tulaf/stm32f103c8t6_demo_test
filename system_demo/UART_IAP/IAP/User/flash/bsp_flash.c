#include "bsp_flash.h"

uint32_t bsp_GetSector(uint32_t _ulWrAddr)
{
	uint32_t sector = 0;

	sector = _ulWrAddr & SECTOR_MASK;

	return sector;
}

uint8_t bsp_ReadCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpDst, uint32_t _ulSize)
{
	uint32_t i;

	if (_ulFlashAddr + _ulSize > FLASH_BASE_ADDR + FLASH_SIZE)
	{
		return 1;
	}

	if (_ulSize == 0)
	{
		return 1;
	}

	for (i = 0; i < _ulSize; i++)
	{
		*_ucpDst++ = *(uint8_t *)_ulFlashAddr++;
	}

	return 0;
}

uint32_t FLASH_ReadWord(uint32_t faddr)
{
	return *(uint32_t*)faddr; 
}

uint8_t bsp_CmpCpuFlash(uint32_t _ulFlashAddr, uint8_t *_ucpBuf, uint32_t _ulSize)
{
	uint32_t i;
	uint8_t ucIsEqu;
	uint8_t ucByte;

	if (_ulFlashAddr + _ulSize > FLASH_BASE_ADDR + FLASH_SIZE)
	{
		return FLASH_PARAM_ERR;
	}

	if (_ulSize == 0)
	{
		return FLASH_IS_EQU;
	}

	ucIsEqu = 1;
	for (i = 0; i < _ulSize; i++)
	{
		ucByte = *(uint8_t *)_ulFlashAddr;

		if (ucByte != *_ucpBuf)
		{
			if (ucByte != 0xFF)
			{
				return FLASH_REQ_ERASE;
			}
			else
			{
				ucIsEqu = 0;
			}
		}

		_ulFlashAddr++;
		_ucpBuf++;
	}

	if (ucIsEqu == 1)
	{
		return FLASH_IS_EQU;
	}
	else
	{
		return FLASH_REQ_WRITE;
	}
}

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

uint8_t bsp_EraseCpuFlash(uint32_t _ulFlashAddr, uint32_t _ulSize)
{
	uint32_t i,NbrOfPage;
	FLASH_Status status = FLASH_COMPLETE;

	if (_ulSize == 0)
	{
		return 0;
	}

	__set_PRIMASK(1); 
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

	NbrOfPage = FLASH_PagesMask(_ulSize);
	
	for (i = 0; (i < NbrOfPage) && (status == FLASH_COMPLETE); i++)
	{
		status = FLASH_ErasePage(_ulFlashAddr + (PAGE_SIZE * i));
	}

	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASH_Lock();
	__set_PRIMASK(0);

	if (status == FLASH_COMPLETE)
	{
		return 0;
	}
	return 1;
}

uint8_t bsp_WriteCpuFlash(uint32_t _ulFlashAddr, uint32_t *_ucpSrc, uint32_t _ulSize)
{
	uint32_t i,waddr;
	FLASH_Status status = FLASH_COMPLETE;
	
	if (_ulSize == 0)
	{
		return 0;
	}
	
	waddr =_ulFlashAddr;

	__set_PRIMASK(1);
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	

	for (i = 0; i < _ulSize; i += 4)
	{
		status = FLASH_ProgramWord(waddr, *_ucpSrc);
		if ((status != FLASH_COMPLETE)||(*(uint32_t*)waddr != *_ucpSrc))
		{
			break;
		}
		waddr += 4;
		_ucpSrc ++;//指向32位数的指针，自加1即可
	}
	
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASH_Lock();
	__set_PRIMASK(0);

	if (status == FLASH_COMPLETE)
	{
		return 0;
	}
	return 1;
}
