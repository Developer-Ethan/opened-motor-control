#include "HeadFile.h"

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
    int32_t Cos;
    int32_t Sin;
    uint32_t Angle_Temp;

    temp1 = Foc.Smo_Ctrl.LastCurrEst_Real;
    temp2 = ((Foc.StatVolt.Real * Foc.Smo_Ctrl.Factor1) - (Foc.Smo_Ctrl.EmfEst_Real * Foc.Smo_Ctrl.Factor1)) >> 15u;
    temp2 = temp2 + (temp1 - ((temp1 * Foc.Smo_Ctrl.Factor2) >> 15u));
    temp2 = SATURATE(temp2, -16384, 16384);
    Foc.Smo_Ctrl.LastCurrEst_Real = temp2;
    temp2 = temp2 - Foc.StatCurr.Real;
    temp2 = SATURATE(temp2, -Foc.Smo_Ctrl.SmoErrWidth, Foc.Smo_Ctrl.SmoErrWidth);
    temp2 = (temp2 * Foc.Smo_Ctrl.SmoSlope);
    Foc.Smo_Ctrl.EmfEst_Real = temp2;
    temp2 = LPF_Ctr(&Foc.Lpf_EmfEstReal, temp2);
    Foc.Smo_Ctrl.EmfEstLpf_Real = temp2;
    temp3 = -temp2;

    temp1 = Foc.Smo_Ctrl.LastCurrEst_Imag;
    temp2 = ((Foc.StatVolt.Imag * Foc.Smo_Ctrl.Factor1) - (Foc.Smo_Ctrl.EmfEst_Imag * Foc.Smo_Ctrl.Factor1)) >> 15u;
    temp2 = temp2 + (temp1 - ((temp1 * Foc.Smo_Ctrl.Factor2) >> 15u));
    temp2 = SATURATE(temp2, -16384, 16384);
    Foc.Smo_Ctrl.LastCurrEst_Imag = temp2;
    temp2 = temp2 - Foc.StatCurr.Imag;
    temp2 = SATURATE(temp2, -Foc.Smo_Ctrl.SmoErrWidth, Foc.Smo_Ctrl.SmoErrWidth);
    temp2 = (temp2 * Foc.Smo_Ctrl.SmoSlope);
    Foc.Smo_Ctrl.EmfEst_Imag = temp2;
    temp2 = LPF_Ctr(&Foc.Lpf_EmfEstImag, temp2);
    Foc.Smo_Ctrl.EmfEstLpf_Imag = temp2;
    temp4 = temp2;

    Angle_Temp = Foc.AnglePLL >> 6u;

    Cos = pTable_Cos[Angle_Temp];
    Sin = Table_Sin[Angle_Temp];
    LoopCtrl.ClosedLoopCtrl.PLLLoop.Error = (temp3 * Cos - temp4 * Sin) >> SHIFT_15BITS;
    Foc.SpeedEst = PID_Ctr(&LoopCtrl.ClosedLoopCtrl.PLLLoop, LoopCtrl.ClosedLoopCtrl.PLLLoop.Error);
    Angle_Temp = (Foc.SpeedEst * Foc.Ts) >> 15u;
    Foc.AnglePLL += (10430 * Angle_Temp) >> 14u;
}

/**
 * @brief      EstFlux_Ctr function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
inline void EstSVCM_Ctr(void)
{
    uint16_t Angle_temp;
    int16_t Ed, Eq;
    int16_t Temp;
    AXIS_DEF RotaVolt = {0, 0};
    AXIS_DEF RotaCurr = {0, 0};

    RotaVolt = ParkTransform(&Foc.StatVolt, Foc.AngleEst);
    RotaCurr = ParkTransform(&Foc.StatCurr, Foc.AngleEst);
    Ed = RotaVolt.Real - ((Foc.PhaseRes * Foc.RotaCurr.Real) >> 15u) + ((Foc.SpeedEst * Foc.PhaseInd * Foc.RotaCurr.Imag) >> 29u);
    Eq = RotaVolt.Imag - ((Foc.PhaseRes * Foc.RotaCurr.Imag) >> 15u) - ((Foc.SpeedEst * Foc.PhaseInd * Foc.RotaCurr.Real) >> 29u);

    Temp = SIGN(Foc.SpeedEst, (-1), (1));
    Temp = ((Eq - Temp * Ed) << 14u) / Foc.Flux;
    Temp = (Temp - Foc.SpeedEst) * Foc.SvcmGain >> 15u;
    Foc.SpeedEst += (Temp * Foc.Ts) >> 15u;
    Foc.SpeedEst = SATURATE(Foc.SpeedEst, -19661, 19661);
    Angle_temp = Foc.SpeedEst * Foc.Ts >> 15u;
    Foc.AngleEst += (10430 * Angle_temp) >> 14u;
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
