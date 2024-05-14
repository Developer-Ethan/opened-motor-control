/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 *\*\file n32g430_it.c
 *\*\author Nations
 *\*\version v1.0.0
 *\*\copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 **/

#include "n32g430.h"
#include "n32g430_it.h"
#include "HeadFile.h"
__IO uint16_t injected_adc_volt[3];
__IO uint8_t channel_u = 0, channel_v = 0, channel_w = 0;

extern void TimingDelay_Decrement(void);
uint16_t VoltValue_ADCReg;
int16_t SampleCurr_1st, SampleCurr_2nd;
/** Cortex-M4 Processor Exceptions Handlers **/

/**
 *\*\name    NMI_Handler.
 *\*\fun     This function handles NMI exception.
 *\*\param   none
 *\*\return  none
 **/
void NMI_Handler(void)
{
}

/**
 *\*\name    HardFault_Handler.
 *\*\fun     This function handles Hard Fault exception.
 *\*\param   none
 *\*\return  none
 **/
void HardFault_Handler(void)
{
	/* Go to infinite loop when Hard Fault exception occurs */
	while (1)
	{
	}
}

/**
 *\*\name    MemManage_Handler.
 *\*\fun     This function handles Memory Manage exception.
 *\*\param   none
 *\*\return  none
 **/
void MemManage_Handler(void)
{
	/* Go to infinite loop when Memory Manage exception occurs */
	while (1)
	{
	}
}

/**
 *\*\name    BusFault_Handler.
 *\*\fun     This function handles Bus Fault exception.
 *\*\param   none
 *\*\return  none
 **/
void BusFault_Handler(void)
{
	/* Go to infinite loop when Bus Fault exception occurs */
	while (1)
	{
	}
}

/**
 *\*\name    UsageFault_Handler.
 *\*\fun     This function handles Usage Fault exception.
 *\*\param   none
 *\*\return  none
 **/
void UsageFault_Handler(void)
{
	/* Go to infinite loop when Usage Fault exception occurs */
	while (1)
	{
	}
}

/**
 *\*\name    SVC_Handler.
 *\*\fun     This function handles SVCall exception.
 *\*\param   none
 *\*\return  none
 **/
void SVC_Handler(void)
{
}

/**
 *\*\name    DebugMon_Handler.
 *\*\fun     This function handles Debug Monitor exception.
 *\*\param   none
 *\*\return  none
 **/
void DebugMon_Handler(void)
{
}

/**
 *\*\name    SysTick_Handler.
 *\*\fun     This function handles SysTick Handler.
 *\*\param   none
 *\*\return  none
 **/
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}

/*************************************************************
 * 定时器1 刹车中断 比较器过流导致
 *************************************************************/
void TIM1_BRK_IRQHandler(void)
{
	if (TIM_Interrupt_Status_Get(TIM1, TIM_STS_BITF) != RESET)
	{
		TIM_Interrupt_Disable(TIM1, TIM_INT_BREAK); /* 关闭中断 */
		TIM_Interrupt_Status_Clear(TIM1, TIM_STS_BITF);
	}
}
/*************************************************************
 * 定时器1
 *************************************************************/
uint32_t *POD;
void TIM1_UP_IRQHandler(void)
{
	if (TIM_Flag_Status_Get(TIM1, TIM_FLAG_UPDATE))
	{
		// GPIO_Pin_Toggle(GPIOB,GPIO_PIN_3);
		//		POD = (uint32_t*)(0x40023814);
		//		*POD = *POD ^ (1<<3);
		/* Clear TIM1 COM pending bit */
		TIM_Interrupt_Status_Clear(TIM1, TIM_FLAG_UPDATE);
	}
}
/*************************************************************
 * 定时器1 CC4比较中断，在最高值-20处触发
 *************************************************************/
void TIM1_CC_IRQHandler(void)
{
	if (TIM_Flag_Status_Get(TIM1, TIM_FLAG_CC4))
	{
		// GPIO_Pin_Toggle(GPIOB,GPIO_PIN_3);
		/* Clear TIM1 COM pending bit */
		TIM_Interrupt_Status_Clear(TIM1, TIM_FLAG_CC4);
	}
}

/*************************************************************
 * 定时器2的更新中断，频率和TIM1同步，即可以处理TIM的中断事务
 *************************************************************/
void TIM2_IRQHandler(void)
{
	if (TIM_Flag_Status_Get(TIM2, TIM_FLAG_UPDATE))
	{
		/* Clear TIM1 COM pending bit */
		TIM_Interrupt_Status_Clear(TIM2, TIM_FLAG_UPDATE);
	}
}

/*************************************************************
 * 定时器4  计数器定时器中断
 *************************************************************/
void TIM4_IRQHandler(void)
{
	if (TIM_Interrupt_Status_Get(TIM4, TIM_INT_UPDATE) != RESET)
	{
		TIM_Interrupt_Status_Clear(TIM4, TIM_INT_UPDATE);
	}
}

