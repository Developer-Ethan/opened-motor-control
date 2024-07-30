/*
 * File: FOC_Ctrl_CodeModel.c
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

#include "FOC_Ctrl_CodeModel.h"
#include "FOC_Ctrl_CodeModel_private.h"

/* Named constants for Chart: '<S18>/Chart' */
#define FOC_Ctrl_CodeMode_IN_AlignStage ((uint8_T)1U)
#define FOC_Ctrl_CodeMode_IN_TrackStage ((uint8_T)4U)
#define FOC_Ctrl_CodeModel_IN_OpenStage ((uint8_T)2U)
#define FOC_Ctrl_CodeModel_IN_RunStage ((uint8_T)3U)

/* Named constants for Chart: '<S3>/Chart' */
#define FOC_Ctrl_Cod_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define FOC_Ctrl_CodeMod_IN_Calibration ((uint8_T)1U)
#define FOC_Ctrl_CodeModel_IN_Faults   ((uint8_T)1U)
#define FOC_Ctrl_CodeModel_IN_Initial  ((uint8_T)2U)
#define FOC_Ctrl_CodeModel_IN_NormalRun ((uint8_T)2U)
#define FOC_Ctrl_CodeModel_IN_Ready    ((uint8_T)3U)
#define FOC_Ctrl_CodeModel_IN_Run      ((uint8_T)4U)

/* Block signals and states (default storage) */
DW_FOC_Ctrl_CodeModel_T FOC_Ctrl_CodeModel_DW;

/* External inputs (root inport signals with default storage) */
ExtU_FOC_Ctrl_CodeModel_T FOC_Ctrl_CodeModel_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_FOC_Ctrl_CodeModel_T FOC_Ctrl_CodeModel_Y;

/* Real-time model */
static RT_MODEL_FOC_Ctrl_CodeModel_T FOC_Ctrl_CodeModel_M_;
RT_MODEL_FOC_Ctrl_CodeModel_T *const FOC_Ctrl_CodeModel_M =
  &FOC_Ctrl_CodeModel_M_;

/* System initialize for function-call system: '<S8>/InitFunc' */
void FOC_Ctrl_CodeMode_InitFunc_Init(real32_T rty_dutyOut[3], boolean_T
  rty_ledOut[3])
{
  /* SystemInitialize for SignalConversion generated from: '<S11>/dutyOut' */
  rty_dutyOut[0] = 0.0F;

  /* SystemInitialize for SignalConversion generated from: '<S11>/ledOut' */
  rty_ledOut[0] = true;

  /* SystemInitialize for SignalConversion generated from: '<S11>/dutyOut' */
  rty_dutyOut[1] = 0.0F;

  /* SystemInitialize for SignalConversion generated from: '<S11>/ledOut' */
  rty_ledOut[1] = true;

  /* SystemInitialize for SignalConversion generated from: '<S11>/dutyOut' */
  rty_dutyOut[2] = 0.0F;

  /* SystemInitialize for SignalConversion generated from: '<S11>/ledOut' */
  rty_ledOut[2] = true;
}

/* Output and update for function-call system: '<S8>/InitFunc' */
void FOC_Ctrl_CodeModel_InitFunc(real32_T rty_dutyOut[3], boolean_T rty_ledOut[3],
  structFOC *rtd_varFOC)
{
  /* SignalConversion generated from: '<S11>/dutyOut' */
  rty_dutyOut[0] = 0.0F;

  /* SignalConversion generated from: '<S11>/ledOut' */
  rty_ledOut[0] = true;

  /* SignalConversion generated from: '<S11>/dutyOut' */
  rty_dutyOut[1] = 0.0F;

  /* SignalConversion generated from: '<S11>/ledOut' */
  rty_ledOut[1] = true;

  /* SignalConversion generated from: '<S11>/dutyOut' */
  rty_dutyOut[2] = 0.0F;

  /* SignalConversion generated from: '<S11>/ledOut' */
  rty_ledOut[2] = true;

  /* DataStoreWrite: '<S11>/Data Store Write5' incorporates:
   *  Constant: '<S11>/Constant'
   */
  rtd_varFOC->Signals.Current.iABC.iA = 0.0F;
  rtd_varFOC->Signals.Current.iABC.iB = 0.0F;
  rtd_varFOC->Signals.Current.iABC.iC = 0.0F;
  rtd_varFOC->Signals.Current.Offset.iA = 0.0F;
  rtd_varFOC->Signals.Current.Offset.iB = 0.0F;
  rtd_varFOC->Signals.Current.Offset.iDC = 0.0F;
  rtd_varFOC->Signals.Current.StatCurr.Real = 0.0F;
  rtd_varFOC->Signals.Current.StatCurr.Imag = 0.0F;
  rtd_varFOC->Signals.Current.RotaCurr.Real = 0.0F;
  rtd_varFOC->Signals.Current.RotaCurr.Imag = 0.0F;

  /* DataStoreWrite: '<S11>/Data Store Write1' incorporates:
   *  Constant: '<S11>/Constant1'
   */
  rtd_varFOC->Signals.Voltage.uABC.uA = 0.0F;
  rtd_varFOC->Signals.Voltage.uABC.uB = 0.0F;
  rtd_varFOC->Signals.Voltage.uABC.uC = 0.0F;
  rtd_varFOC->Signals.Voltage.RotaVolt.Real = 0.0F;
  rtd_varFOC->Signals.Voltage.RotaVolt.Imag = 0.0F;
  rtd_varFOC->Signals.Voltage.StatVolt.Real = 0.0F;
  rtd_varFOC->Signals.Voltage.StatVolt.Imag = 0.0F;

  /* DataStoreWrite: '<S11>/Data Store Write2' incorporates:
   *  Constant: '<S11>/Constant2'
   */
  rtd_varFOC->Signals.DCbus.Voltage = 0.0F;
  rtd_varFOC->Signals.DCbus.Current = 0.0F;

  /* DataStoreWrite: '<S11>/Data Store Write3' incorporates:
   *  Constant: '<S11>/Constant2'
   */
  rtd_varFOC->Signals.Hall.HallSpd.HallSpd = 0.0F;

  /* DataStoreWrite: '<S11>/Data Store Write4' incorporates:
   *  Constant: '<S11>/Constant2'
   *  Constant: '<S11>/Constant9'
   */
  rtd_varFOC->Signals.Speed = 30.0F;
  rtd_varFOC->Signals.Position = 0.0F;

  /* DataStoreWrite: '<S11>/Data Store Write7' incorporates:
   *  Constant: '<S11>/Constant5'
   *  Constant: '<S11>/Constant8'
   */
  rtd_varFOC->MotorCtrl.CntrlReq.SpdReq = 0.0F;
  rtd_varFOC->MotorCtrl.CntrlReq.idReq = 0.0F;
  rtd_varFOC->MotorCtrl.CntrlReq.iqReq = 0.8F;
  rtd_varFOC->MotorCtrl.CntrlReq.udReq = 0.0F;
  rtd_varFOC->MotorCtrl.CntrlReq.uqReq = 0.0F;
}

