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
	uint32_t CompAngle_Temp;

    temp1 = Foc.Smo_Ctrl.LastCurrEst_Real;
    temp2 = ((Foc.StatVolt.Real * Foc.Smo_Ctrl.Factor1) >> 13u) - ((Foc.Smo_Ctrl.EmfEst_Real * Foc.Smo_Ctrl.Factor1) >> 13u);
    temp2 = temp2 + (temp1 - ((temp1 * Foc.Smo_Ctrl.Factor2) >> 13u));
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
    temp2 = ((Foc.StatVolt.Imag * Foc.Smo_Ctrl.Factor1) >> 13u) - ((Foc.Smo_Ctrl.EmfEst_Imag * Foc.Smo_Ctrl.Factor1) >> 13u);
    temp2 = temp2 + (temp1 - ((temp1 * Foc.Smo_Ctrl.Factor2) >> 13u));
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
	Foc.SpeedEstLpf = LPF_Ctr(&Foc.Lpf_SpeedEst,Foc.SpeedEst);
    Angle_Temp = (Foc.SpeedEst * Foc.Ts) >> 15u;
    Foc.AngleEst += (10430 * Angle_Temp) >> 14u;
//	CompAngle_Temp = 10 * Angle_Temp;
//	Foc.AngleEst = Foc.AngleEst + ((10430 * CompAngle_Temp) >> 14u);
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
    Ed = RotaVolt.Real - ((Foc.PhaseRes * RotaCurr.Real) >> 14u) + ((Foc.SpeedEst * Foc.PhaseInd * RotaCurr.Imag) >> 28u);
    Eq = RotaVolt.Imag - ((Foc.PhaseRes * RotaCurr.Imag) >> 14u) - ((Foc.SpeedEst * Foc.PhaseInd * RotaCurr.Real) >> 28u);

    Temp = SIGN(Foc.SpeedEst, (-1), (1));
    Temp = ((Eq - Temp * Ed) << 14u) / Foc.Flux;
    Temp = (Temp - Foc.SpeedEst) * Foc.SvcmGain >> 15u;
    Foc.SpeedEst += (Temp * Foc.Ts) >> 15u;
    Foc.SpeedEst = SATURATE(Foc.SpeedEst, -19661, 19661);
	Foc.SpeedEstLpf = LPF_Ctr(&Foc.Lpf_SpeedEst,Foc.SpeedEst);
    Angle_temp = Foc.SpeedEst * Foc.Ts >> 15u;
    Foc.AngleEst += (10430 * Angle_temp) >> 14u;
	
//	Foc.RotaVolt_Old = RotaVolt;
//	Foc.RotaCurr_Old = RotaCurr;
	//(void)RotaCurr;
}

/**
 * @brief      EstPLL_Ctr function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void EstPLL_Ctr(void)
{
	int16_t Temp;
	uint16_t Angle_Temp;
	int16_t Temp1;
	AXIS_DEF RotaVolt_Last = {0, 0};
    AXIS_DEF RotaCurr_Last = {0, 0};
	
	Temp1 = Foc.SpeedEst;
	Temp = RotaCurr_Last.Imag * Foc.PhaseInd * Temp1 >> 28u;
	Temp = Temp + RotaVolt_Last.Real - (RotaCurr_Last.Real * Foc.PhaseRes >> 14u);
	
	if(Temp1 <= OMEGA0)
	{
		Temp1 = OMEGA0;
	}
	else
	{
		Temp1 = Foc.SpeedEst;
	}
	
	Temp1 = (1 << 28u) / (Temp1 * Foc.Flux >> 14u);
	Angle_Temp = (uint16_t)(-(Temp * Temp1 >> 12u));
	
	if(Angle_Temp > 32767)
	{
		Temp = 32767 - Angle_Temp;
	}
	else
	{
		Temp = Angle_Temp;
	}
	
	LoopCtrl.ClosedLoopCtrl.PLLLoop.Error = Temp;
	Foc.SpeedEst = PID_Ctr(&LoopCtrl.ClosedLoopCtrl.PLLLoop, LoopCtrl.ClosedLoopCtrl.PLLLoop.Error);
    Angle_Temp = (Foc.SpeedEst * Foc.Ts) >> 15u;
    Foc.AngleEst += (10430 * Angle_Temp) >> 14u;
	
	RotaVolt_Last.Real = Foc.RotaVolt.Real;
	RotaCurr_Last.Real = Foc.RotaCurr.Real;
	RotaCurr_Last.Imag = Foc.RotaCurr.Imag;
}