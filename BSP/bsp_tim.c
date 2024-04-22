#include "bsp_tim.h"
#include "HeadFile.h"


uint8_t pwm_polarity;
uint16_t GPTIMClockFrequency = 0;
int32_t TIM_Freq_buff[3] = {0};
uint16_t TimerPeriod = 0;
/*************************************************************
 * 定时器1输出PWM配置
 *************************************************************/
void TIM1_PWM_Init(uint8_t polarity)
{
  TIM_TimeBaseInitType TIM1_TimeBaseStructure;
  OCInitType TIM1_OCInitStructure;
  TIM_BDTRInitType TIM1_BDTRInitStructure;

  TimerPeriod = (SystemClockFrequency / (PWM_FREQ * 2) / (TIMER_CLOCK_PRESCALER_SET + 1));

  TIM_Reset(TIM1);
  TIM_Base_Struct_Initialize(&TIM1_TimeBaseStructure);
  TIM1_TimeBaseStructure.Prescaler = TIMER_CLOCK_PRESCALER_SET;
  TIM1_TimeBaseStructure.CntMode = TIM_CNT_MODE_CENTER_ALIGN2; // 中心对齐计数模式下，当计数器向上计数时产生比较中断
  TIM1_TimeBaseStructure.Period = TimerPeriod;
  TIM1_TimeBaseStructure.ClkDiv = TIM_CLK_DIV4; // 4分频
  TIM1_TimeBaseStructure.RepetCnt = 0;

  TIM_Base_Initialize(TIM1, &TIM1_TimeBaseStructure);

  // Channel 1, 2,3 in PWM mode
  // TIM_InitOcStruct(&TIM1_OCInitStructure);
  TIM1_OCInitStructure.OcMode = TIM_OCMODE_PWM2; // Pos logic(ocref:when '<' is negative,when '>' is active)
  TIM1_OCInitStructure.OutputState = TIM_OUTPUT_STATE_DISABLE;
  TIM1_OCInitStructure.OutputNState = TIM_OUTPUT_NSTATE_DISABLE;
  TIM1_OCInitStructure.Pulse = (TimerPeriod >> 2);
  TIM1_OCInitStructure.OcPolarity = TIM_OC_POLARITY_HIGH;
  TIM1_OCInitStructure.OcNPolarity = TIM_OCN_POLARITY_HIGH;
  TIM1_OCInitStructure.OcIdleState = TIM_OC_IDLE_STATE_RESET;
  TIM1_OCInitStructure.OcNIdleState = TIM_OC_IDLE_STATE_RESET;

  if (polarity == SET)
  {
    pwm_polarity = SET;
    TIM1_OCInitStructure.OcPolarity = TIM_OC_POLARITY_HIGH; // high lever is active,its lever is same as the ocref
    TIM1_OCInitStructure.OcNPolarity = TIM_OCN_POLARITY_HIGH;
    TIM1_OCInitStructure.OcIdleState = TIM_OC_IDLE_STATE_RESET;
    TIM1_OCInitStructure.OcNIdleState = TIM_OC_IDLE_STATE_RESET;
  }
  else
  {
    pwm_polarity = RESET;
    TIM1_OCInitStructure.OcPolarity = TIM_OC_POLARITY_LOW;
    TIM1_OCInitStructure.OcNPolarity = TIM_OCN_POLARITY_LOW;
    TIM1_OCInitStructure.OcIdleState = TIM_OC_IDLE_STATE_SET;
    TIM1_OCInitStructure.OcNIdleState = TIM_OC_IDLE_STATE_SET;
  }
  TIM_Output_Channel1_Initialize(TIM1, &TIM1_OCInitStructure);
  TIM_Output_Channel2_Initialize(TIM1, &TIM1_OCInitStructure);
  TIM_Output_Channel3_Initialize(TIM1, &TIM1_OCInitStructure);

  TIM_Compare1_D_Set(TIM1, (TimerPeriod >> 2)); // the second compare point under Asymmetric mode
  TIM_Compare2_D_Set(TIM1, (TimerPeriod >> 2));
  TIM_Compare3_D_Set(TIM1, (TimerPeriod >> 2));

  TIM_Compare7_Set(TIM1, TimerPeriod >> 2);
  TIM_Compare8_Set(TIM1, TimerPeriod >> 1);
  // Enables the TIM1 Preload on CC1,CC2,CC3,CC4 Register
  TIM_Output_Channel1_Preload_Set(TIM1, TIM_OC_PRELOAD_ENABLE); // 使能CCDAT1寄存器的预加载功能
  TIM_Output_Channel2_Preload_Set(TIM1, TIM_OC_PRELOAD_ENABLE);
  TIM_Output_Channel3_Preload_Set(TIM1, TIM_OC_PRELOAD_ENABLE);
  TIM_Output_Channel7_Preload_Set(TIM1, TIM_OC_PRELOAD_ENABLE);
  TIM_Output_Channel8_Preload_Set(TIM1, TIM_OC_PRELOAD_ENABLE);

  TIM_OC7REF_Trigger_To_ADC_Enable(TIM1); // 通道7触发ADC使能
  TIM_OC8REF_Trigger_To_ADC_Enable(TIM1);
  TIM_Output_Trigger_Select(TIM1, TIM_TRGO_SRC_OC4_7_8_9REF);                                        // MMSEL3=1;只有当TIMx_CTRL2.MMSEL3=1时，TRGO输出才会有效
  TIM_Base_Center_Aligned_Mode_OC4_7_8_9_Trigger_Set(TIM1, TIM_UP_COUNTING_OC4_7_8_9_TRIGGER_VALID); // 向上计数，TRGO输出有效，触发ADC采样
  TIM_Asymmetric_Enable(TIM1);                                                                       // 使能中央非对称

  // Automatic Output enable, Break, dead time and lock configuration
  TIM1_BDTRInitStructure.OssrState = TIM_OSSR_STATE_ENABLE;
  TIM1_BDTRInitStructure.OssiState = TIM_OSSI_STATE_ENABLE;
  TIM1_BDTRInitStructure.LockLevel = TIM_LOCK_LEVEL_OFF;
  TIM1_BDTRInitStructure.DeadTime = 9;
  TIM1_BDTRInitStructure.Break = TIM_BREAK_IN_ENABLE;
  TIM1_BDTRInitStructure.BreakPolarity = TIM_BREAK_POLARITY_HIGH;
  TIM1_BDTRInitStructure.AutomaticOutput = TIM_AUTO_OUTPUT_DISABLE; // TIM_AUTO_OUTPUT_ENABLE;		//关闭自动输出
  TIM1_BDTRInitStructure.IomBreakEn = false;
  TIM_Break_And_Dead_Time_Set(TIM1, &TIM1_BDTRInitStructure);

  TIM_On(TIM1);
}

