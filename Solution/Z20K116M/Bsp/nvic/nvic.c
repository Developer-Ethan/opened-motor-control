#include "AppHeadFile.h"

/**
 * @brief      NVIC config function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void Hal_SetupNvic(void)
{
    /* Enable STIM & TIM2 NVIC IRQ*/
    NVIC_SetPriority(HAL_SPEEDLOOPIRQ_ID, 3);
	NVIC_SetPriority(TDG0_IRQn, 2);
    NVIC_SetPriority(ADC0_IRQn, 1);
    NVIC_SetPriority(HAL_FAULTINIRQ_ID, 0);
    NVIC_SetPriority(TIM2_IRQn, 4);

    NVIC_EnableIRQ(ADC0_IRQn);
	NVIC_EnableIRQ(TDG0_IRQn);
    NVIC_EnableIRQ(HAL_SPEEDLOOPIRQ_ID);
    NVIC_EnableIRQ(HAL_FAULTINIRQ_ID);
    NVIC_EnableIRQ(TIM2_IRQn);
}

/**
 * @brief      Interrupt config function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void Hal_SetupInterrupts(isr_cb_t *PwmFaultIntCbf, isr_cb_t *StimIntCbf)
{
    /* Install interrupt callback function */
    TIM_InstallCallBackFunc(FAULT_TIM_ID, TIM_INT_FAULT, PwmFaultIntCbf);
    STIM_InstallCallBackFunc(STIM_ID, STIM_INT, StimIntCbf);

    // Enalbe Fault-in int  fault1 input
    TIM_IntMask(FAULT_TIM_ID, TIM_INT_FAULT, UNMASK);
    // Enable the TIM0 int
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_0, DISABLE);
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_1, DISABLE);
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_2, DISABLE);
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_3, DISABLE);
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_4, DISABLE);
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_5, DISABLE);
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_6, DISABLE);
    TIM_DMACtrl(TIM0_ID, TIM_CHANNEL_7, DISABLE);

    /*start TIM PWM*/
    TIM_StartCounter(PWM_TIM_ID, TIM_CLK_SOURCE_SYSTEM, TIM_CLK_DIVIDE_1); // was TIM_CLK_SOURCE_SYSTEM
    /*start TIM1 FAULT channel*/
    // TIM_StartCounter(FAULT_TIM_ID, TIM_CLK_SOURCE_SYSTEM, TIM_CLK_DIVIDE_1);
	//Hal_PwmOutputEn();
    STIM_Enable(STIM_0);
    // Enable STIM_0 interrupt
    STIM_IntCmd(STIM_0, ENABLE);
}