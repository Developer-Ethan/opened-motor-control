#ifndef __BSP_CONFIG_H
#define __BSP_CONFIG_H

#include "n32g430.h"

void System_Init(void);

void Delay_ms(__IO u32 nTime);
	
void FLASH_Read_Out_Protection(void);

#endif /* end of __BSP_CONFIG_H */

