#include "bsp_ctr.h"

/*******************************************************************************
* Function Name  : BSP_CTR_Config
* Description    : BSP_CTR_Config
* Input          :  
* Return         :  
*******************************************************************************/
void BSP_CTR_Config(void)
{
//	GPIO_InitTypeDef GPIO_InitStruct;
//	
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA	| 
													RCC_APB2Periph_GPIOB	| 
													RCC_APB2Periph_GPIOC,  ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

}



