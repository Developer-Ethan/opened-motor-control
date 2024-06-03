#ifndef _PARAMETER_H_
#define _PARAMETER_H_
#include "DataCalc.h"

#define _PI (3.1415926535f)
/*statemachine detect time*/
#define TIME_STABLE (40u)
#define TIME_CALIBRATE (20u)
#define TIME_IDLE (20u)
#define TIME_ALIGN (200u)
#define TIME_OPENLOOP (1500u)
/*board parameters*/
#define R_SHUNT (0.005f)
#define GAIN_AMP (20.0f)
#define ADC_VREF (5.0f)
#define RES_PULL (680.0f) // kohm
#define RES_DOWN (57.6f)
#define VOLTAGE_MAX_ADCSAMPLE (ADC_VREF * (RES_PULL + RES_DOWN) / RES_DOWN)
#define CURRENT_MAX_ADCSAMPLE (ADC_VREF / R_SHUNT / GAIN_AMP)
/*mcu parameters*/
#define SYSTEM_FREQ (64u)//M
#define PWM_FREQ (16000u)
#define PWM_MOD (int16_t)(SYSTEM_FREQ * 1000 / (PWM_FREQ / 1000))
#define PWM_PERIOD (1.0f / PWM_FREQ) // 50us
#define TIMER_CLOCK_PRESCALER_SET (0)
#define DEADTIME (1.0f)      // us
#define PWM_DELAY (0.5f)
#define MINWINDOW (2.0f)     // us
#define PWM_HOLD (PWM_DELAY + MINWINDOW)
#define ADC_CONV_TIME (1.8f) // us;f = 128m/4;time = f*(12.5+13.5)
/*motor parameters*/
#define POLE_PAIRS (5u)
#define RS_PHASE (0.08f)
#define LD_PHASE (0.00025f)
#define LQ_PHASE (0.00025f)
#define IND_PHASE (LQ_PHASE)
#define EMF_VPP (2.466f)
#define EMF_PERIOD (95.99f) // ms
#define EMF_COEFF (float)((EMF_VPP * POLE_PAIRS * EMF_PERIOD) / (2 * 1.732f * 60))
#define FLUX_RATE (float)((1.414f * 6.2f / 1.732f) / (2 * _PI * ((1000 * POLE_PAIRS) / 60)))
#define VOLT_RATE (36.0f) // 36v/sqrt(3)
#define CURR_RATE (16.0f) // 14.5a
#define EFREQ_RATE (500.0f)

#define VOLT_BASE (float)(VOLT_RATE / 1.732f)    // 17.96
#define CURR_BASE (2*CURR_RATE)                    // 14.14
#define OMEGA_BASE (float)(2 * _PI * EFREQ_RATE) // 1884
#define T_BASE (float)(1 / OMEGA_BASE)
#define RS_BASE (float)(VOLT_BASE / CURR_BASE)
#define L_BASE (float)(RS_BASE * T_BASE)
#define FLUX_BASE (float)(VOLT_BASE * T_BASE)
#define SPEED_BASE (int16_t)((60 * EFREQ_RATE) / POLE_PAIRS)
/*foc parameters*/
#define STABLE_SCALE (int16_t)((MINWINDOW + DEADTIME + ADC_CONV_TIME) * (SYSTEM_FREQ / (TIMER_CLOCK_PRESCALER_SET + 1)))
#define SHIFT_SCALE (int16_t)((PWM_HOLD + DEADTIME) * (SYSTEM_FREQ / (TIMER_CLOCK_PRESCALER_SET + 1)))
#define COEFF_CURR Q14(((ADC_VREF / 2) / (GAIN_AMP * R_SHUNT)) / CURR_BASE)
#define COEFF_VOLT Q14(((ADC_VREF / 2) * (RES_PULL + RES_DOWN) / RES_DOWN) / VOLT_BASE)

#define BANDWIDTH_PLLLOOP (100u)
#define KP_PLLLOOP (100u)
#define KI_PLLLOOP (100u)
#define OUT_MAX_PLLLOOP (int16_t)(19661)
#define OUT_MIN_PLLLOOP (int16_t)(-OUT_MAX_PLLLOOP)

#define BANDWIDTH_CURRLOOP (300u)
#define KP_CURRLOOP (1000u)
#define KI_CURRLOOP (100u)
#define OUT_MAX_CURRLOOP (int16_t)(19661)
#define OUT_MIN_CURRLOOP (int16_t)(-OUT_MAX_CURRLOOP)

#define BANDWIDTH_SPDLOOP (50u)
#define BANDWIDTH_SPDLPF (80.0f)
#define KP_SPDLOOP (6000u)
#define KI_SPDLOOP (20u)
#define OUT_MAX_SPDLOOP (int16_t)(19660)
#define OUT_MIN_SPDLOOP (int16_t)(-OUT_MAX_SPDLOOP)

#define SPEED_TARGET_OPENLOOP (200.0f)
#define SPEED_SWITCH_OPENLOOP (180.0f)
#define SPEED_SLOPE (1.0f)
#define ALIGN_CURR_OPENLOOP (2.0f)
#define ALIGN_CURR_SLOPE (0.02f)
#define ALIGN_ANGLE Q16(0.25f)
#define START_CURR_OPENLOOP (3.5f)
#define IFCURR_TARGET (3.0f)
#define IFCURR_SLOPE (0.02f)

#define UQ_LIMIT Q14(0.9f)
#define UD_LIMIT Q14(0.43f)
#define MODULE_COEFF Q15(0.577)
/*Observer parameters*/
#define SMO_GAIN (0.85f)
#define SMO_ERRWIDTH (0.05f)
#define BANDWIDTH_EMFLPF (200.0f)

#define GAIN_SVCM (0.8f)
#define ONE_SHUNT_ENABLE (1)

#define SMO_ENABLE (1)
#define SVCM_ENABLE (0)
#endif
