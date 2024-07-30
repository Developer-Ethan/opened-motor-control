/*
 * File: rt_remf.c
 *
 * Code generated for Simulink model 'FOC_Ctrl_CodeModel'.
 *
 * Model version                  : 1.13
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Thu Jul 25 15:02:54 2024
 */

#include "rtwtypes.h"
#include <float.h>
#include <math.h>
#include "rt_remf.h"

real32_T rt_remf(real32_T u0, real32_T u1)
{
  real32_T q;
  real32_T y;
  if ((boolean_T)((u1 != 0.0F) & (u1 != truncf(u1)))) {
    q = fabsf(u0 / u1);
    if (fabsf(q - floorf(q + 0.5F)) <= FLT_EPSILON * q) {
      y = 0.0F;
    } else {
      y = fmodf(u0, u1);
    }
  } else {
    y = fmodf(u0, u1);
  }

  return y;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
