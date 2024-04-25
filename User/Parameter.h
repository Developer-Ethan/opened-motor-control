#ifndef _PARAMETER_H_
#define _PARAMETER_H_
#include "DataCalc.h"

/*statemachine detect time*/
#define TIME_STABLE (20u)
#define TIME_CALIBRATE (20u)
#define TIME_IDLE (20u)
#define TIME_ALIGN (20u)
#define TIME_OPENLOOP (20u)
/*hardware parameters*/
#define R_SHUNT (0.005f)
#define GAIN_AMP (8.0f)
#define ADC_VREF (3.3f)
#define RES_PULL (51.0f) // kohm
#define RES_DOWN (3.0f)
/*foc parameters*/
#define PWM_FREQ (16000u)
#define PWM_PERIOD (1.0f / PWM_FREQ) // 50us
#define DEADTIME (1.125f)            // us
#define MINWINDOW (2.0f)             // us
#define ADC_CONV_TIME (0.8f)         // us;f = 128m/4;time = f*(12.5+13.5)
#define STABLE_SCALE (int16_t)((MINWINDOW + DEADTIME + ADC_CONV_TIME) * (128 / (TIMER_CLOCK_PRESCALER_SET + 1)))
#define SHIFT_SCALE (int16_t)((MINWINDOW + DEADTIME) * (128 / (TIMER_CLOCK_PRESCALER_SET + 1)))

#define RS_PHASE (0.74f)
#define LD_PHASE (0.44f)
#define LQ_PHASE (0.44f)
#define IND_PHASE (LQ_PHASE)
#define POLE_PAIRS (6u)
#define VOLT_RATE (22.0f)
#define CURR_RATE (14.5f)
#define EFREQ_RATE (300.0f)

#define VOLT_BASE (float)((VOLT_RATE * 1.414f) / 1.732f)
#define CURR_BASE (float)(CURR_RATE * 1.414f)      // 14.14
#define OMEGA_BASE (float)(2 * 3.14f * EFREQ_RATE) // 1884
#define T_BASE (float)(1 / OMEGA_BASE)
#define RS_BASE (float)(VOLT_BASE / CURR_BASE)
#define L_BASE (float)(RS_BASE * T_BASE)
#define SPEED_BASE (int16_t)((60 * EFREQ_RATE) / POLE_PAIRS)
#define COEFF_CURR ((ADC_VREF / (GAIN_AMP * R_SHUNT)) / (32767 * CURR_BASE))
#define COEFF_VOLT ((ADC_VREF * (RES_PULL + RES_DOWN) / RES_DOWN) / (32767 * VOLT_BASE))

#define BANDWIDTH_PLLLOOP (50u)
#define KP_PLLLOOP (100u)
#define KI_PLLLOOP (100u)
#define PIOUT_MAX_PLLLOOP (65535u)
#define PIOUT_MIN_PLLLOOP (0u)
#define IOUT_MAX_PLLLOOP (65535u)
#define IOUT_MIN_PLLLOOP (0u)

#define BANDWIDTH_CURRLOOP (300u)
#define KP_CURRLOOP (1000u)
#define KI_CURRLOOP (100u)
#define PIOUT_MAX_CURRLOOP (int32_t)(1.2f * 32767)
#define PIOUT_MIN_CURRLOOP (int32_t)(-PIOUT_MAX_CURRLOOP)
#define IOUT_MAX_CURRLOOP (int32_t)(1.2f * 32767)
#define IOUT_MIN_CURRLOOP (int32_t)(-PIOUT_MAX_CURRLOOP)

#define KP_SPDLOOP (1000u)
#define KI_SPDLOOP (100u)
#define PIOUT_MAX_SPDLOOP (int32_t)(1.2f * 32767)
#define PIOUT_MIN_SPDLOOP (-PIOUT_MAX_SPDLOOP)
#define IOUT_MAX_SPDLOOP (int32_t)(1.2f * 32767)
#define IOUT_MIN_SPDLOOP (-IOUT_MAX_SPDLOOP)

#define SPEED_TARGET_OPENLOOP (94.0f)
#define SPEED_SWITCH_OPENLOOP (80.0f)
#define SPEED_SLOPE (1.0f)
#define ALIGN_CURR_OPENLOOP (2.0f)
#define ALIGN_CURR_SLOPE (0.2f)
#define ALIGN_ANGLE Q16(0.0f)
#define START_CURR_OPENLOOP (2.0f)
#define IFCURR_TARGET (1.5f)
#define IFCURR_SLOPE (0.05f)

#define UQ_LIMIT Q15(0.9f)
#define UD_LIMIT Q15(0.43f)
#define MODULE_COEFF Q15(0.577)
#endif
