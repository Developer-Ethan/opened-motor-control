/*
 * File: SVCM.c
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

#include "SVCM.h"

/* Include model header file for global data */
#include "FOC_Ctrl_CodeModel.h"
#include "FOC_Ctrl_CodeModel_private.h"
#include "rt_remf.h"

/* Output and update for atomic system: '<Root>/SVCM' */
void FOC_Ctrl_CodeModel_SVCM(real32_T rtu_Ualpha, real32_T rtu_Ubeta, real32_T
  rtu_Ia, real32_T rtu_Ib, real32_T rtu_Ic, real32_T *rty_est_Speed, real32_T
  *rty_est_Theta, DW_SVCM_FOC_Ctrl_CodeModel_T *localDW)
{
  /* local block i/o variables */
  real32_T Costheta;
  real32_T Sintheta;
  real32_T rtb_DiscreteTimeIntegrator3;
  real32_T rtb_Sin_0;

  /* Trigonometry: '<S6>/Sin1' incorporates:
   *  Delay: '<S2>/Delay7'
   */
  Costheta = cosf(localDW->Delay7_DSTATE);

  /* Trigonometry: '<S6>/Sin' incorporates:
   *  Delay: '<S2>/Delay7'
   */
  Sintheta = sinf(localDW->Delay7_DSTATE);

  /* Gain: '<S5>/Gain1' incorporates:
   *  Sum: '<S5>/Add'
   */
  *rty_est_Speed = (rtu_Ib - rtu_Ic) * 0.577350259F;

  /* Trigonometry: '<S7>/Sin1' incorporates:
   *  Delay: '<S2>/Delay7'
   */
  *rty_est_Theta = cosf(localDW->Delay7_DSTATE);

  /* Trigonometry: '<S7>/Sin' incorporates:
   *  Delay: '<S2>/Delay7'
   */
  rtb_Sin_0 = sinf(localDW->Delay7_DSTATE);

  /* Sum: '<S7>/Add1' incorporates:
   *  Product: '<S7>/Product2'
   *  Product: '<S7>/Product3'
   *  Trigonometry: '<S7>/Sin'
   */
  rtb_DiscreteTimeIntegrator3 = *rty_est_Speed * *rty_est_Theta - rtu_Ia *
    rtb_Sin_0;

  /* Sum: '<S7>/Add' incorporates:
   *  Product: '<S7>/Product'
   *  Product: '<S7>/Product1'
   *  Trigonometry: '<S7>/Sin'
   */
  *rty_est_Theta = rtu_Ia * *rty_est_Theta + *rty_est_Speed * rtb_Sin_0;

  /* Delay: '<S2>/Delay6' */
  *rty_est_Speed = localDW->Delay6_DSTATE;

  /* Signum: '<S2>/Sign1' */
  if (*rty_est_Speed < 0.0F) {
    rtb_Sin_0 = -1.0F;
  } else if (*rty_est_Speed > 0.0F) {
    rtb_Sin_0 = 1.0F;
  } else {
    rtb_Sin_0 = *rty_est_Speed;
  }

  /* End of Signum: '<S2>/Sign1' */

  /* Sum: '<S2>/Add12' incorporates:
   *  Gain: '<S2>/Gain15'
   *  Gain: '<S2>/Gain16'
   *  Gain: '<S2>/Gain22'
   *  Gain: '<S2>/Gain23'
   *  Gain: '<S2>/Gain24'
   *  Product: '<S2>/Product3'
   *  Product: '<S2>/Product4'
   *  Product: '<S2>/Product5'
   *  Product: '<S6>/Product'
   *  Product: '<S6>/Product1'
   *  Product: '<S6>/Product2'
   *  Product: '<S6>/Product3'
   *  Sum: '<S2>/Add10'
   *  Sum: '<S2>/Add11'
   *  Sum: '<S2>/Add7'
   *  Sum: '<S2>/Add8'
   *  Sum: '<S2>/Add9'
   *  Sum: '<S6>/Add'
   *  Sum: '<S6>/Add1'
   */
  rtb_Sin_0 = ((((rtu_Ubeta * Costheta - rtu_Ualpha * Sintheta) - 0.0656113327F *
                 rtb_DiscreteTimeIntegrator3) - 0.24734889F * *rty_est_Theta *
                *rty_est_Speed) - (((rtu_Ualpha * Costheta + rtu_Ubeta *
    Sintheta) - 0.0656113327F * *rty_est_Theta) + 0.24734889F *
    rtb_DiscreteTimeIntegrator3 * *rty_est_Speed) * rtb_Sin_0) * 0.397618473F - *
    rty_est_Speed;

  /* Fcn: '<S2>/Fcn1' incorporates:
   *  DiscreteIntegrator: '<S2>/Discrete-Time Integrator3'
   */
  rtb_DiscreteTimeIntegrator3 = rt_remf(localDW->DiscreteTimeIntegrator3_DSTATE,
    6.28318548F);

  /* Switch: '<S2>/Switch1' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Fcn: '<S2>/Fcn1'
   *  Sum: '<S2>/Add13'
   */
  if (rtb_DiscreteTimeIntegrator3 > 0.0F) {
    *rty_est_Theta = rtb_DiscreteTimeIntegrator3;
  } else {
    *rty_est_Theta = (real32_T)(rtb_DiscreteTimeIntegrator3 + 6.2831853071795862);
  }

  /* End of Switch: '<S2>/Switch1' */

  /* DiscreteIntegrator: '<S2>/Discrete-Time Integrator2' */
  *rty_est_Speed = localDW->DiscreteTimeIntegrator2_DSTATE;

  /* Update for Delay: '<S2>/Delay7' */
  localDW->Delay7_DSTATE = *rty_est_Theta;

  /* Update for Delay: '<S2>/Delay6' */
  localDW->Delay6_DSTATE = *rty_est_Speed;

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator3' */
  localDW->DiscreteTimeIntegrator3_DSTATE += 0.0981747732F * *rty_est_Speed;

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator2' incorporates:
   *  Gain: '<S2>/Gain25'
   */
  localDW->DiscreteTimeIntegrator2_DSTATE += 0.8F * rtb_Sin_0 * 0.0981747732F;
  if (localDW->DiscreteTimeIntegrator2_DSTATE >= 2.0F) {
    localDW->DiscreteTimeIntegrator2_DSTATE = 2.0F;
  } else {
    if (localDW->DiscreteTimeIntegrator2_DSTATE <= -2.0F) {
      localDW->DiscreteTimeIntegrator2_DSTATE = -2.0F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator2' */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