/* System initialize for function-call system: '<S8>/FaultFunc' */
void FOC_Ctrl_CodeMod_FaultFunc_Init(real32_T rty_dutyOut[3], boolean_T
  rty_ledOut[3])
{
  /* SystemInitialize for SignalConversion generated from: '<S10>/dutyOut' */
  rty_dutyOut[0] = 0.0F;

  /* SystemInitialize for SignalConversion generated from: '<S10>/ledOut' */
  rty_ledOut[0] = false;

  /* SystemInitialize for SignalConversion generated from: '<S10>/dutyOut' */
  rty_dutyOut[1] = 0.0F;

  /* SystemInitialize for SignalConversion generated from: '<S10>/ledOut' */
  rty_ledOut[1] = true;

  /* SystemInitialize for SignalConversion generated from: '<S10>/dutyOut' */
  rty_dutyOut[2] = 0.0F;

  /* SystemInitialize for SignalConversion generated from: '<S10>/ledOut' */
  rty_ledOut[2] = true;
}

/* Output and update for function-call system: '<S8>/FaultFunc' */
void FOC_Ctrl_CodeModel_FaultFunc(real32_T rty_dutyOut[3], boolean_T rty_ledOut
  [3])
{
  /* SignalConversion generated from: '<S10>/dutyOut' */
  rty_dutyOut[0] = 0.0F;

  /* SignalConversion generated from: '<S10>/ledOut' */
  rty_ledOut[0] = false;

  /* SignalConversion generated from: '<S10>/dutyOut' */
  rty_dutyOut[1] = 0.0F;

  /* SignalConversion generated from: '<S10>/ledOut' */
  rty_ledOut[1] = true;

  /* SignalConversion generated from: '<S10>/dutyOut' */
  rty_dutyOut[2] = 0.0F;

  /* SignalConversion generated from: '<S10>/ledOut' */
  rty_ledOut[2] = true;
}

/* System initialize for function-call system: '<S8>/ReadyFunc' */
void FOC_Ctrl_CodeMod_ReadyFunc_Init(real32_T rty_dutyOut[3], boolean_T
  rty_ledOut[3])
{
  /* SystemInitialize for SignalConversion generated from: '<S13>/dutyOut' */
  rty_dutyOut[0] = 0.0F;

  /* SystemInitialize for SignalConversion generated from: '<S13>/ledOut' */
  rty_ledOut[0] = true;

  /* SystemInitialize for SignalConversion generated from: '<S13>/dutyOut' */
  rty_dutyOut[1] = 0.0F;

  /* SystemInitialize for SignalConversion generated from: '<S13>/ledOut' */
  rty_ledOut[1] = false;

  /* SystemInitialize for SignalConversion generated from: '<S13>/dutyOut' */
  rty_dutyOut[2] = 0.0F;

  /* SystemInitialize for SignalConversion generated from: '<S13>/ledOut' */
  rty_ledOut[2] = true;
}

/* Output and update for function-call system: '<S8>/ReadyFunc' */
void FOC_Ctrl_CodeModel_ReadyFunc(real32_T rty_dutyOut[3], boolean_T rty_ledOut
  [3])
{
  /* SignalConversion generated from: '<S13>/dutyOut' */
  rty_dutyOut[0] = 0.0F;

  /* SignalConversion generated from: '<S13>/ledOut' */
  rty_ledOut[0] = true;

  /* SignalConversion generated from: '<S13>/dutyOut' */
  rty_dutyOut[1] = 0.0F;

  /* SignalConversion generated from: '<S13>/ledOut' */
  rty_ledOut[1] = false;

  /* SignalConversion generated from: '<S13>/dutyOut' */
  rty_dutyOut[2] = 0.0F;

  /* SignalConversion generated from: '<S13>/ledOut' */
  rty_ledOut[2] = true;
}

/* System initialize for function-call system: '<S8>/NormalRunFunc' */
void FOC_Ctrl_Cod_NormalRunFunc_Init(boolean_T rty_ledOut[3])
{
  /* SystemInitialize for SignalConversion generated from: '<S12>/ledOut' */
  rty_ledOut[0] = true;
  rty_ledOut[1] = false;
  rty_ledOut[2] = false;
}

/* Enable for function-call system: '<S8>/NormalRunFunc' */
void FOC_Ctrl_C_NormalRunFunc_Enable(DW_NormalRunFunc_FOC_Ctrl_Cod_T *localDW)
{
  localDW->NormalRunFunc_RESET_ELAPS_T = true;

  /* Enable for DiscreteIntegrator: '<S30>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_SYSTEM_ = 1U;

  /* Enable for DiscreteIntegrator: '<S30>/Discrete-Time Integrator2' */
  localDW->DiscreteTimeIntegrator2_SYSTEM_ = 1U;

  /* Enable for Atomic SubSystem: '<S18>/PLLObserver1' */
  FOC_Ctrl_Co_PLLObserver1_Enable(&localDW->PLLObserver1);

  /* End of Enable for SubSystem: '<S18>/PLLObserver1' */
}

