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
  uint32_t SampleCurrSum_1st;
  uint32_t SampleCurrSum_2nd;
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
  float Emf_Coeff;
  float FluxRated;

  float PhaseRes_Base;
  float PhaseInd_Base;
  float Volt_Base;
  float Curr_Base;
  int16_t Speed_Base;
  float OmageBase;

  /* data */
} MOTOR_PARAMETER_DEF;

typedef struct
{
  int16_t Factor1;
  int16_t Factor2;
  int16_t SmoGain;
  int16_t SmoErrWidth;
	int16_t SmoSlope;
  int16_t EmfEst_Real;
  int16_t EmfEst_Imag;
	int16_t EmfEstLpf_Real;
  int16_t EmfEstLpf_Imag;
  int16_t LastCurrEst_Real;
  int16_t LastCurrEst_Imag;
  /* data */
} SMO_CTRL_DEF;

typedef struct
{
  AXIS_DEF StatCurr;
  AXIS_DEF StatVolt;
  AXIS_DEF RotaCurr;
  AXIS_DEF RotaVolt;
  SAMPLE_CURR_DEF Sample_Curr;
  uint16_t Sample_Volt;
  uint16_t PhaseInd;
  uint16_t PhaseRes;
  float PhaseInd_Pu;
  float PhaseRes_Pu;
  LPF_DEF RealFluxLPF;
  LPF_DEF ImagFluxLPF;
  LPF_DEF FluxAmpLPF;
  LPF_DEF Lpf_EmfEstReal;
	LPF_DEF Lpf_EmfEstImag;
  uint16_t FluxAngle;
  uint16_t AnglePLL;
	uint16_t AngleOpen;
  uint16_t Angle;
  uint16_t Angle_Align;
  int16_t IdRef;
  int16_t IqRef;
  int16_t Is;
  int16_t SpeedEst;
  float TsPu;
  int16_t Ts;
  PHASE_CURR_DEF PhaseCurr;
  float BandWidthPu_CurrLoop;
	float BandWidthPu_PllLoop;
  SMO_CTRL_DEF Smo_Ctrl;
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
extern void OpenLoop_Init(void);
void LimitedCircle_Voltage(AXIS_DEF *pAxis);
void EstFlux_Ctr(void);
void EstSmo_Ctr(void);
extern FOC_DEF Foc;

#endif
