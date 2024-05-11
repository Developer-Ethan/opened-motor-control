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
    Foc.PhaseRes = Q15(Foc.PhaseRes_Pu);
    Foc.PhaseInd = Q15(Foc.PhaseInd_Pu);
    Foc.TsPu = PWM_PERIOD / T_BASE;
    Foc.Ts = Q15(Foc.TsPu);
    Foc.Angle_Align = ALIGN_ANGLE;
    Foc.BandWidthPu_CurrLoop = BANDWIDTH_CURRLOOP / Motor_Param.EfreqRated;

    Foc.Lpf_EmfEstReal.BandWidthPu = BANDWIDTH_EMFLPF / Motor_Param.EfreqRated;
    Foc.Lpf_EmfEstReal.Coeff = Q15(1 / (1 + Foc.Lpf_EmfEstReal.BandWidthPu * Foc.TsPu));
    Foc.Lpf_EmfEstImag.BandWidthPu = BANDWIDTH_EMFLPF / Motor_Param.EfreqRated;
    Foc.Lpf_EmfEstImag.Coeff = Q15(1 / (1 + Foc.Lpf_EmfEstImag.BandWidthPu * Foc.TsPu));
    Foc.BandWidthPu_PllLoop = BANDWIDTH_PLLLOOP / Motor_Param.EfreqRated;

    Foc.Smo_Ctrl.Factor1 = Q15(PWM_PERIOD * Motor_Param.PhaseRes_Base / Motor_Param.PhaseInd);
    Foc.Smo_Ctrl.Factor2 = Q15(PWM_PERIOD * Motor_Param.PhaseRes / Motor_Param.PhaseInd);
    Foc.Smo_Ctrl.SmoGain = Q14(SMO_GAIN);
    Foc.Smo_Ctrl.SmoErrWidth = Q14(SMO_ERRWIDTH);
    Foc.Smo_Ctrl.SmoSlope = (SMO_GAIN / SMO_ERRWIDTH);

    LoopCtrl.ClosedLoopCtrl.PLLLoop.Pid_Ki = Q15(Foc.BandWidthPu_PllLoop * Foc.BandWidthPu_PllLoop);
    LoopCtrl.ClosedLoopCtrl.PLLLoop.Pid_Kp = Q15(2 * Foc.BandWidthPu_PllLoop);
    LoopCtrl.ClosedLoopCtrl.PLLLoop.Iout_Max = IOUT_MAX_PLLLOOP;
    LoopCtrl.ClosedLoopCtrl.PLLLoop.Iout_Min = IOUT_MIN_PLLLOOP;
    LoopCtrl.ClosedLoopCtrl.PLLLoop.Out_Max = PIOUT_MAX_PLLLOOP;
    LoopCtrl.ClosedLoopCtrl.PLLLoop.Out_Min = PIOUT_MIN_PLLLOOP;
    LoopCtrl.ClosedLoopCtrl.PLLLoop.I_Out = 0;

    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.Pid_Ki = (Foc.BandWidthPu_CurrLoop * Foc.PhaseRes); // KI_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.Pid_Kp = (Foc.BandWidthPu_CurrLoop * Foc.PhaseInd); // KP_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.Iout_Max = IOUT_MAX_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.Iout_Min = IOUT_MIN_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.Out_Max = PIOUT_MAX_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.Out_Min = PIOUT_MIN_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.I_Out = 0;

    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.Pid_Ki = (Foc.BandWidthPu_CurrLoop * Foc.PhaseRes);
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.Pid_Kp = (Foc.BandWidthPu_CurrLoop * Foc.PhaseInd);
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.Iout_Max = IOUT_MAX_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.Iout_Min = IOUT_MIN_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.Out_Max = PIOUT_MAX_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.Out_Min = PIOUT_MIN_CURRLOOP;
    LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.I_Out = 0;

    LoopCtrl.ClosedLoopCtrl.SpdLoop.Pid_Ki = KI_SPDLOOP;
    LoopCtrl.ClosedLoopCtrl.SpdLoop.Pid_Kp = KP_SPDLOOP;
    LoopCtrl.ClosedLoopCtrl.SpdLoop.Iout_Max = IOUT_MAX_SPDLOOP;
    LoopCtrl.ClosedLoopCtrl.SpdLoop.Iout_Min = IOUT_MIN_SPDLOOP;
    LoopCtrl.ClosedLoopCtrl.SpdLoop.Out_Max = PIOUT_MAX_SPDLOOP;
    LoopCtrl.ClosedLoopCtrl.SpdLoop.Out_Min = PIOUT_MIN_SPDLOOP;
    LoopCtrl.ClosedLoopCtrl.SpdLoop.I_Out = 0;

    LoopCtrl.OpenLoopCtrl.AlignCurr_Target = Q14(ALIGN_CURR_OPENLOOP / CURR_BASE);
    LoopCtrl.OpenLoopCtrl.AlignCurrSlope = Q14(ALIGN_CURR_SLOPE / CURR_BASE);
    LoopCtrl.OpenLoopCtrl.StartCurr = Q14(START_CURR_OPENLOOP / CURR_BASE);
    LoopCtrl.OpenLoopCtrl.IFCurr = LoopCtrl.OpenLoopCtrl.StartCurr;
    LoopCtrl.OpenLoopCtrl.IFCurr_Target = Q14(IFCURR_TARGET / CURR_BASE);
    LoopCtrl.OpenLoopCtrl.IFCurrSlope = Q14(IFCURR_SLOPE / CURR_BASE);
    LoopCtrl.OpenLoopCtrl.SwitchSpd = Q15(SPEED_SWITCH_OPENLOOP / SPEED_BASE);
    LoopCtrl.OpenLoopCtrl.OpenLoopSpdTarget = Q15(SPEED_TARGET_OPENLOOP / SPEED_BASE);
    LoopCtrl.OpenLoopCtrl.SpeedSlope = Q15(SPEED_SLOPE / SPEED_BASE);

    Svm.ShiftScale = SHIFT_SCALE;
    Svm.StableScale = STABLE_SCALE;
}

