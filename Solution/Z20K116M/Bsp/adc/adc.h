#ifndef _ADC_H_
#define _ADC_H_
#include "stdint.h"
#define VALUE_WM (2)
extern uint32_t AdcMapData[2];
extern uint32_t IRQn_AdcMapData[5];
extern uint32_t IRQn_AdcMapDataVal[5];
uint8_t Hal_SetupAdcs(void);
void GetAdcData(void);
#endif