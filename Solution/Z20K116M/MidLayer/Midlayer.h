#ifndef _MIDLAYER_H
#define _MIDLAYER_H
#include "AppHeadFile.h"

#define APP_SPEED_BASE (float)(SPEED_BASE)
#define APP_VOLT_BASE (float)(VOLT_BASE)
#define APP_CURR_BASE (float)(CURR_BASE)

#define DUTY_LIMIT	(0.94f)
#define MOD_LIMIT_UP (int16_t)(DUTY_LIMIT * PWM_MOD_COUNTER)
#define MOD_LIMIT_DOWN (int16_t)((1 - DUTY_LIMIT) * PWM_MOD_COUNTER)
void Pmsm_IRQHandleCurrentLoopIsr(void);
void Pmsm_IRQHandleBkinIsr(void);
void Pmsm_IRQHandleSpeedLoopIsr(void);
void EventHandle_1ms(void);
#endif