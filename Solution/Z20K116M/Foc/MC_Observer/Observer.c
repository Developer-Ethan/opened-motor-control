#include "HeadFile.h"

/**
 * @brief      EstFlux_Ctr function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void EstSmo_Ctr(void)
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

    Angle_Temp = Foc.AngleEst >> 6u;

    Cos = pTable_Cos[Angle_Temp];
    Sin = Table_Sin[Angle_Temp];
    LoopCtrl.ClosedLoopCtrl.PLLLoop.Error = (temp3 * Cos - temp4 * Sin) >> SHIFT_15BITS;
    Foc.SpeedEst = PID_Ctr(&LoopCtrl.ClosedLoopCtrl.PLLLoop, LoopCtrl.ClosedLoopCtrl.PLLLoop.Error);
    Angle_Temp = (Foc.SpeedEst * Foc.Ts) >> 15u;
    Foc.AngleEst += (10430 * Angle_Temp) >> 14u;
}

/**
 * @brief      EstFlux_Ctr function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void EstSVCM_Ctr(void)
{
    uint16_t Angle_temp;
    int16_t Ed, Eq;
    int16_t Temp;
    AXIS_DEF RotaVolt = {0, 0};
    AXIS_DEF RotaCurr = {0, 0};

    RotaVolt = ParkTransform(&Foc.StatVolt, Foc.AngleEst);
    RotaCurr = ParkTransform(&Foc.StatCurr, Foc.AngleEst);
    Ed = RotaVolt.Real - ((Foc.PhaseRes * Foc.RotaCurr.Real) >> 14u) + ((Foc.SpeedEst * Foc.PhaseInd * Foc.RotaCurr.Imag) >> 28u);
    Eq = RotaVolt.Imag - ((Foc.PhaseRes * Foc.RotaCurr.Imag) >> 14u) - ((Foc.SpeedEst * Foc.PhaseInd * Foc.RotaCurr.Real) >> 28u);

    Temp = SIGN(Foc.SpeedEst, (-1), (1));
    Temp = ((Eq - Temp * Ed) << 14u) / Foc.Flux;
    Temp = (Temp - Foc.SpeedEst) * Foc.SvcmGain >> 15u;
    Foc.SpeedEst += (Temp * Foc.Ts) >> 15u;
    Foc.SpeedEst = SATURATE(Foc.SpeedEst, -19661, 19661);
    Angle_temp = Foc.SpeedEst * Foc.Ts >> 15u;
    Foc.AngleEst += (10430 * Angle_temp) >> 14u;
	
	(void)RotaCurr;
}
