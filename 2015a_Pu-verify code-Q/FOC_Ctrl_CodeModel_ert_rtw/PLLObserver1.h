/*
 * File: PLLObserver1.h
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

#ifndef RTW_HEADER_PLLObserver1_h_
#define RTW_HEADER_PLLObserver1_h_
#ifndef FOC_Ctrl_CodeModel_COMMON_INCLUDES_
#define FOC_Ctrl_CodeModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_Ctrl_CodeModel_COMMON_INCLUDES_ */

#include "FOC_Ctrl_CodeModel_types.h"

/* Block signals and states (default storage) for system '<S18>/PLLObserver1' */
typedef struct {
  real32_T Delay2_DSTATE;              /* '<S25>/Delay2' */
  real32_T Delay3_DSTATE;              /* '<S25>/Delay3' */
  real32_T Delay4_DSTATE;              /* '<S25>/Delay4' */
  real32_T Delay8_DSTATE;              /* '<S25>/Delay8' */
  real32_T DiscreteTimeIntegrator2_DSTATE;/* '<S33>/Discrete-Time Integrator2' */
  real32_T DiscreteTimeIntegrator4_DSTATE;/* '<S33>/Discrete-Time Integrator4' */
  real32_T DiscreteTimeIntegrator2_PREV_U;/* '<S33>/Discrete-Time Integrator2' */
  real32_T DiscreteTimeIntegrator4_PREV_U;/* '<S33>/Discrete-Time Integrator4' */
  uint8_T DiscreteTimeIntegrator2_SYSTEM_;/* '<S33>/Discrete-Time Integrator2' */
  uint8_T DiscreteTimeIntegrator4_SYSTEM_;/* '<S33>/Discrete-Time Integrator4' */
} DW_PLLObserver1_FOC_Ctrl_Code_T;

extern void FOC_Ctrl_Co_PLLObserver1_Enable(DW_PLLObserver1_FOC_Ctrl_Code_T
  *localDW);
extern void FOC_Ctrl_CodeModel_PLLObserver1(real32_T rtu_Ud, real32_T rtu_Id,
  real32_T rtu_Iq, real32_T *rty_est_theta, real32_T *rty_est_omega,
  DW_PLLObserver1_FOC_Ctrl_Code_T *localDW, uint32_T *rtd_NormalRunFunc_ELAPS_T);

#endif                                 /* RTW_HEADER_PLLObserver1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