/**************************************************************************************************
* Description   : Set the output of inverter bridge arms
*                 for motor control run/stop, capacitance charge of bootstrap circuit, brake
* Input         : option
                    INV_ALL_ON: all inverter arms turn on
                    INV_ALL_OFF: all inverter arms turn off (inverter stop)
                    INV_MOTOR_BRAKE: all inverter down arms turn on, up arms turn off
                    INV_U_CHARGE: only U phase arm turn on        ch0
                    INV_V_CHARGE: only V phase arm turn on        ch1
                    INV_W_CHARGE: only W phase arm turn on        ch2
* Return:       : none
**************************************************************************************************/
void __attribute__((section(".RamFunc"))) switch_pwm(PWMStatus option)
{
  uint32_t reg_temp = TIM1->CCEN;
  if (pwm_polarity == RESET)
  {
    reg_temp |= (TIM_CCEN_CC1EN | TIM_CCEN_CC2EN | TIM_CCEN_CC3EN | TIM_CCEN_CC1NEN | TIM_CCEN_CC2NEN | TIM_CCEN_CC3NEN);
  }
  {
    switch (option)
    {
    case INV_ALL_OFF: /* 0x00 */
      /* turn off 6-phases (up/vp/wp, un/vn/wn) */
      /* timer_periph channels output disable */
      TIM_PWM_Output_Disable(TIM1); // 保护电平设置后关总输出就可以
      break;
    case INV_ALL_ON:
      /* turn on 6-phases (up/vp/wp, un/vn/wn) */
      /* timer_periph channels output enable */
      reg_temp |= (TIM_CCEN_CC1EN | TIM_CCEN_CC2EN | TIM_CCEN_CC3EN | TIM_CCEN_CC1NEN | TIM_CCEN_CC2NEN | TIM_CCEN_CC3NEN);
      TIM1->CCEN = reg_temp;
      TIM_Interrupt_Status_Clear(TIM1, TIM_STS_BITF); /* clear interrupt request flag */
      TIM_Interrupt_Enable(TIM1, TIM_INT_BREAK);      /* 打开中断 */
      TIM_PWM_Output_Enable(TIM1);
      break;
    case INV_MOTOR_BRAKE: // 刹车

      if (pwm_polarity == RESET)
      {
        //                                GD码配置了CH3EN待确认
        reg_temp &= (uint32_t)(~((uint32_t)TIM_CCEN_CC1EN));
        reg_temp &= (uint32_t)(~((uint32_t)TIM_CCEN_CC2EN));
        reg_temp &= (uint32_t)(~((uint32_t)TIM_CCEN_CC3EN));
        reg_temp |= (uint32_t)(((uint32_t)TIM_CCEN_CC1NEN));
        reg_temp |= (uint32_t)(((uint32_t)TIM_CCEN_CC2NEN));
        reg_temp |= (uint32_t)(((uint32_t)TIM_CCEN_CC3NEN));
      }
      else
      {
        reg_temp &= (uint32_t)(~((uint32_t)TIM_CCEN_CC1NEN));
        reg_temp &= (uint32_t)(~((uint32_t)TIM_CCEN_CC2NEN));
        reg_temp &= (uint32_t)(~((uint32_t)TIM_CCEN_CC3NEN));
        reg_temp |= (uint32_t)(((uint32_t)TIM_CCEN_CC1EN));
        reg_temp |= (uint32_t)(((uint32_t)TIM_CCEN_CC2EN));
        reg_temp |= (uint32_t)(((uint32_t)TIM_CCEN_CC3EN));
      }

      TIM1->CCEN = (uint32_t)reg_temp; // 上管有效，下管无效
      TIM_PWM_Output_Enable(TIM1);
      break;
    case INV_UVW_CHARGE:

      if (pwm_polarity == SET)
      {
        reg_temp &= (uint32_t)(~((uint32_t)TIM_CCEN_CC1EN));
        reg_temp &= (uint32_t)(~((uint32_t)TIM_CCEN_CC2EN));
        reg_temp &= (uint32_t)(~((uint32_t)TIM_CCEN_CC3EN));
        reg_temp |= (uint32_t)(((uint32_t)TIM_CCEN_CC1NEN));
        reg_temp |= (uint32_t)(((uint32_t)TIM_CCEN_CC2NEN));
        reg_temp |= (uint32_t)(((uint32_t)TIM_CCEN_CC3NEN));
      }
      else
      {
        reg_temp &= (uint32_t)(~((uint32_t)TIM_CCEN_CC1NEN));
        reg_temp &= (uint32_t)(~((uint32_t)TIM_CCEN_CC2NEN));
        reg_temp &= (uint32_t)(~((uint32_t)TIM_CCEN_CC3NEN));
        reg_temp |= (uint32_t)(((uint32_t)TIM_CCEN_CC1EN));
        reg_temp |= (uint32_t)(((uint32_t)TIM_CCEN_CC2EN));
        reg_temp |= (uint32_t)(((uint32_t)TIM_CCEN_CC3EN));
      }

      TIM1->CCEN = (uint32_t)reg_temp; // 下管有效，上管无效
      TIM_PWM_Output_Enable(TIM1);
      break;
    case INV_U_CHARGE:
      if (pwm_polarity == RESET)
      {
        reg_temp &= ~TIM_CCEN_CC1P;
      }
      else
      {
        reg_temp |= TIM_CCEN_CC1P;
      }
      TIM1->CCEN = (uint32_t)reg_temp | TIM_CCEN_CC1NEN; // U相下管输出 其他无效输出
      TIM_PWM_Output_Enable(TIM1);
      break;
    case INV_V_CHARGE:
      if (pwm_polarity == RESET)
      {
        reg_temp &= ~TIM_CCEN_CC2P;
      }
      else
      {
        reg_temp |= TIM_CCEN_CC2P;
      }
      /* set inverter bridge arm (VH) as "High" and output enable */
      TIM1->CCEN = (uint32_t)reg_temp | TIM_CCEN_CC2NEN; // V相下管输出 其他无效输出
      TIM_PWM_Output_Enable(TIM1);
      break;
    case INV_W_CHARGE:
      if (pwm_polarity == RESET)
      {
        reg_temp &= ~TIM_CCEN_CC3P;
      }
      else
      {
        reg_temp |= TIM_CCEN_CC3P;
      }
      /* set inverter bridge arm (WH) as "High" and output enable */
      TIM1->CCEN = (uint32_t)reg_temp | TIM_CCEN_CC3NEN; // W相下管输出 其他无效输出
      TIM_PWM_Output_Enable(TIM1);
      break;
    default: /* invalid arguments */
      /* turn off 6-phases (up/vp/wp, un/vn/wn) */
      /* timer_periph channels output disable */
      TIM_PWM_Output_Disable(TIM1);
      TIM1->CCEN = (uint32_t)reg_temp;
      break;
    }
  }
}

