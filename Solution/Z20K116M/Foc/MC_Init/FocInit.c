#include "HeadFile.h"

FOC_DEF Foc;
MOTOR_PARAMETER_DEF Motor_Param =
    {
        RS_PHASE,
        LD_PHASE,
        LQ_PHASE,
        IND_PHASE,
        POLE_PAIRS,
        VOLT_RATE,
        CURR_RATE,
        EFREQ_RATE,
        EMF_COEFF,
        FLUX_RATE,

        RS_BASE,
        L_BASE,
        VOLT_BASE,
        CURR_BASE,
        SPEED_BASE,
        OMEGA_BASE,
        FLUX_BASE,
};
/**
 * @brief      Foc_Init function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void Foc_Init(void)
{
    memset(&LoopCtrl, 0, sizeof(LOOP_CONTROL_DEF));
    memset(&Foc, 0, sizeof(FOC_DEF));

    Foc.PhaseRes_Pu = Motor_Param.PhaseRes / Motor_Param.PhaseRes_Base;
    Foc.PhaseInd_Pu = Motor_Param.PhaseInd / Motor_Param.PhaseInd_Base;
    Foc.PhaseRes = Q14(Foc.PhaseRes_Pu);
    Foc.PhaseInd = Q14(Foc.PhaseInd_Pu);
    Foc.TsPu = PWM_PERIOD / T_BASE;
    Foc.Ts = Q15(Foc.TsPu);
    Foc.FluxPu = FLUX_RATE / FLUX_BASE;
    Foc.Flux = Q14(Foc.FluxPu);
    Foc.SvcmGain = Q15(GAIN_SVCM);
    Foc.Angle_Align = ALIGN_ANGLE;
    Foc.BandWidthPu_CurrLoop = BANDWIDTH_CURRLOOP / Motor_Param.EfreqRated;

    Foc.Lpf_EmfEstReal.BandWidthPu = BANDWIDTH_EMFLPF / Motor_Param.EfreqRated;
    Foc.Lpf_EmfEstReal.Coeff = Q15(1 / (1 + Foc.Lpf_EmfEstReal.BandWidthPu * Foc.TsPu));
    Foc.Lpf_EmfEstImag.BandWidthPu = BANDWIDTH_EMFLPF / Motor_Param.EfreqRated;
    Foc.Lpf_EmfEstImag.Coeff = Q15(1 / (1 + Foc.Lpf_EmfEstImag.BandWidthPu * Foc.TsPu));
    Foc.Lpf_SpeedEst.BandWidthPu = BANDWIDTH_SPDLPF / Motor_Param.EfreqRated;
    Foc.Lpf_EmfEstReal.Coeff = Q15(1 / (1 + Foc.Lpf_SpeedEst.BandWidthPu * Foc.TsPu));
	
    Foc.BandWidthPu_PllLoop = BANDWIDTH_PLLLOOP / Motor_Param.EfreqRated;

    Foc.Smo_Ctrl.Factor1 = Q15(PWM_PERIOD * Motor_Param.PhaseRes_Base / Motor_Param.PhaseInd);
    Foc.Smo_Ctrl.Factor2 = Q15(PWM_PERIOD * Motor_Param.PhaseRes / Motor_Param.PhaseInd);
    Foc.Smo_Ctrl.SmoGain = Q14(SMO_GAIN);
    Foc.Smo_Ctrl.SmoErrWidth = Q14(SMO_ERRWIDTH);
    Foc.Smo_Ctrl.SmoSlope = (SMO_GAIN / SMO_ERRWIDTH);

    Foc.BandWidthPu_SpdLoop = BANDWIDTH_SPDLOOP / Motor_Param.EfreqRated;

    LoopCtrl.ClosedLoopCtrl.PLLLoop.Pid_Ki = Q14(Foc.BandWidthPu_PllLoop * Foc.BandWidthPu_PllLoop * Foc.TsPu);
    LoopCtrl.ClosedLoopCtrl.PLLLoop.Pid_Kp = Q14(2 * Foc.BandWidthPu_PllLoop);
    LoopCtrl.ClosedLoopCtrl.PLLLoop.OutMax = OUT_MAX_PLLLOOP;
    LoopCtrl.ClosedLoopCtrl.PLLLoop.OutMin = OUT_MIN_PLLLOOP;
    LoopCtrl.ClosedLoopCtrl.PLLLoop.I_Out = 0;

    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.Pid_Ki = (int16_t)(Foc.BandWidthPu_CurrLoop * Foc.PhaseRes * Foc.TsPu); // KI_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.Pid_Kp = (int16_t)(Foc.BandWidthPu_CurrLoop * Foc.PhaseInd);            // KP_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.OutMax = OUT_MAX_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.OutMin = OUT_MIN_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.I_Out = 0;

    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.Pid_Ki = (int16_t)(Foc.BandWidthPu_CurrLoop * Foc.PhaseRes * Foc.TsPu);
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.Pid_Kp = (int16_t)(Foc.BandWidthPu_CurrLoop * Foc.PhaseInd);
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.OutMax = OUT_MAX_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.OutMin = OUT_MIN_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.I_Out = 0;

    LoopCtrl.ClosedLoopCtrl.SpdLoop.Pid_Ki = KI_SPDLOOP;
    LoopCtrl.ClosedLoopCtrl.SpdLoop.Pid_Kp = KP_SPDLOOP;
    LoopCtrl.ClosedLoopCtrl.SpdLoop.OutMax = OUT_MAX_SPDLOOP;
    LoopCtrl.ClosedLoopCtrl.SpdLoop.OutMin = OUT_MIN_SPDLOOP;
    LoopCtrl.ClosedLoopCtrl.SpdLoop.I_Out = 0;

    LoopCtrl.OpenLoopCtrl.AlignCurr_Target = Q14(ALIGN_CURR_OPENLOOP / CURR_BASE);
    LoopCtrl.OpenLoopCtrl.AlignCurrSlope = Q14(ALIGN_CURR_SLOPE / CURR_BASE);
    LoopCtrl.OpenLoopCtrl.StartCurr = Q14(START_CURR_OPENLOOP / CURR_BASE);
    LoopCtrl.OpenLoopCtrl.IFCurr = LoopCtrl.OpenLoopCtrl.StartCurr;
    LoopCtrl.OpenLoopCtrl.IFCurr_Target = Q14(IFCURR_TARGET / CURR_BASE);
    LoopCtrl.OpenLoopCtrl.IFCurrSlope = Q14(IFCURR_SLOPE / CURR_BASE);
    LoopCtrl.OpenLoopCtrl.SwitchSpd = Q14(SPEED_SWITCH_OPENLOOP / SPEED_BASE);
    LoopCtrl.OpenLoopCtrl.OpenLoopSpdTarget = Q14(SPEED_TARGET_OPENLOOP / SPEED_BASE);
    LoopCtrl.OpenLoopCtrl.SpeedSlope = Q14(SPEED_SLOPE / SPEED_BASE);

    Svm.ShiftScale = SHIFT_SCALE;
    Svm.StableScale = STABLE_SCALE;
	Svm.CompareValue_SimplePoint1 = PWM_MOD >> 3;
	Svm.CompareValue_SimplePoint2 = PWM_MOD >> 2;

    LoopCtrl.ClosedLoopCtrl.SpdLoop.InputRef = Q14(600.0f / SPEED_BASE);
}

/**
 * @brief      OpenLoop_Init function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void ClosedLoop_Init(void)
{
    LoopCtrl.ClosedLoopCtrl.PLLLoop.I_Out = LoopCtrl.OpenLoopCtrl.OpenLoopSpd << 14u;
	Foc.AngleEst = Foc.AngleOpen;
	Foc.SpeedEstLpf = LoopCtrl.OpenLoopCtrl.OpenLoopSpd;
    LoopCtrl.ClosedLoopCtrl.SpdLoop.I_Out = LoopCtrl.OpenLoopCtrl.IFCurr << 14u;
}

/**
 * @brief      OpenLoop_Init function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void OpenLoop_Init(void)
{
    LoopCtrl.OpenLoopCtrl.OpenLoopAngle = Foc.Angle_Align;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.InputRef = LoopCtrl.OpenLoopCtrl.StartCurr;
}
/**
 * @brief      EstFlux_Ctr function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
inline void LimitedCircle_Voltage(AXIS_DEF *pAxis)
{
    uint32_t ComposedVectorVoltAmp2;
    uint32_t LimitedVoltage;
    int16_t Uq_Max, Ud_Max;
    int16_t Temp;

    ComposedVectorVoltAmp2 = pAxis->Imag * pAxis->Imag + pAxis->Real * pAxis->Real;
    LimitedVoltage = Foc.Sample_Volt * MODULE_COEFF >> SHIFT_15BITS;
    Uq_Max = LimitedVoltage * UQ_LIMIT >> SHIFT_15BITS;
    Ud_Max = LimitedVoltage * UD_LIMIT >> SHIFT_15BITS;
    LimitedVoltage = LimitedVoltage * LimitedVoltage;

    if (ComposedVectorVoltAmp2 > LimitedVoltage)
    {
        if ((ABS(pAxis->Imag)) > Uq_Max)
        {
            if (pAxis->Imag > 0)
            {
                pAxis->Imag = Uq_Max;
            }
            else
            {
                pAxis->Imag = -Uq_Max;
            }

            if (pAxis->Real > 0)
            {
                pAxis->Real = Ud_Max;
            }
            else
            {
                pAxis->Real = -Ud_Max;
            }
        }
        else
        {
            Temp = pAxis->Real;
            Temp = (Temp / LimitedVoltage) << 8;

            if (Temp > 256)
            {
                Temp = 256;
            }

            Temp = Table_Sqrt[Temp];
            Temp = Temp * LimitedVoltage >> 8;

            if (pAxis->Imag > 0)
            {
                pAxis->Imag = Temp;
            }
            else
            {
                pAxis->Imag = -Temp;
            }
        }
    }
}