/**
 * @brief      PhaseCurr_Get function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
PHASE_CURR_DEF PhaseCurr_Get(FOC_DEF *pFoc)
{
    uint16_t Sector_Last;
    Sector_Last = Svm.Sector;
    PHASE_CURR_DEF Phase_Curr_Temp = {0, 0, 0};
    switch (Sector_Last)
    {
    case 0: /* constant-expression */
        /* code */
        pFoc->PhaseCurr.PhaseU = pFoc->Sample_Curr.Curr_SamplePoint_1st;
        pFoc->PhaseCurr.PhaseW = -pFoc->Sample_Curr.Curr_SamplePoint_2nd;
        pFoc->PhaseCurr.PhaseV = -(pFoc->PhaseCurr.PhaseU + pFoc->PhaseCurr.PhaseW);

        break;

    case 1:
        pFoc->PhaseCurr.PhaseV = pFoc->Sample_Curr.Curr_SamplePoint_1st;
        pFoc->PhaseCurr.PhaseW = -pFoc->Sample_Curr.Curr_SamplePoint_2nd;
        pFoc->PhaseCurr.PhaseU = -(pFoc->PhaseCurr.PhaseV + pFoc->PhaseCurr.PhaseW);

        break;

    case 2:
        pFoc->PhaseCurr.PhaseV = pFoc->Sample_Curr.Curr_SamplePoint_1st;
        pFoc->PhaseCurr.PhaseU = -pFoc->Sample_Curr.Curr_SamplePoint_2nd;
        pFoc->PhaseCurr.PhaseW = -(pFoc->PhaseCurr.PhaseV + pFoc->PhaseCurr.PhaseU);

        break;

    case 3:
        pFoc->PhaseCurr.PhaseW = pFoc->Sample_Curr.Curr_SamplePoint_1st;
        pFoc->PhaseCurr.PhaseU = -pFoc->Sample_Curr.Curr_SamplePoint_2nd;
        pFoc->PhaseCurr.PhaseV = -(pFoc->PhaseCurr.PhaseW + pFoc->PhaseCurr.PhaseU);

        break;

    case 4:
        pFoc->PhaseCurr.PhaseW = pFoc->Sample_Curr.Curr_SamplePoint_1st;
        pFoc->PhaseCurr.PhaseV = -pFoc->Sample_Curr.Curr_SamplePoint_2nd;
        pFoc->PhaseCurr.PhaseU = -(pFoc->PhaseCurr.PhaseW + pFoc->PhaseCurr.PhaseV);

        break;

    default:
        pFoc->PhaseCurr.PhaseU = pFoc->Sample_Curr.Curr_SamplePoint_1st;
        pFoc->PhaseCurr.PhaseV = -pFoc->Sample_Curr.Curr_SamplePoint_2nd;
        pFoc->PhaseCurr.PhaseW = -(pFoc->PhaseCurr.PhaseU + pFoc->PhaseCurr.PhaseV);
        break;
    }

    Phase_Curr_Temp = pFoc->PhaseCurr;
    return Phase_Curr_Temp;
}

