#include "HeadFile.h"

TIMER_STATE_DEF Timer_State;
TIMER_DEF Timer;

/**
 * @brief      Timer_Init function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void Timer_Init(TIMER_DEF *pTimer)
{
    pTimer->Counter = 0;
    pTimer->Period = 0;
    pTimer->Enable = 0;
    pTimer->Overflow = 0;
}

/**
 * @brief      Timer_Start function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
inline void Timer_Start(TIMER_DEF *pTimer, uint32_t Period)
{
    pTimer->Counter = 0;
    pTimer->Period = Period;
    pTimer->Enable = 1;
    pTimer->Overflow = 0;
}

/**
 * @brief      Timer_Tick function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
inline void Timer_Tick(TIMER_DEF *pTimer)
{
    if ((pTimer->Enable == 1) && (pTimer->Overflow == 0))
    {
        if (pTimer->Counter < pTimer->Period)
        {
            pTimer->Counter++;
            if (pTimer->Counter == pTimer->Period)
            {
                pTimer->Overflow = 1;
            }
        }
    }
}

/**
 * @brief      TimerTick_State function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
inline void TimerTick_State(TIMER_STATE_DEF *pTimer_State)
{
    Timer_Tick(&pTimer_State->Timer_Stable);
    Timer_Tick(&pTimer_State->Timer_Calibrate);
    Timer_Tick(&pTimer_State->Timer_Idle);
    Timer_Tick(&pTimer_State->Timer_Align);
    Timer_Tick(&pTimer_State->Timer_OpenLoop);
    Timer_Tick(&pTimer_State->Timer_ClosedLoop);
}

/**
 * @brief      Timer_Timeout function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
inline uint8_t Timer_Timeout(TIMER_DEF *pTimer)
{
    return pTimer->Overflow;
}

/**
 * @brief      Timer_Init function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void Timer_State_Init(void)
{
		Timer_Init(&Timer_State.Timer_Stable);
    Timer_Init(&Timer_State.Timer_Calibrate);
    Timer_Init(&Timer_State.Timer_Idle);
    Timer_Init(&Timer_State.Timer_Align);
    Timer_Init(&Timer_State.Timer_OpenLoop);

    Timer_State.Time_Stable = TIME_STABLE;
    Timer_State.Time_Calibrate = TIME_CALIBRATE;
    Timer_State.Time_Idle = TIME_IDLE;
    Timer_State.Time_Align = TIME_ALIGN;
    Timer_State.Time_OpenLoop = TIME_OPENLOOP;
}