/******************************************************************************
* Description   : PWM duty set for inverter control
* Input         : timer_periph
                    COMP_TIMER;
                    FAN_TIMER;
* Input         : uduty;vduty;wduty
                    0-COMP_PWM_COUNT_SET;
* Input         : uphase_value;vdutyvphase_value;wphase_value
******************************************************************************/
void __attribute__((section(".RamFunc"))) pwm_duty_set(uint16_t duty1, uint16_t duty2, uint16_t duty3)
{
  TIM_Compare1_Set(TIM1, duty1); // U相占空比
  TIM_Compare2_Set(TIM1, duty2); // V相占空比
  TIM_Compare3_Set(TIM1, duty3); // W相占空比

  TIM_Compare7_Set(TIM1, duty1); // 设置触发采样时间
  TIM_Compare8_Set(TIM1, duty2);
  TIM_Compare9_Set(TIM1, duty3);

  TIM_Compare1_D_Set(TIM1, duty1); // U相 中央非对称模式向下计数值，可以自由更改AR值~1
  TIM_Compare2_D_Set(TIM1, duty2); // V相
  TIM_Compare3_D_Set(TIM1, duty3); // W相
}

/*************************************************************
 * 定时器6  1ms中断
 *************************************************************/
void TIM6_1Khz_Init(void)
{
  uint32_t prescaler_value;
  RCC_ClocksType RCC_Clocks;
  TIM_TimeBaseInitType TIM_TimeBaseStructure;
  NVIC_InitType NVIC_InitStructure;

  RCC_Clocks_Frequencies_Value_Get(&RCC_Clocks);

  if (RCC_Clocks.HclkFreq > RCC_Clocks.Pclk1Freq)
  {
    prescaler_value = RCC_Clocks.Pclk1Freq * 2;
  }
  else
  {
    prescaler_value = RCC_Clocks.Pclk1Freq;
  }

  TIM_Base_Struct_Initialize(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.Period = prescaler_value / 1000 / 100 - 1;
  TIM_TimeBaseStructure.Prescaler = 100 - 1;
  TIM_TimeBaseStructure.ClkDiv = TIM_CLK_DIV1;
  TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;

  TIM_Base_Initialize(TIM6, &TIM_TimeBaseStructure);
  TIM_Base_Reload_Mode_Set(TIM6, TIM_PSC_RELOAD_MODE_IMMEDIATE);

  TIM_Interrupt_Enable(TIM6, TIM_INT_UPDATE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Initializes(&NVIC_InitStructure);

  TIM_On(TIM6);
}

/*************************************************************
 * 定时器4
 *************************************************************/
void TIM4_ETR_Init(void)
{
  TIM_TimeBaseInitType TIM_TimeBaseStructure;
  NVIC_InitType NVIC_InitStructure;

  // 外部输入作为计数源，配置分频等，现在不设置分频滤波
  TIM_External_Clock_Mode2_Set(TIM4, TIM_EXT_TRG_PSC_OFF, TIM_EXT_TRIG_POLARITY_NONINVERTED, 0);

  TIM_Base_Struct_Initialize(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.Period = 65535;
  TIM_TimeBaseStructure.Prescaler = 0;
  TIM_TimeBaseStructure.ClkDiv = TIM_CLK_DIV1;
  TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;

  TIM_Base_Initialize(TIM4, &TIM_TimeBaseStructure);
  TIM_Base_Reload_Mode_Set(TIM4, TIM_PSC_RELOAD_MODE_IMMEDIATE);

  TIM_Interrupt_Enable(TIM4, TIM_INT_UPDATE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Initializes(&NVIC_InitStructure);

  TIM_On(TIM4);
}

void TIM4_Capture_Config(void)
{
  GPIO_InitType GPIO_InitStructure;
  TIM_ICInitType TIM_ICInitStructure;
  TIM_TimeBaseInitType TIM_TimeBaseStructure;
  DMA_InitType DMA_InitStructure;
  uint32_t prescaler_value;
  RCC_ClocksType RCC_Clocks;

  GPIO_Structure_Initialize(&GPIO_InitStructure);
  /* TIM4 channel 1 pin (PB.06) configuration */
  GPIO_InitStructure.Pin = GPIO_PIN_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.GPIO_Current = GPIO_DS_4MA;
  GPIO_InitStructure.GPIO_Alternate = GPIO_AF3_TIM4;
  GPIO_Peripheral_Initialize(GPIOB, &GPIO_InitStructure);

  RCC_Clocks_Frequencies_Value_Get(&RCC_Clocks);

  if (RCC_Clocks.HclkFreq > RCC_Clocks.Pclk1Freq)
  {
    prescaler_value = RCC_Clocks.Pclk1Freq * 2;
  }
  else
  {
    prescaler_value = RCC_Clocks.Pclk1Freq;
  }

  GPTIMClockFrequency = prescaler_value / 1000;

  DMA_Reset(DMA_CH2);
  DMA_Structure_Initializes(&DMA_InitStructure);
  DMA_InitStructure.PeriphAddr = (uint32_t)&TIM4->CCDAT1;
  DMA_InitStructure.MemAddr = (uint32_t)TIM_Freq_buff;
  DMA_InitStructure.Direction = DMA_DIR_PERIPH_SRC;
  DMA_InitStructure.BufSize = 2;
  DMA_InitStructure.PeriphInc = DMA_PERIPH_INC_MODE_DISABLE;
  DMA_InitStructure.MemoryInc = DMA_MEM_INC_MODE_ENABLE;
  DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_WORD;
  DMA_InitStructure.MemDataSize = DMA_MEM_DATA_WIDTH_WORD;
  DMA_InitStructure.CircularMode = DMA_CIRCULAR_MODE_DISABLE;
  DMA_InitStructure.Priority = DMA_CH_PRIORITY_MEDIUM;
  DMA_InitStructure.Mem2Mem = DMA_MEM2MEM_DISABLE;
  DMA_Initializes(DMA_CH2, &DMA_InitStructure);
  DMA_Channel_Request_Remap(DMA_CH2, DMA_REMAP_TIM4_CH1);
  DMA_Channel_Enable(DMA_CH2);

  /*60M / 10K = 6K  最高频率可以检测到6K，最低频率检测0.1HZ   20HZ ~ 150HZ*/
  TIM_Base_Struct_Initialize(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.Period = GPTIMClockFrequency - 1; // 定时器3工作在30M，计数值为30K
  TIM_TimeBaseStructure.Prescaler = 10000 - 1;            // 分频10K
  TIM_TimeBaseStructure.ClkDiv = TIM_CLK_DIV1;
  TIM_TimeBaseStructure.CntMode = TIM_CNT_MODE_UP;

  TIM_Base_Initialize(TIM4, &TIM_TimeBaseStructure);
  TIM_Base_Reload_Mode_Set(TIM4, TIM_PSC_RELOAD_MODE_IMMEDIATE);

  TIM_Input_Struct_Initialize(&TIM_ICInitStructure);
  TIM_ICInitStructure.Channel = TIM_CH_1;
  TIM_ICInitStructure.IcPolarity = TIM_IC_POLARITY_RISING;
  TIM_ICInitStructure.IcSelection = TIM_IC_SELECTION_DIRECTTI;
  TIM_ICInitStructure.IcPrescaler = TIM_IC_PSC_DIV1;
  TIM_ICInitStructure.IcFilter = 0x0;
  TIM_Input_Channel_Initialize(TIM4, &TIM_ICInitStructure);

  /* TIM enable counter */
  TIM_On(TIM4);
  TIM_Dma_Enable(TIM4, TIM_DMA_CC1);
}
