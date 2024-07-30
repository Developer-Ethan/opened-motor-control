/*
 * File: FOC_Ctrl_CodeModel.h
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

#ifndef RTW_HEADER_FOC_Ctrl_CodeModel_h_
#define RTW_HEADER_FOC_Ctrl_CodeModel_h_
#include <math.h>
#ifndef FOC_Ctrl_CodeModel_COMMON_INCLUDES_
#define FOC_Ctrl_CodeModel_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* FOC_Ctrl_CodeModel_COMMON_INCLUDES_ */

#include "FOC_Ctrl_CodeModel_types.h"

/* Child system includes */
#include "PLLObserver.h"
#include "PLLObserver1.h"
#include "SVCM.h"

/* Includes for objects with custom storage classes. */
#include "Parameter.h"

/* Macros for accessing real-time model data structure */

/* Block signals and states (default storage) for system '<S8>/NormalRunFunc' */
typedef struct {
  DW_PLLObserver1_FOC_Ctrl_Code_T PLLObserver1;/* '<S18>/PLLObserver1' */
  strcutFocInternalPara FocInternalPara;/* '<S18>/Data Store Memory' */
  real32_T DiscreteTimeIntegrator1_DSTATE;/* '<S30>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator2_DSTATE;/* '<S30>/Discrete-Time Integrator2' */
  real32_T UnitDelay_DSTATE;           /* '<S31>/Unit Delay' */
  real32_T DiscreteTimeIntegrator1_PREV_U;/* '<S30>/Discrete-Time Integrator1' */
  real32_T DiscreteTimeIntegrator2_PREV_U;/* '<S30>/Discrete-Time Integrator2' */
  uint32_T NormalRunFunc_PREV_T;       /* '<S8>/NormalRunFunc' */
  uint16_T temporalCounter_i1;         /* '<S18>/Chart' */
  uint8_T DiscreteTimeIntegrator1_SYSTEM_;/* '<S30>/Discrete-Time Integrator1' */
  uint8_T DiscreteTimeIntegrator2_SYSTEM_;/* '<S30>/Discrete-Time Integrator2' */
  uint8_T is_active_c3_FOC_Ctrl_CodeModel;/* '<S18>/Chart' */
  uint8_T is_c3_FOC_Ctrl_CodeModel;    /* '<S18>/Chart' */
  boolean_T NormalRunFunc_RESET_ELAPS_T;/* '<S8>/NormalRunFunc' */
} DW_NormalRunFunc_FOC_Ctrl_Cod_T;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_NormalRunFunc_FOC_Ctrl_Cod_T NormalRunFunc;/* '<S8>/NormalRunFunc' */
  DW_SVCM_FOC_Ctrl_CodeModel_T SVCM;   /* '<Root>/SVCM' */
  DW_PLLObserver_FOC_Ctrl_CodeM_T PLLObserver;/* '<Root>/PLLObserver' */
  structFOC varFOC;                    /* '<S3>/Data Store Memory26' */
  real32_T UnitDelay_DSTATE;           /* '<S14>/Unit Delay' */
  real32_T UnitDelay_DSTATE_b;         /* '<S15>/Unit Delay' */
  real32_T UnitDelay_DSTATE_f;         /* '<S16>/Unit Delay' */
  uint16_T CalCnt;                     /* '<S3>/Chart' */
  uint8_T is_active_c1_FOC_Ctrl_CodeModel;/* '<S3>/Chart' */
  uint8_T is_c1_FOC_Ctrl_CodeModel;    /* '<S3>/Chart' */
  uint8_T is_Run;                      /* '<S3>/Chart' */
  boolean_T InitDone;                  /* '<S3>/Chart' */
} DW_FOC_Ctrl_CodeModel_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uint16_T ADCinput[5];                /* '<Root>/ADCinput' */
  boolean_T MotorSwitch;               /* '<Root>/MotorSwitch' */
  boolean_T FaultSwitch;               /* '<Root>/FaultSwitch' */
  real32_T Input;                      /* '<Root>/Input' */
  real32_T Input1;                     /* '<Root>/Input1' */
  real32_T Input2;                     /* '<Root>/Input2' */
  real32_T Input3;                     /* '<Root>/Input3' */
  real32_T Input4;                     /* '<Root>/Input4' */
  int16_T Input5;                      /* '<Root>/Input5' */
} ExtU_FOC_Ctrl_CodeModel_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T DUTY[3];                    /* '<Root>/DUTY' */
  boolean_T LED[3];                    /* '<Root>/LED' */
  real32_T Output;                     /* '<Root>/Output' */
  real32_T Output1;                    /* '<Root>/Output1' */
  int16_T Output2;                     /* '<Root>/Output2' */
} ExtY_FOC_Ctrl_CodeModel_T;