/* Output and update for function-call system: '<S8>/NormalRunFunc' */
void FOC_Ctrl_CodeMode_NormalRunFunc(RT_MODEL_FOC_Ctrl_CodeModel_T * const
  FOC_Ctrl_CodeModel_M, const uint16_T rtu_dataRaw[5], real32_T rty_dutyOut[3],
  boolean_T rty_ledOut[3], DW_NormalRunFunc_FOC_Ctrl_Cod_T *localDW, structFOC
  *rtd_varFOC)
{
  real32_T DiscreteTimeIntegrator1;
  real32_T DiscreteTimeIntegrator2;
  real32_T rtb_DataTypeConversion2_j;
  real32_T rtb_Fcn1_g2;
  real32_T rtb_Gain2_f;
  real32_T rtb_Gain3_l;
  real32_T rtb_Gain6_i;
  real32_T rtb_Saturation1_h;
  real32_T rtb_Subtract_j;
  real32_T rtb_Sum2_a;
  real32_T rtb_Sum2_p;
  uint32_T NormalRunFunc_ELAPS_T;
  if (localDW->NormalRunFunc_RESET_ELAPS_T) {
    NormalRunFunc_ELAPS_T = 0U;
  } else {
    NormalRunFunc_ELAPS_T = FOC_Ctrl_CodeModel_M->Timing.clockTick0 -
      localDW->NormalRunFunc_PREV_T;
  }

  localDW->NormalRunFunc_PREV_T = FOC_Ctrl_CodeModel_M->Timing.clockTick0;
  localDW->NormalRunFunc_RESET_ELAPS_T = false;

  /* SignalConversion generated from: '<S12>/ledOut' */
  rty_ledOut[0] = true;
  rty_ledOut[1] = false;
  rty_ledOut[2] = false;

  /* Gain: '<S19>/Gain2' incorporates:
   *  DataStoreRead: '<S19>/Data Store Read2'
   *  DataTypeConversion: '<S19>/Data Type Conversion4'
   *  Sum: '<S19>/Sum1'
   */
  rtb_Gain2_f = (rtd_varFOC->Signals.Current.Offset.iB - (real32_T)rtu_dataRaw[1])
    * 0.0152625153F;

  /* Gain: '<S19>/Gain3' incorporates:
   *  DataStoreRead: '<S19>/Data Store Read2'
   *  DataTypeConversion: '<S19>/Data Type Conversion'
   *  Sum: '<S19>/Sum'
   */
  rtb_Gain3_l = (rtd_varFOC->Signals.Current.Offset.iA - (real32_T)rtu_dataRaw[0])
    * 0.0152625153F;

  /* Gain: '<S19>/Gain6' incorporates:
   *  Sum: '<S19>/Sum2'
   */
  rtb_Gain6_i = -(rtb_Gain3_l + rtb_Gain2_f);

  /* Gain: '<S29>/Gain' incorporates:
   *  DataStoreWrite: '<S12>/Data Store Write1'
   *  Sum: '<S29>/Add'
   */
  rtd_varFOC->Signals.Current.StatCurr.Imag = (rtb_Gain2_f - rtb_Gain6_i) *
    0.577350259F;

  /* Trigonometry: '<S26>/Sin' incorporates:
   *  DataStoreRead: '<S18>/Data Store Read'
   *  Trigonometry: '<S28>/Sin'
   */
  rtb_Sum2_p = sinf(localDW->FocInternalPara.FocTheta.Angle);

  /* Trigonometry: '<S26>/Cos' incorporates:
   *  DataStoreRead: '<S18>/Data Store Read'
   *  Trigonometry: '<S28>/Cos'
   */
  rtb_DataTypeConversion2_j = cosf(localDW->FocInternalPara.FocTheta.Angle);

  /* Sum: '<S26>/Add' incorporates:
   *  DataStoreWrite: '<S12>/Data Store Write1'
   *  Product: '<S26>/Product'
   *  Product: '<S26>/Product1'
   *  Trigonometry: '<S26>/Cos'
   *  Trigonometry: '<S26>/Sin'
   */
  rtd_varFOC->Signals.Current.RotaCurr.Real =
    rtd_varFOC->Signals.Current.StatCurr.Imag * rtb_Sum2_p +
    rtb_DataTypeConversion2_j * rtb_Gain3_l;

  /* DiscreteIntegrator: '<S30>/Discrete-Time Integrator1' */
  if (localDW->DiscreteTimeIntegrator1_SYSTEM_ != 0) {
    /* DiscreteIntegrator: '<S30>/Discrete-Time Integrator1' */
    DiscreteTimeIntegrator1 = localDW->DiscreteTimeIntegrator1_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S30>/Discrete-Time Integrator1' */
    DiscreteTimeIntegrator1 = 0.0981747732F * (real32_T)NormalRunFunc_ELAPS_T
      * localDW->DiscreteTimeIntegrator1_PREV_U +
      localDW->DiscreteTimeIntegrator1_DSTATE;
  }

  if (DiscreteTimeIntegrator1 >= 1.2F) {
    /* DiscreteIntegrator: '<S30>/Discrete-Time Integrator1' */
    DiscreteTimeIntegrator1 = 1.2F;
  } else {
    if (DiscreteTimeIntegrator1 <= -1.2F) {
      /* DiscreteIntegrator: '<S30>/Discrete-Time Integrator1' */
      DiscreteTimeIntegrator1 = -1.2F;
    }
  }

  /* End of DiscreteIntegrator: '<S30>/Discrete-Time Integrator1' */

  /* Sum: '<S30>/Add' incorporates:
   *  Constant: '<S18>/Constant'
   *  DataStoreWrite: '<S12>/Data Store Write1'
   *  Gain: '<S30>/Gain'
   *  Sum: '<S30>/Subtract1'
   */
  rtb_Saturation1_h = (0.0F - rtd_varFOC->Signals.Current.RotaCurr.Real) *
    0.24734889F + DiscreteTimeIntegrator1;

  /* Saturate: '<S30>/Saturation1' incorporates:
   *  DataStoreWrite: '<S12>/Data Store Write1'
   */
  if (rtb_Saturation1_h > 1.2F) {
    rtd_varFOC->Signals.Voltage.RotaVolt.Real = 1.2F;
  } else if (rtb_Saturation1_h < -1.2F) {
    rtd_varFOC->Signals.Voltage.RotaVolt.Real = -1.2F;
  } else {
    rtd_varFOC->Signals.Voltage.RotaVolt.Real = rtb_Saturation1_h;
  }

  /* End of Saturate: '<S30>/Saturation1' */

  /* Sum: '<S26>/Subtract1' incorporates:
   *  DataStoreWrite: '<S12>/Data Store Write1'
   *  Product: '<S26>/Product2'
   *  Product: '<S26>/Product3'
   *  Trigonometry: '<S26>/Cos'
   *  Trigonometry: '<S26>/Sin'
   */
  rtd_varFOC->Signals.Current.RotaCurr.Imag =
    rtd_varFOC->Signals.Current.StatCurr.Imag * rtb_DataTypeConversion2_j -
    rtb_Gain3_l * rtb_Sum2_p;

  /* Sum: '<S22>/Sum2' incorporates:
   *  Constant: '<S22>/Constant1'
   *  Constant: '<S22>/Constant2'
   *  DataTypeConversion: '<S22>/Data Type Conversion'
   *  Product: '<S22>/Product'
   */
  rtb_Sum2_a = (real32_T)rtu_dataRaw[4] * 0.015F + 280.0F;

  /* Sum: '<S30>/Subtract' incorporates:
   *  DataStoreWrite: '<S12>/Data Store Write1'
   */
  rtb_Subtract_j = rtb_Sum2_a - rtd_varFOC->Signals.Current.RotaCurr.Imag;

  /* DiscreteIntegrator: '<S30>/Discrete-Time Integrator2' */
  if (localDW->DiscreteTimeIntegrator2_SYSTEM_ != 0) {
    /* DiscreteIntegrator: '<S30>/Discrete-Time Integrator2' */
    DiscreteTimeIntegrator2 = localDW->DiscreteTimeIntegrator2_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S30>/Discrete-Time Integrator2' */
    DiscreteTimeIntegrator2 = 0.0981747732F * (real32_T)NormalRunFunc_ELAPS_T
      * localDW->DiscreteTimeIntegrator2_PREV_U +
      localDW->DiscreteTimeIntegrator2_DSTATE;
  }

  if (DiscreteTimeIntegrator2 >= 1.2F) {
    /* DiscreteIntegrator: '<S30>/Discrete-Time Integrator2' */
    DiscreteTimeIntegrator2 = 1.2F;
  } else {
    if (DiscreteTimeIntegrator2 <= -1.2F) {
      /* DiscreteIntegrator: '<S30>/Discrete-Time Integrator2' */
      DiscreteTimeIntegrator2 = -1.2F;
    }
  }

  /* End of DiscreteIntegrator: '<S30>/Discrete-Time Integrator2' */

  /* Sum: '<S30>/Add1' incorporates:
   *  Gain: '<S30>/Gain1'
   */
  rtb_Saturation1_h = 0.24734889F * rtb_Subtract_j + DiscreteTimeIntegrator2;

  /* Saturate: '<S30>/Saturation2' incorporates:
   *  DataStoreWrite: '<S12>/Data Store Write1'
   */
  if (rtb_Saturation1_h > 1.2F) {
    rtd_varFOC->Signals.Voltage.RotaVolt.Imag = 1.2F;
  } else if (rtb_Saturation1_h < -1.2F) {
    rtd_varFOC->Signals.Voltage.RotaVolt.Imag = -1.2F;
  } else {
    rtd_varFOC->Signals.Voltage.RotaVolt.Imag = rtb_Saturation1_h;
  }

  /* End of Saturate: '<S30>/Saturation2' */

  /* Sum: '<S28>/Subtract' incorporates:
   *  DataStoreWrite: '<S12>/Data Store Write1'
   *  Product: '<S28>/Product'
   *  Product: '<S28>/Product1'
   */
  rtd_varFOC->Signals.Voltage.StatVolt.Real =
    rtd_varFOC->Signals.Voltage.RotaVolt.Real * rtb_DataTypeConversion2_j -
    rtd_varFOC->Signals.Voltage.RotaVolt.Imag * rtb_Sum2_p;

  /* Gain: '<S27>/one_by_sqrt3' incorporates:
   *  DataStoreWrite: '<S12>/Data Store Write1'
   */
  rtb_Saturation1_h = 0.577350259F * rtd_varFOC->Signals.Voltage.StatVolt.Real;

  /* Sum: '<S27>/a' */
  rtb_Fcn1_g2 = rtb_Saturation1_h + rtb_Saturation1_h;

  /* Sum: '<S28>/Add' incorporates:
   *  DataStoreWrite: '<S12>/Data Store Write1'
   *  Product: '<S28>/Product2'
   *  Product: '<S28>/Product3'
   */
  rtd_varFOC->Signals.Voltage.StatVolt.Imag =
    rtd_varFOC->Signals.Voltage.RotaVolt.Real * rtb_Sum2_p +
    rtd_varFOC->Signals.Voltage.RotaVolt.Imag * rtb_DataTypeConversion2_j;

  /* Sum: '<S27>/b' incorporates:
   *  DataStoreWrite: '<S12>/Data Store Write1'
   */
  rtb_Sum2_p = rtd_varFOC->Signals.Voltage.StatVolt.Imag - rtb_Saturation1_h;

  /* Sum: '<S27>/c' incorporates:
   *  DataStoreWrite: '<S12>/Data Store Write1'
   */
  rtb_Saturation1_h = (0.0F - rtb_Saturation1_h) -
    rtd_varFOC->Signals.Voltage.StatVolt.Imag;

  /* Gain: '<S27>/one_by_two' incorporates:
   *  MinMax: '<S27>/Max'
   *  MinMax: '<S27>/Min'
   *  Sum: '<S27>/Add'
   */
  rtb_DataTypeConversion2_j = (fmaxf(fmaxf(rtb_Fcn1_g2, rtb_Sum2_p),
    rtb_Saturation1_h) + fminf(fminf(rtb_Fcn1_g2, rtb_Sum2_p), rtb_Saturation1_h))
    * 0.5F;

  /* Sum: '<S18>/Sum1' incorporates:
   *  Constant: '<S18>/Constant4'
   *  Gain: '<S18>/Gain1'
   *  Gain: '<S18>/Gain5'
   *  Sum: '<S27>/Da'
   */
  rtb_Fcn1_g2 = (rtb_Fcn1_g2 - rtb_DataTypeConversion2_j) * 0.0833333358F * 0.5F
    + 0.5F;

  /* SignalConversion: '<S18>/Signal Conversion' incorporates:
   *  Constant: '<S18>/Constant4'
   *  Gain: '<S18>/Gain2'
   *  Gain: '<S18>/Gain3'
   *  Gain: '<S18>/Gain6'
   *  Gain: '<S18>/Gain7'
   *  Sum: '<S18>/Sum2'
   *  Sum: '<S18>/Sum3'
   *  Sum: '<S27>/Db'
   *  Sum: '<S27>/Dc'
   */
  rty_dutyOut[0] = rtb_Fcn1_g2;
  rty_dutyOut[1] = (rtb_Sum2_p - rtb_DataTypeConversion2_j) * 0.0833333358F *
    0.5F + 0.5F;
  rty_dutyOut[2] = (rtb_Saturation1_h - rtb_DataTypeConversion2_j) *
    0.0833333358F * 0.5F + 0.5F;

  /* DataStoreWrite: '<S12>/Data Store Write1' */
  rtd_varFOC->Signals.Current.StatCurr.Real = rtb_Gain3_l;

  /* Outputs for Atomic SubSystem: '<S18>/PLLObserver1' */
  FOC_Ctrl_CodeModel_PLLObserver1(rtd_varFOC->Signals.Voltage.RotaVolt.Real,
    rtd_varFOC->Signals.Current.RotaCurr.Real,
    rtd_varFOC->Signals.Current.RotaCurr.Imag, &rtb_Fcn1_g2, &rtb_Saturation1_h,
    &localDW->PLLObserver1, &NormalRunFunc_ELAPS_T);

  /* End of Outputs for SubSystem: '<S18>/PLLObserver1' */

  /* DataStoreWrite: '<S12>/Data Store Write2' */
  rtd_varFOC->Signals.Snls.AngleFlux = rtb_Fcn1_g2;
  rtd_varFOC->Signals.Snls.VelocityFlux = rtb_Saturation1_h;

  /* Gain: '<S20>/Gain1' incorporates:
   *  DataStoreRead: '<S20>/Data Store Read1'
   *  DataStoreWrite: '<S20>/Data Store Write3'
   *  DataTypeConversion: '<S20>/Data Type Conversion1'
   *  Sum: '<S20>/Sum3'
   */
  rtd_varFOC->Signals.DCbus.Current = ((real32_T)rtu_dataRaw[2] -
    rtd_varFOC->Signals.Current.Offset.iDC) * 0.0122100124F;

  /* Gain: '<S21>/Gain8' incorporates:
   *  DataStoreWrite: '<S21>/Data Store Write4'
   *  DataTypeConversion: '<S21>/Data Type Conversion2'
   */
  rtd_varFOC->Signals.DCbus.Voltage = 0.0109890113F * (real32_T)rtu_dataRaw[3];

  /* DataStoreWrite: '<S19>/Data Store Write1' */
  rtd_varFOC->Signals.Current.iABC.iA = rtb_Gain3_l;
  rtd_varFOC->Signals.Current.iABC.iB = rtb_Gain2_f;
  rtd_varFOC->Signals.Current.iABC.iC = rtb_Gain6_i;

  /* DataStoreWrite: '<S22>/Data Store Write5' */
  rtd_varFOC->MotorCtrl.CntrlReq.SpdReq = rtb_Sum2_a;

  /* DataStoreWrite: '<S18>/Data Store Write' */
  localDW->FocInternalPara.FocTheta.EstAngle = rtb_Fcn1_g2;
  localDW->FocInternalPara.FocSpd.EstOmega = rtb_Saturation1_h;

  /* Chart: '<S18>/Chart' */
  if (localDW->temporalCounter_i1 < 32767U) {
    localDW->temporalCounter_i1++;
  }

  if (localDW->is_active_c3_FOC_Ctrl_CodeModel == 0U) {
    localDW->is_active_c3_FOC_Ctrl_CodeModel = 1U;
    localDW->is_c3_FOC_Ctrl_CodeModel = FOC_Ctrl_CodeMode_IN_AlignStage;
    localDW->temporalCounter_i1 = 0U;
    rtb_Gain2_f = 1.0F;
    rtb_Gain3_l = 1.0F;
    rtb_Gain6_i = 1.0F;

    /* DataStoreWrite: '<S18>/Data Store Write2' */
    localDW->FocInternalPara.FocTheta.Angle = 0.0F;
    rtb_Sum2_a = 0.0F;
  } else {
    switch (localDW->is_c3_FOC_Ctrl_CodeModel) {
     case FOC_Ctrl_CodeMode_IN_AlignStage:
      if (localDW->temporalCounter_i1 >= 8000) {
        localDW->is_c3_FOC_Ctrl_CodeModel = FOC_Ctrl_CodeModel_IN_OpenStage;
        localDW->temporalCounter_i1 = 0U;
        rtb_Gain2_f = 1.0F;
        rtb_Gain3_l = 1.0F;
        rtb_Gain6_i = 0.0F;

        /* DataStoreWrite: '<S18>/Data Store Write2' incorporates:
         *  DataStoreRead: '<S18>/Data Store Read1'
         */
        localDW->FocInternalPara.FocTheta.Angle =
          localDW->FocInternalPara.FocTheta.OpenAngle;
        rtb_Sum2_a = 94.0F;
      } else {
        rtb_Gain2_f = 1.0F;
        rtb_Gain3_l = 1.0F;
        rtb_Gain6_i = 1.0F;

        /* DataStoreWrite: '<S18>/Data Store Write2' */
        localDW->FocInternalPara.FocTheta.Angle = 0.0F;
        rtb_Sum2_a = 0.0F;
      }
      break;

     case FOC_Ctrl_CodeModel_IN_OpenStage:
      if (localDW->temporalCounter_i1 >= 8000) {
        localDW->is_c3_FOC_Ctrl_CodeModel = FOC_Ctrl_CodeMode_IN_TrackStage;
        localDW->temporalCounter_i1 = 0U;
        rtb_Gain2_f = 1.0F;
        rtb_Gain3_l = 0.0F;
        rtb_Gain6_i = 0.0F;

        /* DataStoreWrite: '<S18>/Data Store Write2' incorporates:
         *  DataStoreRead: '<S18>/Data Store Read1'
         */
        localDW->FocInternalPara.FocTheta.Angle =
          localDW->FocInternalPara.FocTheta.OpenAngle;
        rtb_Sum2_a = 94.0F;
      } else {
        rtb_Gain2_f = 1.0F;
        rtb_Gain3_l = 1.0F;
        rtb_Gain6_i = 0.0F;

        /* DataStoreWrite: '<S18>/Data Store Write2' incorporates:
         *  DataStoreRead: '<S18>/Data Store Read1'
         */
        localDW->FocInternalPara.FocTheta.Angle =
          localDW->FocInternalPara.FocTheta.OpenAngle;
        rtb_Sum2_a = 94.0F;
      }
      break;

     case FOC_Ctrl_CodeModel_IN_RunStage:
      rtb_Gain2_f = 0.0F;
      rtb_Gain3_l = 0.0F;
      rtb_Gain6_i = 0.0F;

      /* DataStoreWrite: '<S18>/Data Store Write2' incorporates:
       *  DataStoreRead: '<S18>/Data Store Read1'
       */
      localDW->FocInternalPara.FocTheta.Angle =
        localDW->FocInternalPara.FocTheta.EstAngle;
      rtb_Sum2_a = 0.0F;
      break;

     default:
      /* case IN_TrackStage: */
      if (localDW->temporalCounter_i1 >= 20000) {
        localDW->is_c3_FOC_Ctrl_CodeModel = FOC_Ctrl_CodeModel_IN_RunStage;
        rtb_Gain2_f = 0.0F;
        rtb_Gain3_l = 0.0F;
        rtb_Gain6_i = 0.0F;

        /* DataStoreWrite: '<S18>/Data Store Write2' incorporates:
         *  DataStoreRead: '<S18>/Data Store Read1'
         */
        localDW->FocInternalPara.FocTheta.Angle =
          localDW->FocInternalPara.FocTheta.EstAngle;
        rtb_Sum2_a = 0.0F;
      } else {
        rtb_Gain2_f = 1.0F;
        rtb_Gain3_l = 0.0F;
        rtb_Gain6_i = 0.0F;

        /* DataStoreWrite: '<S18>/Data Store Write2' incorporates:
         *  DataStoreRead: '<S18>/Data Store Read1'
         */
        localDW->FocInternalPara.FocTheta.Angle =
          localDW->FocInternalPara.FocTheta.OpenAngle;
        rtb_Sum2_a = 94.0F;
      }
      break;
    }
  }

  /* End of Chart: '<S18>/Chart' */

  /* DataStoreWrite: '<S18>/Data Store Write2' */
  localDW->FocInternalPara.Rst.snlsRst = rtb_Gain3_l;
  localDW->FocInternalPara.Rst.innerCtrRst = rtb_Gain6_i;
  localDW->FocInternalPara.Rst.outerRst = rtb_Gain2_f;
  localDW->FocInternalPara.FocSpd.OpenOmega = rtb_Sum2_a;

  /* Sum: '<S31>/Add1' incorporates:
   *  Constant: '<S31>/Filter_Constant'
   *  Constant: '<S31>/One'
   *  DataStoreRead: '<S24>/Data Store Read2'
   *  Product: '<S31>/Product'
   *  Product: '<S31>/Product1'
   *  UnitDelay: '<S31>/Unit Delay'
   */
  rtb_Gain2_f = localDW->FocInternalPara.FocSpd.OpenOmega * 0.002F + 0.998F *
    localDW->UnitDelay_DSTATE;

  /* DataStoreWrite: '<S24>/Data Store Write1' incorporates:
   *  DataStoreRead: '<S24>/Data Store Read'
   *  Gain: '<S24>/Gain'
   *  Gain: '<S24>/Gain1'
   *  Sum: '<S24>/Sum4'
   */
  localDW->FocInternalPara.FocTheta.OpenAngle += 0.000636619749F * rtb_Gain2_f *
    16000.0F;

  /* If: '<S24>/If' incorporates:
   *  DataStoreRead: '<S24>/Data Store Read1'
   */
  if (localDW->FocInternalPara.FocTheta.OpenAngle > 6.28318501F) {
    /* Outputs for IfAction SubSystem: '<S24>/If Action Subsystem' incorporates:
     *  ActionPort: '<S32>/Action Port'
     */
    /* DataStoreWrite: '<S32>/Data Store Write1' incorporates:
     *  Constant: '<S32>/Constant'
     */
    localDW->FocInternalPara.FocTheta.OpenAngle = 0.0F;

    /* End of Outputs for SubSystem: '<S24>/If Action Subsystem' */
  }

  /* End of If: '<S24>/If' */

  /* Update for DiscreteIntegrator: '<S30>/Discrete-Time Integrator1' incorporates:
   *  Constant: '<S18>/Constant'
   *  DataStoreWrite: '<S12>/Data Store Write1'
   *  Gain: '<S30>/Gain2'
   *  Sum: '<S30>/Subtract1'
   */
  localDW->DiscreteTimeIntegrator1_SYSTEM_ = 0U;
  localDW->DiscreteTimeIntegrator1_DSTATE = DiscreteTimeIntegrator1;
  localDW->DiscreteTimeIntegrator1_PREV_U = (0.0F -
    rtd_varFOC->Signals.Current.RotaCurr.Real) * 0.0656113327F;

  /* Update for DiscreteIntegrator: '<S30>/Discrete-Time Integrator2' incorporates:
   *  Gain: '<S30>/Gain3'
   */
  localDW->DiscreteTimeIntegrator2_SYSTEM_ = 0U;
  localDW->DiscreteTimeIntegrator2_DSTATE = DiscreteTimeIntegrator2;
  localDW->DiscreteTimeIntegrator2_PREV_U = 0.0656113327F * rtb_Subtract_j;

  /* Update for UnitDelay: '<S31>/Unit Delay' */
  localDW->UnitDelay_DSTATE = rtb_Gain2_f;
}

