/*
 * File: FOC_Ctrl_CodeModel_private.h
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

#ifndef RTW_HEADER_FOC_Ctrl_CodeModel_private_h_
#define RTW_HEADER_FOC_Ctrl_CodeModel_private_h_
#include "rtwtypes.h"
#include "FOC_Ctrl_CodeModel.h"

extern void FOC_Ctrl_CodeMode_InitFunc_Init(real32_T rty_dutyOut[3], boolean_T
  rty_ledOut[3]);
extern void FOC_Ctrl_CodeModel_InitFunc(real32_T rty_dutyOut[3], boolean_T
  rty_ledOut[3], structFOC *rtd_varFOC);
extern void FOC_Ctrl_CodeMod_FaultFunc_Init(real32_T rty_dutyOut[3], boolean_T
  rty_ledOut[3]);
extern void FOC_Ctrl_CodeModel_FaultFunc(real32_T rty_dutyOut[3], boolean_T
  rty_ledOut[3]);
extern void FOC_Ctrl_CodeMod_ReadyFunc_Init(real32_T rty_dutyOut[3], boolean_T
  rty_ledOut[3]);
extern void FOC_Ctrl_CodeModel_ReadyFunc(real32_T rty_dutyOut[3], boolean_T
  rty_ledOut[3]);
extern void FOC_Ctrl_Cod_NormalRunFunc_Init(boolean_T rty_ledOut[3]);
extern void FOC_Ctrl_C_NormalRunFunc_Enable(DW_NormalRunFunc_FOC_Ctrl_Cod_T
  *localDW);
extern void FOC_Ctrl_CodeMode_NormalRunFunc(RT_MODEL_FOC_Ctrl_CodeModel_T *
  const FOC_Ctrl_CodeModel_M, const uint16_T rtu_dataRaw[5], real32_T
  rty_dutyOut[3], boolean_T rty_ledOut[3], DW_NormalRunFunc_FOC_Ctrl_Cod_T
  *localDW, structFOC *rtd_varFOC);

#endif                            /* RTW_HEADER_FOC_Ctrl_CodeModel_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
