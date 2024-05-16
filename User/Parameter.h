#ifndef _PARAMETER_H_
#define _PARAMETER_H_
#include "DataCalc.h"

#define _PI (3.1415926535f)
/*statemachine detect time*/
#define TIME_STABLE (40u)
#define TIME_CALIBRATE (20u)
#define TIME_IDLE (20u)
#define TIME_ALIGN (200u)
#define TIME_OPENLOOP (4000u)
/*hardware parameters*/
#define R_SHUNT (0.005f)
#define GAIN_AMP (8.0f)
#define ADC_VREF (3.3f)
#define RES_PULL (51.0f) // kohm
#define RES_DOWN (3.0f)
#define VOLTAGE_MAX_ADCSAMPLE (ADC_VREF * (RES_PULL + RES_DOWN) / RES_DOWN)
#define CURRENT_MAX_ADCSAMPLE (ADC_VREF / R_SHUNT / GAIN_AMP)
/*foc parameters*/
#define PWM_FREQ (16000u)
#define PWM_PERIOD (1.0f / PWM_FREQ) // 50us
#define DEADTIME (1.0f)              // us
#define MINWINDOW (2.0f)             // us
#define ADC_CONV_TIME (0.8f)         // us;f = 128m/4;time = f*(12.5+13.5)
#define STABLE_SCALE (int16_t)((MINWINDOW + DEADTIME + ADC_CONV_TIME) * (128 / (TIMER_CLOCK_PRESCALER_SET + 1)))
#define SHIFT_SCALE (int16_t)((MINWINDOW + DEADTIME) * (128 / (TIMER_CLOCK_PRESCALER_SET + 1)))

#define RS_PHASE (0.08f)
#define LD_PHASE (0.00025f)
#define LQ_PHASE (0.00025f)
#define EMF_VPP (2.466f)
#define EMF_PERIOD (95.99f) // ms
#define EMF_COEFF (float)((EMF_VPP * POLE_PAIRS * EMF_PERIOD) / (2 * 1.732f * 60))
#define FLUX_RATE (float)((1.414f * EMF_COEFF / 1.732f) / (2 * _PI * ((1000 * POLE_PAIRS) / 60)))
#define IND_PHASE (LQ_PHASE)
#define POLE_PAIRS (5u)
#define VOLT_RATE (36.0f) // 36v/sqrt(3)
#define CURR_RATE (16.0f) // 14.5a
#define EFREQ_RATE (500.0f)

#define VOLT_BASE (float)(VOLT_RATE / 1.732f)    // 17.96
#define CURR_BASE (CURR_RATE)                    // 14.14
#define OMEGA_BASE (float)(2 * _PI * EFREQ_RATE) // 1884
#define T_BASE (float)(1 / OMEGA_BASE)
#define RS_BASE (float)(VOLT_BASE / CURR_BASE)
#define L_BASE (float)(RS_BASE * T_BASE)
#define FLUX_BASE (float)(VOLT_BASE * T_BASE)
#define SPEED_BASE (int16_t)((60 * EFREQ_RATE) / POLE_PAIRS)
#define COEFF_CURR ((ADC_VREF / (GAIN_AMP * R_SHUNT)) / (32767 * CURR_BASE))
#define COEFF_VOLT ((ADC_VREF * (RES_PULL + RES_DOWN) / RES_DOWN) / (32767 * VOLT_BASE))

#define BANDWIDTH_PLLLOOP (100u)
#define KP_PLLLOOP (100u)
#define KI_PLLLOOP (100u)
#define OUT_MAX_PLLLOOP (19661)
#define OUT_MIN_PLLLOOP (-OUT_MAX_PLLLOOP)

#define BANDWIDTH_CURRLOOP (300u)
#define KP_CURRLOOP (1000u)
#define KI_CURRLOOP (100u)
#define OUT_MAX_CURRLOOP (int32_t)(19661)
#define OUT_MIN_CURRLOOP (int32_t)(-OUT_MAX_CURRLOOP)

#define KP_SPDLOOP (1000u)
#define KI_SPDLOOP (100u)
#define OUT_MAX_SPDLOOP (int32_t)(19660)
#define OUT_MIN_SPDLOOP (-OUT_MAX_SPDLOOP)

#define SPEED_TARGET_OPENLOOP (94.0f)
#define SPEED_SWITCH_OPENLOOP (80.0f)
#define SPEED_SLOPE (1.0f)
#define ALIGN_CURR_OPENLOOP (2.0f)
#define ALIGN_CURR_SLOPE (0.02f)
#define ALIGN_ANGLE Q16(0.25f)
#define START_CURR_OPENLOOP (4.0f)
#define IFCURR_TARGET (4.0f)
#define IFCURR_SLOPE (0.05f)

#define UQ_LIMIT Q14(0.9f)
#define UD_LIMIT Q14(0.43f)
#define MODULE_COEFF Q15(0.577)

#define SMO_GAIN (0.85f)
#define SMO_ERRWIDTH (0.05f)
#define BANDWIDTH_EMFLPF (200.0f)

#define GAIN_SVCM (0.8f)
#define ONE_SHUNT_ENABLE (1)

#define SMO_ENABLE (0)
#define SVCM_ENABLE (1)
#endif
