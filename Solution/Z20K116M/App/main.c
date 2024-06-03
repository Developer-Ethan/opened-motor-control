/**************************************************************************************************/
/**
 * @file      : pmsm.c
 * @brief     : pmsm demo main file.
 *              - Platform: Z20K11xM
 * @version   : Demo
 * @date      : 27-Feb-2023
 * @author    : Zhixin Semiconductor
 * @note      : None
 *
 * @copyright : Copyright (c) 2022-2023 Zhixin Semiconductor Ltd. All rights reserved.
 **************************************************************************************************/
#include "AppHeadFile.h"
void HW_Init(void);
void TIM_IRQRLD(void);
/**
 * @brief      Main function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void HW_Init(void)
{
    uint8_t McuFaultResult;
	
    HAL_setupClock();
    disable_all_interrupt();
    /* Z20A8300A Init */
    while (0U == Z20A8300A_Init())
    {
    }
    HAL_setupPwms();
    Hal_SetupTmu();
    HAL_setupStim();
    HAL_setupHwdiv();
    Hal_SetupNvic();
    // Init_LIN();
    McuFaultResult = Hal_SetupAdcs();
    (void)McuFaultResult;
}
/**
 * @brief      Main function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
uint16_t CCV0,CCV1,CCV2,CCV3,CCV4,CCV5;
void TIM_IRQRLD(void)
{
	CCV0 = TIM_GetCCVal(TIM0_ID,TIM_CHANNEL_0);
	CCV1 = TIM_GetCCVal(TIM0_ID,TIM_CHANNEL_1);
	CCV2 = TIM_GetCCVal(TIM0_ID,TIM_CHANNEL_2);
	CCV3 = TIM_GetCCVal(TIM0_ID,TIM_CHANNEL_3);
	CCV4 = TIM_GetCCVal(TIM0_ID,TIM_CHANNEL_4);
	CCV5 = TIM_GetCCVal(TIM0_ID,TIM_CHANNEL_5);
	if(((ABS(CCV0 - CCV2) < Svm.StableScale) && (ABS(CCV0 - CCV2) > 0))\
	|| ((ABS(CCV0 - CCV4) < Svm.StableScale) && (ABS(CCV0 - CCV4) > 0))\
	|| ((ABS(CCV2 - CCV4) < Svm.StableScale) && (ABS(CCV2 - CCV4) > 0)))
	{
		while(1);
	}
}
/**
 * @brief      Main function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void main(void)
{
    HW_Init();
	Foc_Init();
	Timer_State_Init();
    ADC_InstallCallBackFunc(ADC0_ID, ADC_FWM_INT, Pmsm_IRQHandleCurrentLoopIsr);
	TIM_InstallCallBackFunc(TIM0_ID,TIM_INT_RLD,TIM_IRQRLD);
    Hal_SetupInterrupts(Pmsm_IRQHandleBkinIsr, EventHandle_1ms);
    // Enable global interrupts
    enable_all_interrupt();

	PORT_PinmuxConfig(PORT_C,GPIO_8,PTC8_GPIO);
	GPIO_SetPinDir(PORT_C,GPIO_8,GPIO_OUTPUT);
	GPIO_ClearPinOutput(PORT_C,GPIO_8);
	
    for (;;)
    {
        MotorStateMachine(&MotorCtrl, &Timer_State);
		if (MotorCtrl.OffsetFlag)
		{
			BiasDetect(&Sample_Curr);
		}
        if ((ABS(Sample_Curr.PhaseCurr.PhaseU) > 3000) || (ABS(Sample_Curr.PhaseCurr.PhaseV) > 3000) || (ABS(Sample_Curr.PhaseCurr.PhaseW) > 3000))
        {
            //Hal_PwmOutputDis();
        }
    }
}

/** @} end of group PMSM_Public_Functions */

/** @} end of group PMSM driver modules */

/** @} end of group Z20K11XM_Foc */