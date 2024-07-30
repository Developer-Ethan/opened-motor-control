/*
 * File: PLLObserver1.c
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

#include "PLLObserver1.h"

/* Include model header file for global data */
#include "FOC_Ctrl_CodeModel.h"
#include "FOC_Ctrl_CodeModel_private.h"
#include "rt_remf.h"

/* Enable for atomic system: '<S18>/PLLObserver1' */
void FOC_Ctrl_Co_PLLObserver1_Enable(DW_PLLObserver1_FOC_Ctrl_Code_T *localDW)
{
  /* Enable for Atomic SubSystem: '<S25>/PLL' */
  /* Enable for DiscreteIntegrator: '<S33>/Discrete-Time Integrator2' */
  localDW->DiscreteTimeIntegrator2_SYSTEM_ = 1U;

  /* Enable for DiscreteIntegrator: '<S33>/Discrete-Time Integrator4' */
  localDW->DiscreteTimeIntegrator4_SYSTEM_ = 1U;

  /* End of Enable for SubSystem: '<S25>/PLL' */
}

/* Output and update for atomic system: '<S18>/PLLObserver1' */
void FOC_Ctrl_CodeModel_PLLObserver1(real32_T rtu_Ud, real32_T rtu_Id, real32_T
  rtu_Iq, real32_T *rty_est_theta, real32_T *rty_est_omega,
  DW_PLLObserver1_FOC_Ctrl_Code_T *localDW, uint32_T *rtd_NormalRunFunc_ELAPS_T)
{
  real32_T DiscreteTimeIntegrator2;
  real32_T DiscreteTimeIntegrator4;
  real32_T rtb_Gain8_d;

  /* Switch: '<S25>/Switch' incorporates:
   *  Constant: '<S25>/Constant'
   *  Delay: '<S25>/Delay8'
   */
  if (localDW->Delay8_DSTATE > ((int16_T)Omega0)) {
    rtb_Gain8_d = localDW->Delay8_DSTATE;
  } else {
    rtb_Gain8_d = ((int16_T)Omega0);
  }

  /* End of Switch: '<S25>/Switch' */

  /* Gain: '<S25>/Gain8' incorporates:
   *  Constant: '<S25>/Constant1'
   *  Constant: '<S25>/Constant2'
   *  Constant: '<S25>/Constant5'
   *  Delay: '<S25>/Delay2'
   *  Delay: '<S25>/Delay3'
   *  Delay: '<S25>/Delay4'
   *  Gain: '<S25>/Gain'
   *  Gain: '<S25>/Gain2'
   *  Product: '<S25>/Divide'
   *  Product: '<S25>/Product'
   *  Product: '<S25>/Product1'
   *  Product: '<S25>/Product2'
   *  Product: '<S25>/Product3'
   *  Sum: '<S25>/Add'
   */
  rtb_Gain8_d = -(((rtu_Ud - localDW->Delay2_DSTATE * 0.0656113327F) +
                   0.24734889F * localDW->Delay3_DSTATE * localDW->Delay4_DSTATE)
                  * (1.0F / (rtb_Gain8_d * 2.51497388F))) * 4.0F;

  /* Switch: '<S25>/Switch4' incorporates:
   *  Constant: '<S25>/Constant7'
   *  Sum: '<S25>/Add2'
   */
  if (rtb_Gain8_d >= 3.14159274F) {
    rtb_Gain8_d -= 6.28318548F;
  }

  /* End of Switch: '<S25>/Switch4' */

  /* Switch: '<S25>/Switch5' incorporates:
   *  Constant: '<S25>/Constant8'
   *  Sum: '<S25>/Add3'
   */
  if (rtb_Gain8_d < -3.14159274F) {
    rtb_Gain8_d += 6.28318548F;
  }

  /* End of Switch: '<S25>/Switch5' */

  /* Outputs for Atomic SubSystem: '<S25>/PLL' */
  /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator2' */
  if (localDW->DiscreteTimeIntegrator2_SYSTEM_ != 0) {
    /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator2' */
    DiscreteTimeIntegrator2 = localDW->DiscreteTimeIntegrator2_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator2' */
    DiscreteTimeIntegrator2 = 6.25E-5F * (real32_T)*rtd_NormalRunFunc_ELAPS_T
      * localDW->DiscreteTimeIntegrator2_PREV_U +
      localDW->DiscreteTimeIntegrator2_DSTATE;
  }

  if (DiscreteTimeIntegrator2 >= 1.2F) {
    /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator2' */
    DiscreteTimeIntegrator2 = 1.2F;
  } else {
    if (DiscreteTimeIntegrator2 <= -1.2F) {
      /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator2' */
      DiscreteTimeIntegrator2 = -1.2F;
    }
  }

  /* End of DiscreteIntegrator: '<S33>/Discrete-Time Integrator2' */

  /* Sum: '<S33>/Add14' incorporates:
   *  Gain: '<S33>/Gain'
   */
  DiscreteTimeIntegrator4 = 0.8F * rtb_Gain8_d + DiscreteTimeIntegrator2;

  /* Saturate: '<S33>/Saturation1' */
  if (DiscreteTimeIntegrator4 > 1.2F) {
    *rty_est_omega = 1.2F;
  } else if (DiscreteTimeIntegrator4 < -1.2F) {
    *rty_est_omega = -1.2F;
  } else {
    *rty_est_omega = DiscreteTimeIntegrator4;
  }

  /* End of Saturate: '<S33>/Saturation1' */

  /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator4' */
  if (localDW->DiscreteTimeIntegrator4_SYSTEM_ != 0) {
    /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator4' */
    DiscreteTimeIntegrator4 = localDW->DiscreteTimeIntegrator4_DSTATE;
  } else {
    /* DiscreteIntegrator: '<S33>/Discrete-Time Integrator4' */
    DiscreteTimeIntegrator4 = 0.0981747732F * (real32_T)
      *rtd_NormalRunFunc_ELAPS_T * localDW->DiscreteTimeIntegrator4_PREV_U +
      localDW->DiscreteTimeIntegrator4_DSTATE;
  }

  /* End of DiscreteIntegrator: '<S33>/Discrete-Time Integrator4' */

  /* Update for DiscreteIntegrator: '<S33>/Discrete-Time Integrator2' incorporates:
   *  Gain: '<S33>/Gain7'
   */
  localDW->DiscreteTimeIntegrator2_SYSTEM_ = 0U;
  localDW->DiscreteTimeIntegrator2_DSTATE = DiscreteTimeIntegrator2;
  localDW->DiscreteTimeIntegrator2_PREV_U = 0.16F * rtb_Gain8_d;

  /* Update for DiscreteIntegrator: '<S33>/Discrete-Time Integrator4' */
  localDW->DiscreteTimeIntegrator4_SYSTEM_ = 0U;
  localDW->DiscreteTimeIntegrator4_DSTATE = DiscreteTimeIntegrator4;
  localDW->DiscreteTimeIntegrator4_PREV_U = *rty_est_omega;

  /* End of Outputs for SubSystem: '<S25>/PLL' */

  /* Fcn: '<S25>/Fcn1' */
  *rty_est_theta = rt_remf(DiscreteTimeIntegrator4, 6.28318548F);

  /* Update for Delay: '<S25>/Delay2' */
  localDW->Delay2_DSTATE = rtu_Id;

  /* Update for Delay: '<S25>/Delay3' */
  localDW->Delay3_DSTATE = rtu_Iq;

  /* Update for Delay: '<S25>/Delay4' */
  localDW->Delay4_DSTATE = *rty_est_omega;

  /* Update for Delay: '<S25>/Delay8' */
  localDW->Delay8_DSTATE = *rty_est_omega;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
