#ifndef _LOOPCONTROL_H_
#define _LOOPCONTROL_H_
#include "stdint.h"
#include "PI.h"
#include "StateMachine.h"
typedef struct
{
  PI_DEF SpdLoop;
  PI_DEF PLLLoop;
  PI_DQ_DEF CurrLoop;
  /* data */
} CLOSEDLOOP_DEF;

typedef struct
{
  int16_t SpeedSlope;
  int16_t OpenLoopSpd;
  int16_t OpenLoopSpdTarget;
  int16_t AngleSlope;
  int16_t SwitchSpd;
  uint16_t OpenLoopAngle;

  int16_t AlignCurr;
  int16_t AlignCurr_Target;
  int16_t AlignCurrSlope;

  int16_t StartCurr;
  int16_t IFCurr_Target;
  int16_t IFCurr;
  int16_t IFCurrSlope;
  /* data */
} OPENLOOP_DEF;

typedef struct
{
  CLOSEDLOOP_DEF ClosedLoopCtrl;
  OPENLOOP_DEF OpenLoopCtrl;
  /* data */
} LOOP_CONTROL_DEF;

extern LOOP_CONTROL_DEF LoopCtrl;
void SpdLoop_Control(MOTORCTRL_DEF *pMotorCtrl, LOOP_CONTROL_DEF *pLoopCtrl);
uint16_t Angle_Given(OPENLOOP_DEF *pOpenLoop);
#endif // !_LOOPCONTROL_H_
