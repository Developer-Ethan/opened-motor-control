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
    switch (pMotorCtrl->State)
    {
    case MotorAlign:
        if (pLoopCtrl->OpenLoopCtrl.AlignCurr < pLoopCtrl->OpenLoopCtrl.AlignCurr_Target)
        {
            pLoopCtrl->OpenLoopCtrl.AlignCurr += pLoopCtrl->OpenLoopCtrl.AlignCurrSlope;
        }
        else
        {
            pLoopCtrl->OpenLoopCtrl.AlignCurr = pLoopCtrl->OpenLoopCtrl.AlignCurr_Target;
        }
        pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_Q.InputRef = pLoopCtrl->OpenLoopCtrl.AlignCurr;
				pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_D.InputRef = 0;
        /* code */
        break;

    case MotorOpenLoop:
        if (pLoopCtrl->OpenLoopCtrl.OpenLoopSpd < pLoopCtrl->OpenLoopCtrl.OpenLoopSpdTarget)//speed pu = omega pu = f pu
        {
            pLoopCtrl->OpenLoopCtrl.OpenLoopSpd += pLoopCtrl->OpenLoopCtrl.SpeedSlope;
        }
        else
        {
            pLoopCtrl->OpenLoopCtrl.OpenLoopSpd = pLoopCtrl->OpenLoopCtrl.OpenLoopSpdTarget;
        }

        pLoopCtrl->OpenLoopCtrl.AngleSlope = DataMult_Q15(pLoopCtrl->OpenLoopCtrl.OpenLoopSpd, Foc.TsPu);

        if (pLoopCtrl->OpenLoopCtrl.OpenLoopSpd < pLoopCtrl->OpenLoopCtrl.SwitchSpd)
        {
            pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_Q.InputRef = pLoopCtrl->OpenLoopCtrl.StartCurr;
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
            pLoopCtrl->ClosedLoopCtrl.SpdLoop.I_Out = pLoopCtrl->OpenLoopCtrl.IFCurr;
        }
				break;
    case MotorClosedLoop:
        pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_Q.InputRef = PID_Ctr(&LoopCtrl.ClosedLoopCtrl.SpdLoop, LoopCtrl.ClosedLoopCtrl.SpdLoop.InputRef - Foc.SpeedEst);
				pLoopCtrl->ClosedLoopCtrl.CurrLoop.Pi_D.InputRef = 0;
        break;

    default:
        break;
    }
}
