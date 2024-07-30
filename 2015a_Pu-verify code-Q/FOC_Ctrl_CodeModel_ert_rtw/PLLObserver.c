/*
 * File: PLLObserver.c
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

#include "PLLObserver.h"

/* Include model header file for global data */
#include "FOC_Ctrl_CodeModel.h"
#include "FOC_Ctrl_CodeModel_private.h"
#include "rt_remf.h"

/* Output and update for atomic system: '<Root>/PLLObserver' */
void FOC_Ctrl_CodeModel_PLLObserver(real32_T rtu_Ud, real32_T rtu_Id, real32_T
  rtu_Iq, real32_T *rty_est_theta, real32_T *rty_est_omega,
  DW_PLLObserver_FOC_Ctrl_CodeM_T *localDW)
{
  real32_T rtb_DiscreteTimeIntegrator2_g;
  real32_T rtb_DiscreteTimeIntegrator2_i;

  /* Delay: '<S1>/Delay8' */
  rtb_DiscreteTimeIntegrator2_g = localDW->Delay8_DSTATE;

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S1>/Constant'
   */
  if (rtb_DiscreteTimeIntegrator2_g > ((int16_T)Omega0)) {
    rtb_DiscreteTimeIntegrator2_i = rtb_DiscreteTimeIntegrator2_g;
  } else {
    rtb_DiscreteTimeIntegrator2_i = ((int16_T)Omega0);
  }

  /* End of Switch: '<S1>/Switch' */

  /* Gain: '<S1>/Gain8' incorporates:
   *  Constant: '<S1>/Constant1'
   *  Constant: '<S1>/Constant2'
   *  Constant: '<S1>/Constant5'
   *  Delay: '<S1>/Delay2'
   *  Delay: '<S1>/Delay3'
   *  Gain: '<S1>/Gain'
   *  Gain: '<S1>/Gain2'
   *  Product: '<S1>/Divide'
   *  Product: '<S1>/Product'
   *  Product: '<S1>/Product1'
   *  Product: '<S1>/Product2'
   *  Product: '<S1>/Product3'
   *  Sum: '<S1>/Add'
   */
  rtb_DiscreteTimeIntegrator2_g = -(((rtu_Ud - localDW->Delay2_DSTATE *
    0.0656113327F) + 0.24734889F * localDW->Delay3_DSTATE *
    rtb_DiscreteTimeIntegrator2_g) * (1.0F / (rtb_DiscreteTimeIntegrator2_i *
    2.51497388F))) * 4.0F;

  /* Switch: '<S1>/Switch4' incorporates:
   *  Constant: '<S1>/Constant7'
   *  Sum: '<S1>/Add2'
   */
  if (rtb_DiscreteTimeIntegrator2_g >= 3.14159274F) {
    rtb_DiscreteTimeIntegrator2_g -= 6.28318548F;
  }

  /* End of Switch: '<S1>/Switch4' */

  /* Switch: '<S1>/Switch5' incorporates:
   *  Constant: '<S1>/Constant8'
   *  Sum: '<S1>/Add3'
   */
  if (rtb_DiscreteTimeIntegrator2_g < -3.14159274F) {
    rtb_DiscreteTimeIntegrator2_g += 6.28318548F;
  }

  /* End of Switch: '<S1>/Switch5' */

  /* Sum: '<S4>/Add14' incorporates:
   *  DiscreteIntegrator: '<S4>/Discrete-Time Integrator2'
   *  Gain: '<S4>/Gain'
   */
  *rty_est_omega = 0.8F * rtb_DiscreteTimeIntegrator2_g +
    localDW->DiscreteTimeIntegrator2_DSTATE;

  /* Saturate: '<S4>/Saturation1' */
  if (*rty_est_omega > 1.2F) {
    *rty_est_omega = 1.2F;
  } else {
    if (*rty_est_omega < -1.2F) {
      *rty_est_omega = -1.2F;
    }
  }

  /* End of Saturate: '<S4>/Saturation1' */

  /* Fcn: '<S1>/Fcn1' incorporates:
   *  DiscreteIntegrator: '<S4>/Discrete-Time Integrator4'
   */
  *rty_est_theta = rt_remf(localDW->DiscreteTimeIntegrator4_DSTATE, 6.28318548F);

  /* Update for Delay: '<S1>/Delay2' */
  localDW->Delay2_DSTATE = rtu_Id;

  /* Update for Delay: '<S1>/Delay3' */
  localDW->Delay3_DSTATE = rtu_Iq;

  /* Update for Delay: '<S1>/Delay8' */
  localDW->Delay8_DSTATE = *rty_est_omega;

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator2' incorporates:
   *  Gain: '<S4>/Gain7'
   */
  localDW->DiscreteTimeIntegrator2_DSTATE += 0.16F *
    rtb_DiscreteTimeIntegrator2_g * 0.0981747732F;
  if (localDW->DiscreteTimeIntegrator2_DSTATE >= 1.2F) {
    localDW->DiscreteTimeIntegrator2_DSTATE = 1.2F;
  } else {
    if (localDW->DiscreteTimeIntegrator2_DSTATE <= -1.2F) {
      localDW->DiscreteTimeIntegrator2_DSTATE = -1.2F;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator2' */

  /* Update for DiscreteIntegrator: '<S4>/Discrete-Time Integrator4' */
  localDW->DiscreteTimeIntegrator4_DSTATE += 0.0981747732F * *rty_est_omega;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
