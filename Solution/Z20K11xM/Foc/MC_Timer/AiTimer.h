#ifndef _TIMER_H_
#define _TIMER_H_
#include "stdint.h"
typedef struct
{
    uint32_t Counter;
    uint32_t Period;
    uint8_t Overflow;
    uint8_t Enable;
    /* data */
} TIMER_DEF;

typedef struct
{
    uint16_t Time_Stable;
    uint16_t Time_Calibrate;
    uint16_t Time_Idle;
    uint16_t Time_Align;
    uint16_t Time_OpenLoop;
    TIMER_DEF Timer_Stable;
    TIMER_DEF Timer_Calibrate;
    TIMER_DEF Timer_Idle;
    TIMER_DEF Timer_Align;
    TIMER_DEF Timer_OpenLoop;
    TIMER_DEF Timer_ClosedLoop;
    /* data */
} TIMER_STATE_DEF;

void Timer_Start(TIMER_DEF *pTimer, uint32_t Period);
void Timer_Tick(TIMER_DEF *pTimer);
void TimerTick_State(TIMER_STATE_DEF *pTimer_State);
uint8_t Timer_Timeout(TIMER_DEF *pTimer);
extern TIMER_STATE_DEF Timer_State;
extern TIMER_DEF Timer;
extern void Timer_Init(TIMER_DEF *pTimer);
extern void Timer_State_Init(void);
#endif
