/*
 * File: SVCM.h
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

#ifndef RTW_HEADER_SVCM_h_
#define RTW_HEADER_SVCM_h_
#include <math.h>
#ifndef FOC_Ctrl_CodeModel_COMMON_INCLUDES_
#define FOC_Ctrl_CodeModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_Ctrl_CodeModel_COMMON_INCLUDES_ */

#include "FOC_Ctrl_CodeModel_types.h"

/* Block signals and states (default storage) for system '<Root>/SVCM' */
typedef struct {
  real32_T Delay7_DSTATE;              /* '<S2>/Delay7' */
  real32_T Delay6_DSTATE;              /* '<S2>/Delay6' */
  real32_T DiscreteTimeIntegrator3_DSTATE;/* '<S2>/Discrete-Time Integrator3' */
  real32_T DiscreteTimeIntegrator2_DSTATE;/* '<S2>/Discrete-Time Integrator2' */
} DW_SVCM_FOC_Ctrl_CodeModel_T;

extern void FOC_Ctrl_CodeModel_SVCM(real32_T rtu_Ualpha, real32_T rtu_Ubeta,
  real32_T rtu_Ia, real32_T rtu_Ib, real32_T rtu_Ic, real32_T *rty_est_Speed,
  real32_T *rty_est_Theta, DW_SVCM_FOC_Ctrl_CodeModel_T *localDW);

#endif                                 /* RTW_HEADER_SVCM_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