/* Model step function */
void FOC_Ctrl_CodeModel_step(void)
{
  int32_T tmp;
  real32_T rtb_DiscreteTimeIntegrator2;
  real32_T rtb_Switch1;

  /* Chart: '<S3>/Chart' incorporates:
   *  Inport: '<Root>/FaultSwitch'
   *  Inport: '<Root>/MotorSwitch'
   */
  if (FOC_Ctrl_CodeModel_DW.is_active_c1_FOC_Ctrl_CodeModel == 0U) {
    FOC_Ctrl_CodeModel_DW.is_active_c1_FOC_Ctrl_CodeModel = 1U;
    FOC_Ctrl_CodeModel_DW.is_c1_FOC_Ctrl_CodeModel =
      FOC_Ctrl_CodeModel_IN_Initial;

    /* Outputs for Function Call SubSystem: '<S8>/InitFunc' */
    /* Outport: '<Root>/LED' incorporates:
     *  Outport: '<Root>/DUTY'
     */
    FOC_Ctrl_CodeModel_InitFunc(FOC_Ctrl_CodeModel_Y.DUTY,
      FOC_Ctrl_CodeModel_Y.LED, &FOC_Ctrl_CodeModel_DW.varFOC);

    /* End of Outputs for SubSystem: '<S8>/InitFunc' */
    FOC_Ctrl_CodeModel_DW.InitDone = true;
  } else {
    switch (FOC_Ctrl_CodeModel_DW.is_c1_FOC_Ctrl_CodeModel) {
     case FOC_Ctrl_CodeModel_IN_Faults:
      if ((boolean_T)(FOC_Ctrl_CodeModel_U.FaultSwitch ^ 1)) {
        FOC_Ctrl_CodeModel_DW.is_c1_FOC_Ctrl_CodeModel =
          FOC_Ctrl_CodeModel_IN_Initial;

        /* Outputs for Function Call SubSystem: '<S8>/InitFunc' */
        /* Outport: '<Root>/LED' incorporates:
         *  Outport: '<Root>/DUTY'
         */
        FOC_Ctrl_CodeModel_InitFunc(FOC_Ctrl_CodeModel_Y.DUTY,
          FOC_Ctrl_CodeModel_Y.LED, &FOC_Ctrl_CodeModel_DW.varFOC);

        /* End of Outputs for SubSystem: '<S8>/InitFunc' */
        FOC_Ctrl_CodeModel_DW.InitDone = true;
      } else {
        /* Outputs for Function Call SubSystem: '<S8>/FaultFunc' */
        /* Outport: '<Root>/LED' incorporates:
         *  Outport: '<Root>/DUTY'
         */
        FOC_Ctrl_CodeModel_FaultFunc(FOC_Ctrl_CodeModel_Y.DUTY,
          FOC_Ctrl_CodeModel_Y.LED);

        /* End of Outputs for SubSystem: '<S8>/FaultFunc' */
      }
      break;

     case FOC_Ctrl_CodeModel_IN_Initial:
      if (FOC_Ctrl_CodeModel_DW.InitDone) {
        FOC_Ctrl_CodeModel_DW.is_c1_FOC_Ctrl_CodeModel =
          FOC_Ctrl_CodeModel_IN_Ready;

        /* Outputs for Function Call SubSystem: '<S8>/ReadyFunc' */
        /* Outport: '<Root>/LED' incorporates:
         *  Outport: '<Root>/DUTY'
         */
        FOC_Ctrl_CodeModel_ReadyFunc(FOC_Ctrl_CodeModel_Y.DUTY,
          FOC_Ctrl_CodeModel_Y.LED);

        /* End of Outputs for SubSystem: '<S8>/ReadyFunc' */
      } else if (FOC_Ctrl_CodeModel_U.FaultSwitch) {
        FOC_Ctrl_CodeModel_DW.is_c1_FOC_Ctrl_CodeModel =
          FOC_Ctrl_CodeModel_IN_Faults;

        /* Outputs for Function Call SubSystem: '<S8>/FaultFunc' */
        /* Outport: '<Root>/LED' incorporates:
         *  Outport: '<Root>/DUTY'
         */
        FOC_Ctrl_CodeModel_FaultFunc(FOC_Ctrl_CodeModel_Y.DUTY,
          FOC_Ctrl_CodeModel_Y.LED);

        /* End of Outputs for SubSystem: '<S8>/FaultFunc' */
      } else {
        /* Outputs for Function Call SubSystem: '<S8>/InitFunc' */
        /* Outport: '<Root>/LED' incorporates:
         *  Outport: '<Root>/DUTY'
         */
        FOC_Ctrl_CodeModel_InitFunc(FOC_Ctrl_CodeModel_Y.DUTY,
          FOC_Ctrl_CodeModel_Y.LED, &FOC_Ctrl_CodeModel_DW.varFOC);

        /* End of Outputs for SubSystem: '<S8>/InitFunc' */
        FOC_Ctrl_CodeModel_DW.InitDone = true;
      }
      break;

     case FOC_Ctrl_CodeModel_IN_Ready:
      if (FOC_Ctrl_CodeModel_U.MotorSwitch) {
        FOC_Ctrl_CodeModel_DW.is_c1_FOC_Ctrl_CodeModel =
          FOC_Ctrl_CodeModel_IN_Run;
        FOC_Ctrl_CodeModel_DW.is_Run = FOC_Ctrl_CodeMod_IN_Calibration;
        FOC_Ctrl_CodeModel_DW.CalCnt = 0U;
      } else if (FOC_Ctrl_CodeModel_U.FaultSwitch) {
        FOC_Ctrl_CodeModel_DW.is_c1_FOC_Ctrl_CodeModel =
          FOC_Ctrl_CodeModel_IN_Faults;

        /* Outputs for Function Call SubSystem: '<S8>/FaultFunc' */
        /* Outport: '<Root>/LED' incorporates:
         *  Outport: '<Root>/DUTY'
         */
        FOC_Ctrl_CodeModel_FaultFunc(FOC_Ctrl_CodeModel_Y.DUTY,
          FOC_Ctrl_CodeModel_Y.LED);

        /* End of Outputs for SubSystem: '<S8>/FaultFunc' */
      } else {
        /* Outputs for Function Call SubSystem: '<S8>/ReadyFunc' */
        /* Outport: '<Root>/LED' incorporates:
         *  Outport: '<Root>/DUTY'
         */
        FOC_Ctrl_CodeModel_ReadyFunc(FOC_Ctrl_CodeModel_Y.DUTY,
          FOC_Ctrl_CodeModel_Y.LED);

        /* End of Outputs for SubSystem: '<S8>/ReadyFunc' */
      }
      break;

     default:
      /* case IN_Run: */
      if ((boolean_T)(FOC_Ctrl_CodeModel_U.MotorSwitch ^ 1)) {
        FOC_Ctrl_CodeModel_DW.is_Run = FOC_Ctrl_Cod_IN_NO_ACTIVE_CHILD;
        FOC_Ctrl_CodeModel_DW.is_c1_FOC_Ctrl_CodeModel =
          FOC_Ctrl_CodeModel_IN_Initial;

        /* Outputs for Function Call SubSystem: '<S8>/InitFunc' */
        /* Outport: '<Root>/LED' incorporates:
         *  Outport: '<Root>/DUTY'
         */
        FOC_Ctrl_CodeModel_InitFunc(FOC_Ctrl_CodeModel_Y.DUTY,
          FOC_Ctrl_CodeModel_Y.LED, &FOC_Ctrl_CodeModel_DW.varFOC);

        /* End of Outputs for SubSystem: '<S8>/InitFunc' */
        FOC_Ctrl_CodeModel_DW.InitDone = true;
      } else if (FOC_Ctrl_CodeModel_U.FaultSwitch) {
        FOC_Ctrl_CodeModel_DW.is_Run = FOC_Ctrl_Cod_IN_NO_ACTIVE_CHILD;
        FOC_Ctrl_CodeModel_DW.is_c1_FOC_Ctrl_CodeModel =
          FOC_Ctrl_CodeModel_IN_Faults;

        /* Outputs for Function Call SubSystem: '<S8>/FaultFunc' */
        /* Outport: '<Root>/LED' incorporates:
         *  Outport: '<Root>/DUTY'
         */
        FOC_Ctrl_CodeModel_FaultFunc(FOC_Ctrl_CodeModel_Y.DUTY,
          FOC_Ctrl_CodeModel_Y.LED);

        /* End of Outputs for SubSystem: '<S8>/FaultFunc' */
      } else if (FOC_Ctrl_CodeModel_DW.is_Run == FOC_Ctrl_CodeMod_IN_Calibration)
      {
        if (FOC_Ctrl_CodeModel_DW.CalCnt > 10000) {
          FOC_Ctrl_CodeModel_DW.CalCnt = 0U;
          FOC_Ctrl_CodeModel_DW.is_Run = FOC_Ctrl_CodeModel_IN_NormalRun;

          /* Outputs for Function Call SubSystem: '<S8>/NormalRunFunc' */
          /* Outport: '<Root>/LED' incorporates:
           *  Inport: '<Root>/ADCinput'
           *  Outport: '<Root>/DUTY'
           */
          FOC_Ctrl_CodeMode_NormalRunFunc(FOC_Ctrl_CodeModel_M,
            FOC_Ctrl_CodeModel_U.ADCinput, FOC_Ctrl_CodeModel_Y.DUTY,
            FOC_Ctrl_CodeModel_Y.LED, &FOC_Ctrl_CodeModel_DW.NormalRunFunc,
            &FOC_Ctrl_CodeModel_DW.varFOC);

          /* End of Outputs for SubSystem: '<S8>/NormalRunFunc' */
        } else {
          tmp = FOC_Ctrl_CodeModel_DW.CalCnt + 1;
          if (FOC_Ctrl_CodeModel_DW.CalCnt + 1 > 65535) {
            tmp = 65535;
          }

          FOC_Ctrl_CodeModel_DW.CalCnt = (uint16_T)tmp;

          /* Outputs for Function Call SubSystem: '<S8>/CalFunc' */
          /* Sum: '<S14>/Add1' incorporates:
           *  Constant: '<S14>/Filter_Constant'
           *  Constant: '<S14>/One'
           *  DataStoreWrite: '<S9>/Data Store Write15'
           *  DataTypeConversion: '<S9>/Data Type Conversion'
           *  Inport: '<Root>/ADCinput'
           *  Product: '<S14>/Product'
           *  Product: '<S14>/Product1'
           *  UnitDelay: '<S14>/Unit Delay'
           */
          FOC_Ctrl_CodeModel_DW.varFOC.Signals.Current.Offset.iA = (real32_T)
            FOC_Ctrl_CodeModel_U.ADCinput[0] * 0.001F + 0.999F *
            FOC_Ctrl_CodeModel_DW.UnitDelay_DSTATE;

          /* Sum: '<S15>/Add1' incorporates:
           *  Constant: '<S15>/Filter_Constant'
           *  Constant: '<S15>/One'
           *  DataStoreWrite: '<S9>/Data Store Write15'
           *  DataTypeConversion: '<S9>/Data Type Conversion1'
           *  Inport: '<Root>/ADCinput'
           *  Product: '<S15>/Product'
           *  Product: '<S15>/Product1'
           *  UnitDelay: '<S15>/Unit Delay'
           */
          FOC_Ctrl_CodeModel_DW.varFOC.Signals.Current.Offset.iB = (real32_T)
            FOC_Ctrl_CodeModel_U.ADCinput[1] * 0.001F + 0.999F *
            FOC_Ctrl_CodeModel_DW.UnitDelay_DSTATE_b;

          /* Sum: '<S16>/Add1' incorporates:
           *  Constant: '<S16>/Filter_Constant'
           *  Constant: '<S16>/One'
           *  DataStoreWrite: '<S9>/Data Store Write15'
           *  DataTypeConversion: '<S9>/Data Type Conversion2'
           *  Inport: '<Root>/ADCinput'
           *  Product: '<S16>/Product'
           *  Product: '<S16>/Product1'
           *  UnitDelay: '<S16>/Unit Delay'
           */
          FOC_Ctrl_CodeModel_DW.varFOC.Signals.Current.Offset.iDC = (real32_T)
            FOC_Ctrl_CodeModel_U.ADCinput[2] * 0.001F + 0.999F *
            FOC_Ctrl_CodeModel_DW.UnitDelay_DSTATE_f;

          /* Update for UnitDelay: '<S14>/Unit Delay' incorporates:
           *  DataStoreWrite: '<S9>/Data Store Write15'
           */
          FOC_Ctrl_CodeModel_DW.UnitDelay_DSTATE =
            FOC_Ctrl_CodeModel_DW.varFOC.Signals.Current.Offset.iA;

          /* Update for UnitDelay: '<S15>/Unit Delay' incorporates:
           *  DataStoreWrite: '<S9>/Data Store Write15'
           */
          FOC_Ctrl_CodeModel_DW.UnitDelay_DSTATE_b =
            FOC_Ctrl_CodeModel_DW.varFOC.Signals.Current.Offset.iB;

          /* Update for UnitDelay: '<S16>/Unit Delay' incorporates:
           *  DataStoreWrite: '<S9>/Data Store Write15'
           */
          FOC_Ctrl_CodeModel_DW.UnitDelay_DSTATE_f =
            FOC_Ctrl_CodeModel_DW.varFOC.Signals.Current.Offset.iDC;

          /* End of Outputs for SubSystem: '<S8>/CalFunc' */

          /* Outport: '<Root>/DUTY' */
          FOC_Ctrl_CodeModel_Y.DUTY[0] = 0.0F;

          /* Outport: '<Root>/LED' */
          FOC_Ctrl_CodeModel_Y.LED[0] = false;

          /* Outport: '<Root>/DUTY' */
          FOC_Ctrl_CodeModel_Y.DUTY[1] = 0.0F;

          /* Outport: '<Root>/LED' */
          FOC_Ctrl_CodeModel_Y.LED[1] = false;

          /* Outport: '<Root>/DUTY' */
          FOC_Ctrl_CodeModel_Y.DUTY[2] = 0.0F;

          /* Outport: '<Root>/LED' */
          FOC_Ctrl_CodeModel_Y.LED[2] = true;
        }
      } else {
        /* Outputs for Function Call SubSystem: '<S8>/NormalRunFunc' */
        /* Outport: '<Root>/LED' incorporates:
         *  Inport: '<Root>/ADCinput'
         *  Outport: '<Root>/DUTY'
         */
        /* case IN_NormalRun: */
        FOC_Ctrl_CodeMode_NormalRunFunc(FOC_Ctrl_CodeModel_M,
          FOC_Ctrl_CodeModel_U.ADCinput, FOC_Ctrl_CodeModel_Y.DUTY,
          FOC_Ctrl_CodeModel_Y.LED, &FOC_Ctrl_CodeModel_DW.NormalRunFunc,
          &FOC_Ctrl_CodeModel_DW.varFOC);

        /* End of Outputs for SubSystem: '<S8>/NormalRunFunc' */
      }
      break;
    }
  }

  /* End of Chart: '<S3>/Chart' */

  /* Outputs for Atomic SubSystem: '<Root>/PLLObserver' */
  /* Inport: '<Root>/Input' incorporates:
   *  Inport: '<Root>/Input1'
   *  Inport: '<Root>/Input2'
   *  Outport: '<Root>/Output'
   *  Outport: '<Root>/Output1'
   */
  FOC_Ctrl_CodeModel_PLLObserver(FOC_Ctrl_CodeModel_U.Input,
    FOC_Ctrl_CodeModel_U.Input1, FOC_Ctrl_CodeModel_U.Input2,
    &FOC_Ctrl_CodeModel_Y.Output, &FOC_Ctrl_CodeModel_Y.Output1,
    &FOC_Ctrl_CodeModel_DW.PLLObserver);

  /* End of Outputs for SubSystem: '<Root>/PLLObserver' */

  /* Outputs for Atomic SubSystem: '<Root>/SVCM' */
  /* Inport: '<Root>/Input3' incorporates:
   *  Inport: '<Root>/Input'
   *  Inport: '<Root>/Input1'
   *  Inport: '<Root>/Input2'
   *  Inport: '<Root>/Input4'
   */
  FOC_Ctrl_CodeModel_SVCM(FOC_Ctrl_CodeModel_U.Input3,
    FOC_Ctrl_CodeModel_U.Input2, FOC_Ctrl_CodeModel_U.Input1,
    FOC_Ctrl_CodeModel_U.Input, FOC_Ctrl_CodeModel_U.Input4,
    &rtb_DiscreteTimeIntegrator2, &rtb_Switch1, &FOC_Ctrl_CodeModel_DW.SVCM);

  /* End of Outputs for SubSystem: '<Root>/SVCM' */

  /* Outport: '<Root>/Output2' incorporates:
   *  ArithShift: '<Root>/Shift Arithmetic'
   *  Inport: '<Root>/Input5'
   */
  FOC_Ctrl_CodeModel_Y.Output2 = (int16_T)(FOC_Ctrl_CodeModel_U.Input5 << 2);

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 6.25E-5, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   */
  FOC_Ctrl_CodeModel_M->Timing.clockTick0++;
}

