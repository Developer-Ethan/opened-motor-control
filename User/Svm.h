#ifndef _SVM_H_
#define _SVM_H_
#include "stdint.h"
typedef struct
{
  uint16_t Angle;
  uint16_t Angle_D;
  uint16_t Sector;
  uint16_t Amp;
  uint16_t T1;
  uint16_t T2;
  uint16_t ModulCoeff;
  int16_t ComparePoint_1st_Up;
  int16_t ComparePoint_2nd_Up;
  int16_t ComparePoint_3th_Up;
  int16_t ComparePoint_1st_Up_Last;
  int16_t ComparePoint_2nd_Up_Last;
  int16_t ComparePoint_3th_Up_Last;
  int16_t ComparePoint_1st_Down;
  int16_t ComparePoint_2nd_Down;
  int16_t ComparePoint_3th_Down;
  int16_t StableScale;
  int16_t ShiftScale;
  /* data */
} SVM_DEF;

#define SHIFT_PHASE_EN (0)
void Svm_Ctr(SVM_DEF *pSvm, AXIS_DEF *pAxis);
extern SVM_DEF Svm;
extern uint16_t TimerPeriod;
#endif // !1
