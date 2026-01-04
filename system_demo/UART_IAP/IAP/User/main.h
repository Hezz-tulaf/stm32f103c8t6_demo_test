#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f10x.h"
#include "sys_para.h"

#define TASKS_MAX           						2
#define DEBUG_MODE           						1

void TaskReMarks(void);
void TaskProcess(void);
void Peripheral_Init(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
