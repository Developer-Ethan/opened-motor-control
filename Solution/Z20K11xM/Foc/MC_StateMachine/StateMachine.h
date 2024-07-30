#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_
#include "stdint.h"
#include "AiTimer.h"
typedef struct
{
  uint8_t State;
  uint8_t OffsetFlag;
  uint8_t StartFlag;
  uint8_t CalibrateOverFlag;
  /* data */
} MOTORCTRL_DEF;

typedef enum
{
  MotorPowerOn = 0,
  MotorStable,
  MotorCalibrate,
  MotorIdle,
  MotorAlign,
  MotorOpenLoop,
  MotorClosedLoop,
  MotorShutdown,
  MotorFault,
} MOTOR_STATE_DEF;

void MotorStateMachine(MOTORCTRL_DEF *pMotorCtrl, TIMER_STATE_DEF *pTimer_State);
extern MOTORCTRL_DEF MotorCtrl;
#endif // !_STATEMACHINE_H
