/**************************************************************************************************/
/**
 * @file      : user_coeff.h
 * @brief     : User coeff design header file.
 *              - Platform: Z20K11xM
 * @version   : Demo
 * @date      : 27-Feb-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2022-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#ifndef _APPPARAMETER_H_
#define _APPPARAMETER_H_

#include "zxmathfp.h"
#include "MidLayer.h"

#define APP_Q15(dat) (int16_t)(32767 * dat)
#define APP_Q14(dat) (int16_t)(16384 * dat)
/****StallRotor Protection Param****/
#define Motor_StallRotor_Speed_Max (6000.0f)
#define MOTOR_STALLROTOR_SPEED_MAX APP_Q14(Motor_StallRotor_Speed_Max / APP_SPEED_BASE)
#define Motor_StallRotor_Speed_Min (500.0f)
#define MOTOR_STALLROTOR_SPEED_MIN APP_Q14(Motor_StallRotor_Speed_Min / APP_SPEED_BASE)
#define ESTI_EMF_SQUARE_MIN (76)
#define STALLROTOR_DETECT_TIME (200)
#define STALLROTOR_DETECTDELAY_TIME (500)
#define STALLROTOR_TYPE (0X0010)

/****DryRotor Protection Param****/
#define Motor_DryRotor_Speed_Min (1500.f)
#define MOTOR_DRYROTOR_SPEED_MIN APP_Q14(Motor_DryRotor_Speed_Min / APP_SPEED_BASE)
#define Motor_DryRotor_BusCurrent (1.0f)
#define MOTOR_DRYROTOR_BUSCURRENT APP_Q14(Motor_DryRotor_BusCurrent / APP_CURR_BASE)
#define DRYROTOR_DETECT_TIME (200)
#define DRYROTOR_DETECTDELAY_TIME (500)
#define DELAYDETECT_TIME (5000)
#define DRYROTOR_TYPE (0X0020)

/****OverCurrent Protection Param****/
#define OverCurrentValue1 (9.0f)
#define OVERCURRENT_VALUE1 APP_Q14(OverCurrentValue1 / APP_CURR_BASE)
#define OverCurrentValue2 (11.0f)
#define OVERCURRENT_VALUE2 APP_Q14(OverCurrentValue2 / APP_CURR_BASE)
#define OVERCURRENT_DETECT_TIME (200)

#define LimitCurrentValue_ReConstr (5.1f)
#define LIMITCURRENT_VALUE_RECONSTR APP_Q14(LimitCurrentValue_ReConstr / APP_CURR_BASE)
#define LimitCurrentValue_HwSamp (5.7f)
#define LIMITCURRENT_VALUE_HWSAMP APP_Q14(LimitCurrentValue_HwSamp / APP_CURR_BASE)

#define LimitCurrentValue1 (2.58f)
#define LIMITCURRENT_VALUE1 APP_Q14(LimitCurrentValue1 / APP_CURR_BASE)
#define LIMITCURRENT_DETECT_TIME (200)
#define OVERCURRENT_REC_DETECT_TIME (200)

#define OC_REDUCELOAD_SPEED (q15)(0.6 * FREQUENCY_MAX)
#define OVERCURRENT_TYPE (0X0008)

/****Temperature Protection Param****/
#define R_PULL (10.0f)
#define LimitTemperature_Value (3.38f)
#define LIMITTEMPERATURE_VALUE APP_Q14((LimitTemperature_Value / (LimitTemperature_Value + R_PULL)) * 5 / 5)
#define RecoverTemperature_Value (3.934f)
#define RECOVERTMPERATURE_VALUE APP_Q14((RecoverTemperature_Value / (RecoverTemperature_Value + R_PULL)) * 5 / 5)

#define OverTemperature_Value (2.522f)
#define OVERTEMPERATURE_VALUE APP_Q14((OverTemperature_Value / (OverTemperature_Value + R_PULL)) * 5 / 5)
#define RestartTemperature_Value (2.916f)
#define RESTARTTEMPERATURE_VALUE APP_Q14((RestartTemperature_Value / (RestartTemperature_Value + R_PULL)) * 5 / 5)

#define OT_REDUCELOAD_SPEED (int16_t)(0.6 * FREQUENCY_MAX)

#define LIMITTEMPERATURE_DETECT_TIME (200)
#define OVERTEMPERATURE_DETECT_TIME (200)
#define OTREC_DETECT_TIME (20000 - (STEADY_TIME_MS + CALIBRATION_TIME_MS))
#define LIMTREC_DETECT_TIME (20000)

/****LossSpeed Protection Param****/
#define LossSpeed_Value (1200.0f)
#define LOSSSPEED_VALUE APP_Q14(LossSpeed_Value / APP_SPEED_BASE)
#define LOSSSPEED_DETECT_TIME (4000)
#define LOSSSPEED_TYPE (0X0040)

/****LossPhase Protection Param****/
#define DETECT_TIME_LP (50)
#define DELAY_TIME_LP (1000)
#define THRESHOLD_LP (100)

