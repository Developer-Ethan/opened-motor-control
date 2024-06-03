#include "AppHeadFile.h"

void Get_TimerCv(void);
void Duty_Limit(void);
/**
 * @brief      Currentloop function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void Get_TimerCv(void)
{
    PwmCv.CCV0 = Svm.ComparePoint_1st_Up;
    PwmCv.CCV1 = Svm.ComparePoint_1st_Down;
    PwmCv.CCV2 = Svm.ComparePoint_2nd_Up;
    PwmCv.CCV3 = Svm.ComparePoint_2nd_Down;
    PwmCv.CCV4 = Svm.ComparePoint_3th_Up;
    PwmCv.CCV5 = Svm.ComparePoint_3th_Down;
}
/**
 * @brief      Faultin brake function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void Duty_Limit(void)
{
	Svm.ComparePoint_1st_Down = SATURATE(Svm.ComparePoint_1st_Down,Svm.ComparePoint_1st_Up + MOD_LIMIT_DOWN,Svm.ComparePoint_1st_Up + MOD_LIMIT_UP);
	Svm.ComparePoint_2nd_Down = SATURATE(Svm.ComparePoint_2nd_Down,Svm.ComparePoint_2nd_Up + MOD_LIMIT_DOWN,Svm.ComparePoint_2nd_Up + MOD_LIMIT_UP);
	Svm.ComparePoint_3th_Down = SATURATE(Svm.ComparePoint_3th_Down,Svm.ComparePoint_3th_Up + MOD_LIMIT_DOWN,Svm.ComparePoint_3th_Up + MOD_LIMIT_UP);
}
/**
 * @brief      Currentloop function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void Pmsm_IRQHandleCurrentLoopIsr(void)
{
	//GPIO_WritePinOutput(PORT_C,GPIO_8,GPIO_HIGH);
    uint16_t i = 0;
    uint32_t Read_Fcount;
    int16_t VoltBusRealtime;
    PHASE_CURR_DEF Phase_Curr_Temp;
    adc_reg_t *ADCx = (adc_reg_t *)(ADC0_BASE_ADDR);

    Read_Fcount = ADCx->ADC_FCTRL.FCOUNT;

    if ((VALUE_WM + 1u) == Read_Fcount)
    {
        for (i = 0; i < (VALUE_WM + 1); i++)
        {
            IRQn_AdcMapData[i] = ADCx->ADC_DATA_RD.ADC_DATA_RD;
        }
    }
    GetAdcData();
    VoltBusRealtime = IRQn_AdcMapDataVal[0];
    SampleCurr_1st = IRQn_AdcMapDataVal[1];
    SampleCurr_2nd = IRQn_AdcMapDataVal[2];

    Foc.Sample_Volt = DataMult_Q15((VoltBusRealtime << 4),COEFF_VOLT);
	
	if (MotorCtrl.OffsetFlag == 0)
    {
        SampleCurr_1st -= Sample_Curr.Offset_1st;
        SampleCurr_2nd -= Sample_Curr.Offset_2nd;
        Sample_Curr.Curr_SamplePoint_1st = DataMult_Q15((SampleCurr_1st << 4),COEFF_CURR);
        Sample_Curr.Curr_SamplePoint_2nd = DataMult_Q15((SampleCurr_2nd << 4),COEFF_CURR);
    }
    if ((MotorCtrl.CalibrateOverFlag == 1) && (MotorCtrl.StartFlag == 1))
    {
        switch (MotorCtrl.State)
        {
        case MotorAlign:
            Foc.Angle = Foc.Angle_Align;
            break;
        case MotorOpenLoop:
            Foc.AngleOpen = Angle_Given(&LoopCtrl.OpenLoopCtrl);
            Foc.Angle = Foc.AngleOpen;
			Foc.SpeedRealtime = LoopCtrl.OpenLoopCtrl.OpenLoopSpd;
            break;
        case MotorClosedLoop:
            Foc.Angle = Foc.AngleEst;
			Foc.SpeedRealtime = Foc.SpeedEst;
            break;
        }
        Phase_Curr_Temp = PhaseCurr_Get(&Sample_Curr);
        Foc.StatCurr = ClarkeTransform(&Phase_Curr_Temp);
        Foc.RotaCurr = ParkTransform(&Foc.StatCurr, Foc.Angle);
        Foc.IdRef = LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.InputRef;
        Foc.IqRef = LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.InputRef;
        Foc.RotaVolt.Imag = PID_Ctr(&LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q, (Foc.IqRef - Foc.RotaCurr.Imag));
        Foc.RotaVolt.Real = PID_Ctr(&LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D, (Foc.IdRef - Foc.RotaCurr.Real));
//		Foc.RotaVolt.Imag = 19661;
//		Foc.RotaVolt.Real = 0;
		Foc.AngleUComp = Foc.Angle;
		Foc.Angle += (10430 * (Foc.SpeedRealtime * Foc.Ts >> 14) >> 14u);
        Foc.StatVolt = iParkTransform(&Foc.RotaVolt, Foc.Angle);
#if SMO_ENABLE
        {
            EstSmo_Ctr();
        }
#elif SVCM_ENABLE
        {
            EstSVCM_Ctr();
        }
#endif
        Svm_Ctr(&Svm, PWM_MOD / 2, &Foc.StatVolt);
		Duty_Limit();
        Get_TimerCv();
        Hal_UpdateAsymmetricOutput(&PwmCv);
        Hal_UpdateTdgDelayOut(Svm.CompareValue_SimplePoint1, Svm.CompareValue_SimplePoint2);
        Hal_PwmOutputEn();
    }
    else
    {
        Hal_PwmOutputDis();
    }
	//GPIO_ClearPinOutput(PORT_C,GPIO_8);//78us
}

/**
 * @brief      Faultin brake function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void Pmsm_IRQHandleBkinIsr(void)
{
    static Z20A8300A_SpiStatusType Result_FaultRead = Z20A8300A_ERR_OK;
    static Z20A8300A_StatusRegType Status;
    static Z20A8300A_AllDiagType Diag;

    Hal_PwmOutputDis();

    Result_FaultRead = Z20A8300A_Diag_ReadClearDiag(&Z20A8300AIf1, &Status, &Diag);
    (void)(Result_FaultRead);
}
/**
 * @brief      Speedloop function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void Pmsm_IRQHandleSpeedLoopIsr(void)
{
	SpdLoop_Control(&MotorCtrl,&LoopCtrl);
    STIM_ClearInt(STIM_0);
}

/**
 * @brief      Speedloop function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void EventHandle_1ms(void)
{
	SpdLoop_Control(&MotorCtrl,&LoopCtrl);
    STIM_ClearInt(STIM_0);
}