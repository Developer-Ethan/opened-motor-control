#ifndef _SVM_H_
#define _SVM_H_
#include "stdint.h"
#include "AxisTransform.h"
typedef struct
{
  uint16_t Sector;
  int16_t T1;
  int16_t T2;
  int16_t T0;
  uint16_t ModulCoeff;
  int16_t ComparePoint_1st_Up;
  int16_t ComparePoint_2nd_Up;
  int16_t ComparePoint_3th_Up;
  int16_t ComparePoint_1st_Down;
  int16_t ComparePoint_2nd_Down;
  int16_t ComparePoint_3th_Down;
  int16_t StableScale;
  int16_t ShiftScale;
  /* data */
} SVM_DEF;

#define SHIFT_PHASE_EN (1)
void Svm_Ctr(SVM_DEF *pSvm, AXIS_DEF *pAxis);
extern SVM_DEF Svm;
extern uint16_t TimerPeriod;
#endif // !1
