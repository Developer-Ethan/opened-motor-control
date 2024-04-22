#ifndef _FOC_H_
#define _FOC_H_
#include "stdint.h"
#include "LPF.h"
#include "LoopControl.h"
typedef struct
{
  int16_t Real;
  int16_t Imag;
  /* data */
} AXIS_DEF;

typedef struct
{
  int16_t Curr_SamplePoint_1st;
  int16_t Curr_SamplePoint_2nd;
  int16_t Offset_1st;
  int16_t Offset_2nd;
  uint16_t SampleCurr[5];
  /* data */
} SAMPLE_CURR_DEF;

typedef struct
{
  int16_t PhaseU;
  int16_t PhaseV;
  int16_t PhaseW;
  /* data */
} PHASE_CURR_DEF;

typedef struct
{
  float PhaseRes;
  float PhaseInd_D;
  float PhaseInd_Q;
  float PhaseInd;
  uint8_t PolePairs;
  float VoltRated;
  float CurrRated;
  float EfreqRated;

  float PhaseRes_Base;
  float PhaseInd_Base;
  float Volt_Base;
  float Curr_Base;
  int16_t Speed_Base;

  /* data */
} MOTOR_PARAMETER_DEF;

typedef struct
{
  AXIS_DEF StatCurr;
  AXIS_DEF StatVolt;
  AXIS_DEF RotaCurr;
  AXIS_DEF RotaVolt;
  SAMPLE_CURR_DEF Sample_Curr;
  uint16_t Sample_Volt;
  uint16_t PhaseInd_Pu;
  uint16_t PhaseRes_Pu;
  LPF_DEF RealFluxLPF;
  LPF_DEF ImagFluxLPF;
  LPF_DEF FluxAmpLPF;
  uint16_t FluxAngle;
  uint16_t AnglePLL;
  uint16_t Angle;
  int16_t IdRef;
  int16_t IqRef;
  int16_t Is;
  int16_t SpeedEst;
  int16_t TsPu;
  PHASE_CURR_DEF PhaseCurr;
  /* data */
} FOC_DEF;

typedef enum
{
  MotorPowerOn = 0,
  MotorStable,
  MotorCalibrate,
  MotorIdle,
  MotorAlign,
  MotorOpenLoop,
  MotorClosedLoop,
  MotorShutdown,
  MotorFault,
} MOTOR_STATE_DEF;

#define SQRT1_3 (18919)
#define SQRT_3 (56752)
#define BIT_MAX (16u)

void Foc_Init(void);
PHASE_CURR_DEF PhaseCurr_Get(FOC_DEF *pFoc);
AXIS_DEF ClarkeTransform(PHASE_CURR_DEF *pPhaseCurr);
AXIS_DEF ParkTransform(AXIS_DEF *pAxis, uint16_t ElecAngle);
AXIS_DEF iParkTransform(AXIS_DEF *pAxis, uint16_t ElecAngle);
uint16_t Angle_Given(OPENLOOP_DEF *pOpenLoop);
void LimitedCircle_Voltage(AXIS_DEF *pAxis);
void EstFlux_Ctr(void);

extern FOC_DEF Foc;

#endif