/****Voltage Protection Param****/
#define UnderVoltage_Value (17.2f)
#define UNDERVOLTAGE_VALUE APP_Q14(UnderVoltage_Value / APP_VOLT_BASE)
#define UNDERVOLTAGE_DETECT_TIME (750)
#define OverVoltage_Value (32.6f)
#define OVERVOLTAGE_VALUE APP_Q14(OverVoltage_Value / APP_VOLT_BASE)
#define OVERVOLTAGE_DETECT_TIME (20)
#define UvRec_Value (18.2f)
#define UVREC_VALUE APP_Q14(UvRec_Value / APP_VOLT_BASE)
#define UVREC_DETECT_TIME (2000 - (STEADY_TIME_MS + CALIBRATION_TIME_MS))
#define OvRec_Value (31.6f)
#define OVREC_VALUE APP_Q14(OvRec_Value / APP_VOLT_BASE)
#define OVREC_DETECT_TIME (2000 - (STEADY_TIME_MS + CALIBRATION_TIME_MS))

/****Diagnose Voltage Param****/
#define DiagVoltage_Min (7.0f)
#define DIAGVOLTAGE_MIN APP_Q14(DiagVoltage_Min / APP_VOLT_BASE)
#define DiagVoltage_Max (35.0f)
#define DIAGVOLTAGE_MAX APP_Q14(DiagVoltage_Max / APP_VOLT_BASE)
#define DiagVoltage_Halt (36.0f)
#define DIAGVOLTAGE_HALT APP_Q14(DiagVoltage_Halt / APP_VOLT_BASE)
#define DIAGVOLTAGE_MAX_TIME (2000)
#define DIAGVOLTAGE_HALT_TIME (20)
#define REC_OVER_VOLTAG_TIME (2000)

/****Fault Enable and Disable Param****/
#define FAULT_DETECT_ENABLE (1)

#define DRYROTOR_DETECT_ENABLE (1)
#define STALLROTOR_DETECT_ENABLE (1)
#define BUSCURRENT_DETECT_ENABLE (1)
#define TEMPERATURE_DETECT_ENABLE (1)
#define LOSSSPEED_DETECT_ENABLE (1)
#define LOSSPHASE_DETECT_ENABLE (1)
#define VOLTAGE_DETECT_ENABLE (1)
#define DIAGVOLTAGE_DETECT_ENABLE (1)
#define RECOVERY_FAULT_ENABLE (1)
#define SWOc_ENABLE (1)
/*Fault Recovery*/
#define RECOVERY_TIME_1st (1000)
#define RECOVERY_TIME_2nd (5000)
#define RECOVERY_TIME_3rd_10th (20000)
#define RECOVERY_TIME_11th_20th (120000)

/*Speed Adjustment*/

#define Duty_0 (0)
#define Duty_7 (0.07)
#define Duty_12 (0.12)
#define Duty_17 (0.17)
#define Duty_93 (0.93)
#define Duty_100 (1.0)
#define Hysteresis (0.008) // 0.005*32767

#define DUTY_0 (uint16_t)(Duty_0 * 32767) // 0*32767
#define DUTY_7 (uint16_t)(Duty_7 * 32767) // 0.07*32767
#define DUTY_12 (uint16_t)(Duty_12 * 32767)
#define DUTY_17 (uint16_t)(Duty_17 * 32767)
#define DUTY_93 (uint16_t)(Duty_93 * 32767)
#define DUTY_100 (uint16_t)(Duty_100 * 32767)
#define HYSTERESIS (uint16_t)(Hysteresis * 32767) // 0.005*32767

#define SPEED_MAX (5200.0f)
#define SPEED_MIN (1500.0f)
#define FREQUENCY_MAX APP_Q14(SPEED_MAX / APP_SPEED_BASE)
#define FREQUENCY_MIN APP_Q14(SPEED_MIN / APP_SPEED_BASE)
#define FREQUENCY_K ((float)(FREQUENCY_MAX - FREQUENCY_MIN) / (DUTY_93 - DUTY_17))

#define CurrentThreshold_DryRotor (1.0f)
#define CURRENT_DRYROTOR APP_Q14(CurrentThreshold_DryRotor / APP_CURR_BASE)
#define Speed_LoopSwitch (5147.0f)
#define SPEED_LOOPSWITCH APP_Q14(Speed_LoopSwitch / APP_SPEED_BASE)
#define Speed_Return (50.0f)
#define SPEED_RETURN APP_Q14(Speed_Return / APP_SPEED_BASE)
#define Speed_Limit (5600.0f)
#define SPEED_LIMIT APP_Q14(Speed_Limit / APP_SPEED_BASE)
#define Current_LoopSwitch (4.8f)
#define CURRENT_LOOPSWITCH APP_Q14(Current_LoopSwitch / APP_CURR_BASE)
#define ReturnCurrent (1.0f)
#define RETURNCURRENT APP_Q14(ReturnCurrent / APP_CURR_BASE)

#define Current_Target (6.0f)
#define Voltage_Rate (24.0f)
#define POWER_TARGET APP_Q14((Current_Target * Voltage_Rate) / (APP_CURR_BASE * APP_VOLT_BASE))

/*Diagnose*/

#define SEND_TIME (5)

#define T_HIGH_DRYROTOR (1000)
#define T_LOW_DRYROTOR (1000)

#define T_HIGH_StallOrOc (1000)
#define T_LOW_StallOrOc (1500)

#define T_HIGH_OT (1000)
#define T_LOW_OT (2000)

#define T_HIGH_LossSpeed (1000)
#define T_LOW_LossSpeed (2500)

#define T_HIGH_NoFault (4500)
#define T_LOW_NoFault (500)

typedef enum
{
    PowerOnState,
    IdleState,
    OpenLoopState,
    CloseLoopState,
    ErrorState,
} APP_MOTOR_STATE;
#endif /* USER_COEFF_H */
