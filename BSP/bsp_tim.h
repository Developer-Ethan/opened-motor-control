#ifndef __BSP_TIM_H
#define __BSP_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g430.h"

typedef enum
{
	INV_ALL_OFF = 0,
	INV_ALL_ON,
	INV_MOTOR_BRAKE,
	INV_UVW_CHARGE,
	INV_U_CHARGE,
	INV_V_CHARGE,
	INV_W_CHARGE
}PWMStatus;

#define ADC_CLOCK (30000000)
#define TIMER_CLOCK_PRESCALER_SET 3 //

void TIM1_PWM_Init(uint8_t polarity);
void __attribute__((section(".RamFunc")))   switch_pwm(PWMStatus option);
void __attribute__((section(".RamFunc"))) pwm_duty_set( uint16_t duty1, uint16_t duty2, uint16_t duty3 );
void TIM4_ETR_Init(void);
void TIM6_1Khz_Init(void);
void TIM4_Capture_Config(void);
#ifdef __cplusplus
}
#endif

#endif