/**
 * @brief      ClarkeTransform function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
inline AXIS_DEF ClarkeTransform(PHASE_CURR_DEF *pPhaseCurr)
{
    AXIS_DEF StatCurr = {0, 0};

    StatCurr.Real = (int16_t)pPhaseCurr->PhaseU;
    StatCurr.Imag = (pPhaseCurr->PhaseV - pPhaseCurr->PhaseW) * SQRT1_3 >> SHIFT_15BITS;

    return StatCurr;
}

/**
 * @brief      ParkTransform function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
inline AXIS_DEF ParkTransform(AXIS_DEF *pAxis, uint16_t ElecAngle)
{
    AXIS_DEF RotaCurr = {0, 0};
    int32_t Cos;
    int32_t Sin;
    uint32_t Angle_Temp;

    Angle_Temp = ElecAngle >> 6u;

    Cos = pTable_Cos[Angle_Temp];
    Sin = Table_Sin[Angle_Temp];

    RotaCurr.Real = Data_Limit((pAxis->Real * Cos + pAxis->Imag * Sin) >> SHIFT_15BITS, BIT_MAX);
    RotaCurr.Imag = Data_Limit((pAxis->Imag * Cos - pAxis->Real * Sin) >> SHIFT_15BITS, BIT_MAX);

    return RotaCurr;
}

/**
 * @brief      iParkTransform function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
inline AXIS_DEF iParkTransform(AXIS_DEF *pAxis, uint16_t ElecAngle)
{
    AXIS_DEF StatVolt = {0, 0};
    int32_t Cos;
    int32_t Sin;
    uint32_t Angle_Temp;

    Angle_Temp = ElecAngle >> 6u;

    Cos = pTable_Cos[Angle_Temp];
    Sin = Table_Sin[Angle_Temp];

    StatVolt.Real = Data_Limit((DataMult_Q15(pAxis->Real, Cos)) - (DataMult_Q15(pAxis->Imag, Sin)), BIT_MAX);
    StatVolt.Imag = Data_Limit((DataMult_Q15(pAxis->Real, Sin)) + (DataMult_Q15(pAxis->Imag, Cos)), BIT_MAX);

    return StatVolt;
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

    AngleSlope_Temp = (pOpenLoop->AngleSlope * 10430) >> 15u; // anglepu:32767 = PI*10430,65535 = 2PI*10430
    pOpenLoop->OpenLoopAngle += AngleSlope_Temp;
    Angle_Temp = pOpenLoop->OpenLoopAngle;
    return Angle_Temp;
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

/**
 * @brief      EstFlux_Ctr function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
inline void EstFlux_Ctr(void)
{
    int16_t Temp;
    uint16_t Temp1;
    uint16_t FluxAbsValue;
    AXIS_DEF FluxSum_Axis = {0, 0};
    AXIS_DEF Flux;
    AXIS_DEF Flux_Corr; // Corrective item

    Temp = Data_Limit(Flux_Corr.Real + Foc.StatVolt.Real - (DataMult_Q15(Foc.StatCurr.Real, Foc.PhaseRes_Pu)), BIT_MAX);
    FluxSum_Axis.Real = LPF_Ctr(&Foc.RealFluxLPF, Temp);
    Flux.Real = Data_Limit(FluxSum_Axis.Real - (DataMult_Q15(Foc.StatCurr.Real, Foc.PhaseInd_Pu)), BIT_MAX);

    Temp = Data_Limit(Flux_Corr.Imag + Foc.StatVolt.Imag - (DataMult_Q15(Foc.StatCurr.Imag, Foc.PhaseRes_Pu)), BIT_MAX);
    FluxSum_Axis.Imag = LPF_Ctr(&Foc.ImagFluxLPF, Temp);
    Flux.Imag = Data_Limit(FluxSum_Axis.Imag - (DataMult_Q15(Foc.StatCurr.Imag, Foc.PhaseInd_Pu)), BIT_MAX);

    Foc.FluxAngle = AngleAmp_Get(Flux, &Temp1);
    FluxAbsValue = Data_Limit(DataMult_Q15(Temp1, 32000), (BIT_MAX + 1));
    Temp = LPF_Ctr(&Foc.FluxAmpLPF, FluxAbsValue);

    if (Flux.Real > Temp)
    {
        Flux_Corr.Real -= 400;
    }
    else
    {
        if (Flux.Real < -Temp)
        {
            Flux_Corr.Real += 400;
        }
        else
        {
            Flux_Corr.Real = 0;
        }
    }
    if (Flux.Imag > Temp)
    {
        Flux_Corr.Imag -= 400;
    }
    else
    {
        if (Flux.Imag < -Temp)
        {
            Flux_Corr.Imag += 400;
        }
        else
        {
            Flux_Corr.Imag = 0;
        }
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
inline void EstSmo_Ctr(void)
{
    int16_t temp1, temp2, temp3, temp4;
    int32_t error;
    int32_t Cos;
    int32_t Sin;
    uint32_t Angle_Temp;

    temp1 = Foc.Smo_Ctrl.LastCurrEst_Real;
    temp2 = ((Foc.StatVolt.Real * Foc.Smo_Ctrl.Factor1) - (temp1 * Foc.Smo_Ctrl.Factor2) - (Foc.Smo_Ctrl.EmfEst_Real * Foc.Smo_Ctrl.Factor1)) >> SHIFT_15BITS;
    temp2 = temp2 + temp1;
    Foc.Smo_Ctrl.LastCurrEst_Real = temp2;
    temp2 = temp2 - Foc.StatCurr.Real;

    if (temp2 > Foc.Smo_Ctrl.SmoErrWidth)
    {
        temp2 = Foc.Smo_Ctrl.SmoGain;
    }
    else
    {
        if (temp2 < -Foc.Smo_Ctrl.SmoErrWidth)
        {
            temp2 = -Foc.Smo_Ctrl.SmoGain;
        }
        else
        {
            temp2 = (temp2 * Foc.Smo_Ctrl.SmoSlope);
        }
    }
    Foc.Smo_Ctrl.EmfEst_Real = temp2;
    temp2 = LPF_Ctr(&Foc.Lpf_EmfEstReal, temp2);
    Foc.Smo_Ctrl.EmfEstLpf_Real = temp2;
    temp3 = -temp2;

    temp1 = Foc.Smo_Ctrl.LastCurrEst_Imag;
    temp2 = ((Foc.StatVolt.Imag * Foc.Smo_Ctrl.Factor1) - (temp1 * Foc.Smo_Ctrl.Factor2) - (Foc.Smo_Ctrl.EmfEst_Imag * Foc.Smo_Ctrl.Factor1)) >> SHIFT_15BITS;
    temp2 = temp2 + temp1;
    Foc.Smo_Ctrl.LastCurrEst_Imag = temp2;
    temp2 = temp2 - Foc.StatCurr.Imag;

    if (temp2 > Foc.Smo_Ctrl.SmoErrWidth)
    {
        temp2 = Foc.Smo_Ctrl.SmoGain;
    }
    else
    {
        if (temp2 < -Foc.Smo_Ctrl.SmoErrWidth)
        {
            temp2 = -Foc.Smo_Ctrl.SmoGain;
        }
        else
        {
            temp2 = (temp2 * Foc.Smo_Ctrl.SmoSlope);
        }
    }
    Foc.Smo_Ctrl.EmfEst_Imag = temp2;
    temp2 = LPF_Ctr(&Foc.Lpf_EmfEstImag, temp2);
    Foc.Smo_Ctrl.EmfEstLpf_Imag = temp2;
    temp4 = temp2;

    Angle_Temp = Foc.AnglePLL >> 6u;

    Cos = pTable_Cos[Angle_Temp];
    Sin = Table_Sin[Angle_Temp];
    error = (temp3 * Cos - temp4 * Sin) >> SHIFT_15BITS;
    Foc.SpeedEst = PID_Ctr(&LoopCtrl.ClosedLoopCtrl.PLLLoop, error);
    Foc.AnglePLL += (Foc.SpeedEst * Foc.Ts) >> 14u;
}
