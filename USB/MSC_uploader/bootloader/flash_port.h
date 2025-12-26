#ifndef __FLASH_PORT_H
#define __FLASH_PORT_H

#include "stdint.h"

int flash_port_erase(uint32_t addr, size_t size);
int flash_port_read(uint32_t addr, uint32_t *buf, size_t size);
int flash_port_erase(uint32_t addr, size_t size)

#endif // !__FLASH_PORT_H