/*************************************************************
 * 定时器6  1Khz中断，测试时规则组ADC放在该中断内触发
 *************************************************************/
void TIM6_IRQHandler(void)
{
	//	static uint8_t time_100ms = 0; // 100ms计时
	if (TIM_Interrupt_Status_Get(TIM6, TIM_INT_UPDATE) != RESET)
	{
		TIM_Interrupt_Status_Clear(TIM6, TIM_INT_UPDATE);
		TimerTick_State(&Timer_State);

		SpdLoop_Control(&MotorCtrl, &LoopCtrl);
	}
}

/*************************************************************
 * ADC中断，注入组采集的数据
 *************************************************************/
void ADC_IRQHandler(void)
{
	GPIO_Pins_Set(GPIOB, GPIO_PIN_3);
	uint8_t Jlen_JSEQ = ((ADC->JSEQ & ADC_JSEQ_JLEN) >> 20);
	uint8_t Num_JSEQ = 1 + Jlen_JSEQ;
	uint8_t Channel_First = 4 - Jlen_JSEQ;
	uint8_t Channel_JSEQ;
	PHASE_CURR_DEF Phase_Curr_Temp;
//	if (ADC_INTFlag_Status_Get(ADC_INT_FLAG_JENDCA) == SET)
//	{
//		GPIO_Pin_Toggle(GPIOB, GPIO_PIN_3);
//		ADC_INTFlag_Status_Clear(ADC_INT_FLAG_JENDCA);
//	}
	if (ADC_INTFlag_Status_Get(ADC_INT_FLAG_JENDC) == SET)
	{
		//GPIO_Pin_Toggle(GPIOB, GPIO_PIN_3);

		VoltValue_ADCReg = ADC_Regular_Group_Conversion_Data_Get();
		Foc.Sample_Volt = Q14((VoltValue_ADCReg << 3) * COEFF_VOLT);

		for (Channel_JSEQ = Channel_First; Channel_JSEQ < Channel_First + Num_JSEQ; Channel_JSEQ++)
		{
			Sample_Curr.SampleCurr[Channel_JSEQ] = ADC_Injected_Group_Conversion_Data_Get(ADC_INJECTED_DATA_REG_1 + 4 * (Channel_JSEQ - Channel_First));
		}

		SampleCurr_1st = (int16_t)Sample_Curr.SampleCurr[Channel_First];
		SampleCurr_2nd = (int16_t)Sample_Curr.SampleCurr[Channel_First + 1];

		if (MotorCtrl.OffsetFlag)
		{
			BiasDetect(&Sample_Curr);
		}
		else
		{
			SampleCurr_1st -= Sample_Curr.Offset_1st;
			SampleCurr_2nd -= Sample_Curr.Offset_2nd;
			Sample_Curr.Curr_SamplePoint_1st = Q14((SampleCurr_1st << 3) * COEFF_CURR);
			Sample_Curr.Curr_SamplePoint_2nd = Q14((SampleCurr_2nd << 3) * COEFF_CURR);
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
				break;
			case MotorClosedLoop:
				Foc.Angle = Foc.AnglePLL;
				break;
			}
			Phase_Curr_Temp = PhaseCurr_Get(&Sample_Curr);
			Foc.StatCurr = ClarkeTransform(&Phase_Curr_Temp);
			Foc.RotaCurr = ParkTransform(&Foc.StatCurr, Foc.Angle);
			Foc.IdRef = LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D.InputRef;
			Foc.IqRef = LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q.InputRef;
			Foc.RotaVolt.Imag = PID_Ctr(&LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_Q, Foc.IqRef - Foc.RotaCurr.Imag);
			Foc.RotaVolt.Real = PID_Ctr(&LoopCtrl.ClosedLoopCtrl.CurrLoop.Pi_D, Foc.IdRef - Foc.RotaCurr.Real);
			// LimitedCircle_Voltage(&Foc.RotaVolt);

			Foc.StatVolt = iParkTransform(&Foc.RotaVolt, Foc.Angle);
			EstSmo_Ctr();
			Svm_Ctr(&Svm, &Foc.StatVolt);
			switch_pwm(INV_ALL_ON);
		}
		else
		{
			switch_pwm(INV_ALL_OFF);
		}

		ADC_INTFlag_Status_Clear(ADC_INT_FLAG_JENDC);
		GPIO_Pins_Reset(GPIOB, GPIO_PIN_3);
	}
	else
	{
		if (ADC_INTFlag_Status_Get(ADC_INT_FLAG_AWDG) == SET)
			ADC_INTFlag_Status_Clear(ADC_INT_FLAG_AWDG);
	}
}

/** N32G430 Peripherals Interrupt Handlers, interrupt handler's name please refer to the startup file (startup_n32g430.s) **/
