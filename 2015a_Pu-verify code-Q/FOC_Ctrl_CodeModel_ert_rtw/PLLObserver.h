/*
 * File: PLLObserver.h
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

#ifndef RTW_HEADER_PLLObserver_h_
#define RTW_HEADER_PLLObserver_h_
#ifndef FOC_Ctrl_CodeModel_COMMON_INCLUDES_
#define FOC_Ctrl_CodeModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_Ctrl_CodeModel_COMMON_INCLUDES_ */

#include "FOC_Ctrl_CodeModel_types.h"

/* Block signals and states (default storage) for system '<Root>/PLLObserver' */
typedef struct {
  real32_T Delay2_DSTATE;              /* '<S1>/Delay2' */
  real32_T Delay3_DSTATE;              /* '<S1>/Delay3' */
  real32_T Delay8_DSTATE;              /* '<S1>/Delay8' */
  real32_T DiscreteTimeIntegrator2_DSTATE;/* '<S4>/Discrete-Time Integrator2' */
  real32_T DiscreteTimeIntegrator4_DSTATE;/* '<S4>/Discrete-Time Integrator4' */
} DW_PLLObserver_FOC_Ctrl_CodeM_T;

extern void FOC_Ctrl_CodeModel_PLLObserver(real32_T rtu_Ud, real32_T rtu_Id,
  real32_T rtu_Iq, real32_T *rty_est_theta, real32_T *rty_est_omega,
  DW_PLLObserver_FOC_Ctrl_CodeM_T *localDW);

#endif                                 /* RTW_HEADER_PLLObserver_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
