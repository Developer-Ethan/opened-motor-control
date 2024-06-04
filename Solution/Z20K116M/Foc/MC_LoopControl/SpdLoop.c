#include "HeadFile.h"

LOOP_CONTROL_DEF LoopCtrl;
/**
 * @brief      EstFlux_Ctr function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void SpdLoop_Control(MOTORCTRL_DEF *pMotorCtrl, LOOP_CONTROL_DEF *pLoopCtrl)
{
	TimerTick_State(&Timer_State);
	
	if(Foc.Sample_Volt < Q14(17.0/VOLT_BASE))
	{
		MotorCtrl.StartFlag = 0;
	}
	else
	{
		MotorCtrl.StartFlag = 1;
	}
	
    switch (pMotorCtrl->State)
    {
	case MotorIdle:
		pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_Q.InputRef = pLoopCtrl->OpenLoopCtrl.StartCurr;
		pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_D.InputRef = 0;
		
		break;
    case MotorAlign:
        if (pLoopCtrl->OpenLoopCtrl.AlignCurr < pLoopCtrl->OpenLoopCtrl.AlignCurr_Target)
        {
            pLoopCtrl->OpenLoopCtrl.AlignCurr += pLoopCtrl->OpenLoopCtrl.AlignCurrSlope;
        }
        else
        {
            pLoopCtrl->OpenLoopCtrl.AlignCurr = pLoopCtrl->OpenLoopCtrl.AlignCurr_Target;
        }
        pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_Q.InputRef = 0; // pLoopCtrl->OpenLoopCtrl.AlignCurr;
        pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_D.InputRef = pLoopCtrl->OpenLoopCtrl.AlignCurr;
        /* code */
        break;

    case MotorOpenLoop:
        if (pLoopCtrl->OpenLoopCtrl.OpenLoopSpd < pLoopCtrl->OpenLoopCtrl.OpenLoopSpdTarget) // speed pu = omega pu = f pu
        {
            pLoopCtrl->OpenLoopCtrl.OpenLoopSpd += pLoopCtrl->OpenLoopCtrl.SpeedSlope;
        }
        else
        {
            pLoopCtrl->OpenLoopCtrl.OpenLoopSpd = pLoopCtrl->OpenLoopCtrl.OpenLoopSpdTarget;
        }

        if (pLoopCtrl->OpenLoopCtrl.OpenLoopSpd < pLoopCtrl->OpenLoopCtrl.SwitchSpd)
        {
            pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_Q.InputRef = pLoopCtrl->OpenLoopCtrl.StartCurr;
            pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_D.InputRef = 0;
        }
        else
        {
            if (pLoopCtrl->OpenLoopCtrl.IFCurr > pLoopCtrl->OpenLoopCtrl.IFCurr_Target)
            {
                pLoopCtrl->OpenLoopCtrl.IFCurr = pLoopCtrl->OpenLoopCtrl.IFCurr - pLoopCtrl->OpenLoopCtrl.IFCurrSlope;
            }
            else
            {
                pLoopCtrl->OpenLoopCtrl.IFCurr = pLoopCtrl->OpenLoopCtrl.IFCurr_Target;
            }
            pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_Q.InputRef = pLoopCtrl->OpenLoopCtrl.IFCurr;
            pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_D.InputRef = 0;
        }
        break;
    case MotorClosedLoop:
        pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_Q.InputRef = pLoopCtrl->OpenLoopCtrl.IFCurr;//PID_Ctr(&LoopCtrl.ClosedLoopCtrl.SpdLoop, LoopCtrl.ClosedLoopCtrl.SpdLoop.InputRef - Foc.SpeedEstLpf);
        pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_D.InputRef = 0;
        break;

    default:
        break;
    }
}

/**
 * @brief      EstFlux_Ctr function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
uint16_t Angle_Given(OPENLOOP_DEF *pOpenLoop)
{
    uint16_t Angle_Temp;
    uint16_t AngleSlope_Temp;

	Angle_Temp = (pOpenLoop->OpenLoopSpd * Foc.Ts) >> 15u;
    AngleSlope_Temp = (Angle_Temp * 10430) >> 14u; // anglepu:32767 = PI*10430,65535 = 2PI*10430
    pOpenLoop->OpenLoopAngle += AngleSlope_Temp;
    return (pOpenLoop->OpenLoopAngle);
}
