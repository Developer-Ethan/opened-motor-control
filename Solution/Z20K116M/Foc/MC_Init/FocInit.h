#ifndef _FOC_H_
#define _FOC_H_
#include "stdint.h"
#include "LPF.h"
#include "SpdLoop.h"
#include "AxisTransform.h"
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
  float FluxBase;

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
  int16_t Sample_Volt;
  uint16_t PhaseInd;
  uint16_t PhaseRes;
  float PhaseInd_Pu;
  float PhaseRes_Pu;
  LPF_DEF Lpf_EmfEstReal;
  LPF_DEF Lpf_EmfEstImag;
  uint16_t AngleEst;
  uint16_t AngleOpen;
  uint16_t Angle;
  uint16_t Angle_Align;
  int16_t IdRef;
  int16_t IqRef;
  int16_t Is;
  int16_t SpeedEst;
  float TsPu;
  int16_t Ts;
  float FluxPu;
  int16_t Flux;
  int16_t SvcmGain;
  float BandWidthPu_CurrLoop;
  float BandWidthPu_PllLoop;
  float BandWidthPu_SpdLoop;
  SMO_CTRL_DEF Smo_Ctrl;
  /* data */
} FOC_DEF;

#define SQRT1_3 (18919)
#define SQRT_3 (56752)
#define BIT_MAX (16u)

void Foc_Init(void);
void ClosedLoop_Init(void);
void OpenLoop_Init(void);
void LimitedCircle_Voltage(AXIS_DEF *pAxis);
extern FOC_DEF Foc;
#endif
