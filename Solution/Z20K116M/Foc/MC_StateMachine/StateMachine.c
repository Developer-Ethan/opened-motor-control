#include "HeadFile.h"

MOTORCTRL_DEF MotorCtrl;
/**
 * @brief      MotorStateMachine function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void MotorStateMachine(MOTORCTRL_DEF *pMotorCtrl, TIMER_STATE_DEF *pTimer_State)
{
    switch (pMotorCtrl->State)
    {
    case MotorPowerOn:
        Timer_Start(&pTimer_State->Timer_Stable, pTimer_State->Time_Stable);
        pMotorCtrl->State = MotorStable;
        /* code */
        break;
    case MotorStable:
        if (Timer_Timeout(&pTimer_State->Timer_Stable))
        {
            Timer_Start(&pTimer_State->Timer_Calibrate, pTimer_State->Time_Calibrate);
            pMotorCtrl->State = MotorCalibrate;
            pMotorCtrl->OffsetFlag = 1;
        }
        break;
    case MotorCalibrate:
        if (Timer_Timeout(&pTimer_State->Timer_Calibrate))
        {
            // GPIO_Pins_Set(GPIOB, GPIO_PIN_3);
            pMotorCtrl->OffsetFlag = 0;
            pMotorCtrl->CalibrateOverFlag = 1;
            pMotorCtrl->State = MotorIdle;
        }
        /* code */
        break;
    case MotorIdle:
        if (pMotorCtrl->StartFlag == 1)
        {
            // GPIO_Pins_Reset(GPIOB, GPIO_PIN_3);
            Timer_Start(&pTimer_State->Timer_Align, pTimer_State->Time_Align);
            pMotorCtrl->State = MotorAlign;
        }
        /* code */
        break;
    case MotorAlign:
        if (Timer_Timeout(&pTimer_State->Timer_Align))
        {
            Timer_Start(&pTimer_State->Timer_OpenLoop, pTimer_State->Time_OpenLoop);
            pMotorCtrl->State = MotorOpenLoop;
            OpenLoop_Init();
        }
        /* code */
        break;
    case MotorOpenLoop:
        if (Timer_Timeout(&pTimer_State->Timer_OpenLoop) && (LoopCtrl.OpenLoopCtrl.IFCurr == LoopCtrl.OpenLoopCtrl.IFCurr_Target))
        {
            pMotorCtrl->State = MotorClosedLoop;
            ClosedLoop_Init();
        }
        /* code */
        break;
    case MotorClosedLoop:
        if (pMotorCtrl->StartFlag == 0)
        {
            pMotorCtrl->State = MotorShutdown;
        }
        /* code */
        break;
    case MotorShutdown:
        pMotorCtrl->State = MotorIdle;
        // Foc_Init();
        break;
    case MotorFault:
        pMotorCtrl->State = MotorIdle;
        break;
    }
}