/* Real-time Model Data Structure */
struct tag_RTM_FOC_Ctrl_CodeModel_T {
  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
  } Timing;
};

/* Block signals and states (default storage) */
extern DW_FOC_Ctrl_CodeModel_T FOC_Ctrl_CodeModel_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_FOC_Ctrl_CodeModel_T FOC_Ctrl_CodeModel_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_FOC_Ctrl_CodeModel_T FOC_Ctrl_CodeModel_Y;

/* Model entry point functions */
extern void FOC_Ctrl_CodeModel_initialize(void);
extern void FOC_Ctrl_CodeModel_step(void);

/* Real-time Model object */
extern RT_MODEL_FOC_Ctrl_CodeModel_T *const FOC_Ctrl_CodeModel_M;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S2>/Constant2' : Unused code path elimination
 * Block '<S2>/Constant3' : Unused code path elimination
 * Block '<S2>/Display1' : Unused code path elimination
 * Block '<S2>/Scope' : Unused code path elimination
 * Block '<S2>/Scope1' : Unused code path elimination
 * Block '<S2>/Sign' : Unused code path elimination
 * Block '<S14>/Data Type Duplicate' : Unused code path elimination
 * Block '<S15>/Data Type Duplicate' : Unused code path elimination
 * Block '<S16>/Data Type Duplicate' : Unused code path elimination
 * Block '<S31>/Data Type Duplicate' : Unused code path elimination
 * Block '<S27>/Data Type Duplicate' : Unused code path elimination
 * Block '<S30>/Scope' : Unused code path elimination
 * Block '<S30>/Scope1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'FOC_Ctrl_CodeModel'
 * '<S1>'   : 'FOC_Ctrl_CodeModel/PLLObserver'
 * '<S2>'   : 'FOC_Ctrl_CodeModel/SVCM'
 * '<S3>'   : 'FOC_Ctrl_CodeModel/Subsystem Reference'
 * '<S4>'   : 'FOC_Ctrl_CodeModel/PLLObserver/PLL'
 * '<S5>'   : 'FOC_Ctrl_CodeModel/SVCM/clark1'
 * '<S6>'   : 'FOC_Ctrl_CodeModel/SVCM/park0'
 * '<S7>'   : 'FOC_Ctrl_CodeModel/SVCM/park1'
 * '<S8>'   : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart'
 * '<S9>'   : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/CalFunc'
 * '<S10>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/FaultFunc'
 * '<S11>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/InitFunc'
 * '<S12>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc'
 * '<S13>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/ReadyFunc'
 * '<S14>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/CalFunc/IIR Filter'
 * '<S15>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/CalFunc/IIR Filter1'
 * '<S16>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/CalFunc/IIR Filter2'
 * '<S17>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Pre_Data_Process'
 * '<S18>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Subsystem Reference'
 * '<S19>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Pre_Data_Process/Subsystem'
 * '<S20>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Pre_Data_Process/Subsystem1'
 * '<S21>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Pre_Data_Process/Subsystem2'
 * '<S22>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Pre_Data_Process/Subsystem3'
 * '<S23>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Subsystem Reference/Chart'
 * '<S24>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Subsystem Reference/Open Calculation'
 * '<S25>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Subsystem Reference/PLLObserver1'
 * '<S26>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Subsystem Reference/Park'
 * '<S27>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Subsystem Reference/Space Vector Generator'
 * '<S28>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Subsystem Reference/ai-park'
 * '<S29>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Subsystem Reference/clark'
 * '<S30>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Subsystem Reference/current loop'
 * '<S31>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Subsystem Reference/Open Calculation/IIR Filter'
 * '<S32>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Subsystem Reference/Open Calculation/If Action Subsystem'
 * '<S33>'  : 'FOC_Ctrl_CodeModel/Subsystem Reference/Chart/NormalRunFunc/Subsystem Reference/PLLObserver1/PLL'
 */
#endif                                 /* RTW_HEADER_FOC_Ctrl_CodeModel_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
