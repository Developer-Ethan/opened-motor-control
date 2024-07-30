/*
 * File: FOC_Ctrl_CodeModel_types.h
 *
 * Code generated for Simulink model 'FOC_Ctrl_CodeModel'.
 *
 * Model version                  : 1.22
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Mon Jul 29 10:46:05 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. ROM efficiency
 *    3. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_FOC_Ctrl_CodeModel_types_h_
#define RTW_HEADER_FOC_Ctrl_CodeModel_types_h_
#include "rtwtypes.h"

/* Model Code Variants */
#ifndef DEFINED_TYPEDEF_FOR_structAxis_
#define DEFINED_TYPEDEF_FOR_structAxis_

typedef struct {
  real32_T Real;
  real32_T Imag;
} structAxis;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structCurrentABC_
#define DEFINED_TYPEDEF_FOR_structCurrentABC_

typedef struct {
  real32_T iA;
  real32_T iB;
  real32_T iC;
} structCurrentABC;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structOffset_
#define DEFINED_TYPEDEF_FOR_structOffset_

typedef struct {
  real32_T iA;
  real32_T iB;
  real32_T iDC;
} structOffset;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structCurrent_
#define DEFINED_TYPEDEF_FOR_structCurrent_

typedef struct {
  structAxis StatCurr;
  structAxis RotaCurr;
  structCurrentABC iABC;
  structOffset Offset;
} structCurrent;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structVoltageADC_
#define DEFINED_TYPEDEF_FOR_structVoltageADC_

typedef struct {
  real32_T uA;
  real32_T uB;
  real32_T uC;
} structVoltageADC;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structVoltage_
#define DEFINED_TYPEDEF_FOR_structVoltage_

typedef struct {
  structAxis RotaVolt;
  structAxis StatVolt;
  structVoltageADC uABC;
} structVoltage;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structDCbus_
#define DEFINED_TYPEDEF_FOR_structDCbus_

typedef struct {
  real32_T Voltage;
  real32_T Current;
} structDCbus;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structHallSignal_
#define DEFINED_TYPEDEF_FOR_structHallSignal_

typedef struct {
  boolean_T HallA;
  boolean_T HallB;
  boolean_T HallC;
} structHallSignal;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structHallCalc_
#define DEFINED_TYPEDEF_FOR_structHallCalc_

typedef struct {
  boolean_T HallXOR;
  boolean_T HallEdgeEvent;
  uint8_T HallSum;
} structHallCalc;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structHallSpd_
#define DEFINED_TYPEDEF_FOR_structHallSpd_

typedef struct {
  uint32_T HallStart;
  uint32_T HallEnd;
  real32_T HallSpd;
} structHallSpd;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structHall_
#define DEFINED_TYPEDEF_FOR_structHall_

typedef struct {
  structHallSignal HallSignal;
  structHallCalc HallCalc;
  structHallSpd HallSpd;
} structHall;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structSnls_
#define DEFINED_TYPEDEF_FOR_structSnls_

typedef struct {
  real32_T VelocitySMO;
  real32_T VelocityFlux;
  real32_T AngleSMO;
  real32_T AngleFlux;
} structSnls;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structSignals_
#define DEFINED_TYPEDEF_FOR_structSignals_

typedef struct {
  structCurrent Current;
  structVoltage Voltage;
  structDCbus DCbus;
  structHall Hall;
  structSnls Snls;
  real32_T Speed;
  real32_T Position;
} structSignals;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structPI_
#define DEFINED_TYPEDEF_FOR_structPI_

typedef struct {
  real32_T Ts;
  real32_T Ki;
  real32_T Kp;
} structPI;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structRegulator_
#define DEFINED_TYPEDEF_FOR_structRegulator_

typedef struct {
  structPI SpdPI;
  structPI idPI;
  structPI iqPI;
} structRegulator;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structCntrlReq_
#define DEFINED_TYPEDEF_FOR_structCntrlReq_

typedef struct {
  real32_T SpdReq;
  real32_T idReq;
  real32_T iqReq;
  real32_T udReq;
  real32_T uqReq;
} structCntrlReq;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structLED_
#define DEFINED_TYPEDEF_FOR_structLED_

typedef struct {
  boolean_T LEDR;
  boolean_T LEDG;
  boolean_T LEDB;
} structLED;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structMotorCtrl_
#define DEFINED_TYPEDEF_FOR_structMotorCtrl_

typedef struct {
  structCntrlReq CntrlReq;
  structLED LED;
  boolean_T MotorOnOff;
  boolean_T FaultSetClear;
} structMotorCtrl;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structMeasRaw_
#define DEFINED_TYPEDEF_FOR_structMeasRaw_

typedef struct {
  uint16_T PotRaw;
  uint16_T iARaw;
  uint16_T iBRaw;
  uint16_T iDCRaw;
  uint16_T vDCRaw;
} structMeasRaw;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structDuty_
#define DEFINED_TYPEDEF_FOR_structDuty_

typedef struct {
  real32_T DutyA;
  real32_T DutyB;
  real32_T DutyC;
} structDuty;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structFOC_
#define DEFINED_TYPEDEF_FOR_structFOC_

typedef struct {
  structSignals Signals;
  structRegulator Regulator;
  structMotorCtrl MotorCtrl;
  structMeasRaw MeasRaw;
  structDuty Duty;
} structFOC;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structRst_
#define DEFINED_TYPEDEF_FOR_structRst_

typedef struct {
  real32_T outerRst;
  real32_T innerCtrRst;
  real32_T snlsRst;
} structRst;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structFocSpd_
#define DEFINED_TYPEDEF_FOR_structFocSpd_

typedef struct {
  real32_T EstOmega;
  real32_T OpenOmega;
} structFocSpd;

#endif

#ifndef DEFINED_TYPEDEF_FOR_structFocTheta_
#define DEFINED_TYPEDEF_FOR_structFocTheta_

typedef struct {
  real32_T Angle;
  real32_T OpenAngle;
  real32_T EstAngle;
} structFocTheta;

#endif

#ifndef DEFINED_TYPEDEF_FOR_strcutFocInternalPara_
#define DEFINED_TYPEDEF_FOR_strcutFocInternalPara_

typedef struct {
  structRst Rst;
  structFocSpd FocSpd;
  structFocTheta FocTheta;
} strcutFocInternalPara;

#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_FOC_Ctrl_CodeModel_T RT_MODEL_FOC_Ctrl_CodeModel_T;

#endif                              /* RTW_HEADER_FOC_Ctrl_CodeModel_types_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