/* Model initialize function */
void FOC_Ctrl_CodeModel_initialize(void)
{
  {
    real32_T OutportBufferFordutyOut_il[3];
    boolean_T OutportBufferForledOut_glv[3];

    /* SystemInitialize for Chart: '<S3>/Chart' incorporates:
     *  SubSystem: '<S8>/InitFunc'
     */
    FOC_Ctrl_CodeMode_InitFunc_Init(OutportBufferFordutyOut_il,
      OutportBufferForledOut_glv);

    /* SystemInitialize for Chart: '<S3>/Chart' incorporates:
     *  SubSystem: '<S8>/FaultFunc'
     */
    FOC_Ctrl_CodeMod_FaultFunc_Init(OutportBufferFordutyOut_il,
      OutportBufferForledOut_glv);

    /* SystemInitialize for Chart: '<S3>/Chart' incorporates:
     *  SubSystem: '<S8>/ReadyFunc'
     */
    FOC_Ctrl_CodeMod_ReadyFunc_Init(OutportBufferFordutyOut_il,
      OutportBufferForledOut_glv);

    /* SystemInitialize for Chart: '<S3>/Chart' incorporates:
     *  SubSystem: '<S8>/NormalRunFunc'
     */
    FOC_Ctrl_Cod_NormalRunFunc_Init(OutportBufferForledOut_glv);

    /* Enable for Chart: '<S3>/Chart' incorporates:
     *  SubSystem: '<S8>/NormalRunFunc'
     */
    FOC_Ctrl_C_NormalRunFunc_Enable(&FOC_Ctrl_CodeModel_DW.NormalRunFunc);
  }
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
