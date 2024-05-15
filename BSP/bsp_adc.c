#include "bsp_adc.h"
__IO uint16_t ADC_RegularConvertedValueTab[2];
// DMA for adc requence
void DMA_AdcSequenceIntiall(void)
{
  DMA_InitType DMA_InitStructure;
  DMA_Reset(DMA_CH1);
  DMA_InitStructure.PeriphAddr = (uint32_t)&ADC->DAT;
  DMA_InitStructure.MemAddr = (uint32_t)ADC_RegularConvertedValueTab;
  DMA_InitStructure.Direction = DMA_DIR_PERIPH_SRC;                  // 从外设到存储器的数据传输
  DMA_InitStructure.BufSize = 2;                                     // 数据传输数量
  DMA_InitStructure.PeriphInc = DMA_PERIPH_INC_MODE_DISABLE;         // 外设地址不会随着每次传输而递增
  DMA_InitStructure.MemoryInc = DMA_MEM_INC_MODE_ENABLE;             // 内存地址随着每次传输而递增
  DMA_InitStructure.PeriphDataSize = DMA_PERIPH_DATA_WIDTH_HALFWORD; // 从外设地址读取的数据大小为16位
  DMA_InitStructure.MemDataSize = DMA_MEM_DATA_WIDTH_HALFWORD;       // 向存储器地址写入的数据大小为16位
  DMA_InitStructure.CircularMode = DMA_CIRCULAR_MODE_ENABLE;         // 通道配置为循环模式
  DMA_InitStructure.Priority = DMA_CH_PRIORITY_HIGH;                 // 高优先级
  DMA_InitStructure.Mem2Mem = DMA_MEM2MEM_DISABLE;                   // 失能存储器->存储器，即选择存储器和外设之间的传输
  DMA_Initializes(DMA_CH1, &DMA_InitStructure);
  DMA_Channel_Request_Remap(DMA_CH1, DMA_REMAP_ADC); // DMA通道请求为ADC
  /* Enable DMA channel1 */
  DMA_Channel_Enable(DMA_CH1); // 使能通道1
}

void Adc_Init(void)
{
  ADC_InitType ADC_InitStructure;
  NVIC_InitType NVIC_InitStructure;

  ADC_Reset();
  /* ADC regular sequencer */
  ADC_InitStructure.MultiChEn = ENABLE;                               // 开启扫描模式
  ADC_InitStructure.ContinueConvEn = ENABLE;                          // 关闭连续转换模式
  ADC_InitStructure.ExtTrigSelect = ADC_EXT_TRIGCONV_REGULAR_SWSTRRCH; // 软件触发规则通道转换
  ADC_InitStructure.DatAlign = ADC_DAT_ALIGN_R;                        // 右对齐
  ADC_InitStructure.ChsNumber = ADC_REGULAR_LEN_1;                     // 一个转换
  ADC_Initializes(&ADC_InitStructure);
  /* ADC regular channel configuration */
  ADC_Regular_Sequence_Conversion_Number_Config(ADC_Channel_11_PB2, ADC_REGULAR_NUMBER_1); // vbus
  ADC_Channel_Sample_Time_Config(ADC_Channel_11_PB2, ADC_SAMP_TIME_13CYCLES5);             // 13.5个周期作为通道采样时间

  /* Set injected sequencer length */
  ADC_Injected_Channels_Number_Config(ADC_INJECTED_LEN_2); // 注入通道两个转换
  /* ADC injected channel Configuration */
  ADC_Channel_Sample_Time_Config(ADC_Channel_08_PA7, ADC_SAMP_TIME_13CYCLES5); // 13.5个周期作为通道采样时间
  ADC_Injected_Sequence_Conversion_Number_Config(ADC_Channel_08_PA7, ADC_INJECTED_NUMBER_4);
  ADC_Injected_Sequence_Conversion_Number_Config(ADC_Channel_08_PA7, ADC_INJECTED_NUMBER_3);
  /* ADC injected external trigger configuration */
  ADC_Injected_Group_External_Trigger_Source_Config(ADC_EXT_TRIGCONV_INJECTED_T1_TRGO); // 配置为TIM1的TRGO触发
  /* Enable automatic injected conversion start after regular one */
  ADC_Injected_Group_Autoconversion_Disable(); // 关闭自动的注入通道序列转换

  ADC_Discontinuous_Mode_Config(ADC_DISCMODE_INJECTED_ENABLE); // 注入通道序列上使用间断模式

  /* Enable ADC */
  ADC_ON(); // 0->1:唤醒ADC;1->1:使能ADC转换
  /* Check ADC Ready */
  while (ADC_Flag_Status_Get(ADC_RD_FLAG, ADC_FLAG_JENDCA, ADC_FLAG_RDY) == RESET)
    ;
  /* Start ADC calibration */
  ADC_Calibration_Operation(ADC_CALIBRATION_ENABLE);
  /* Check the end of ADC calibration */
  while (ADC_Calibration_Operation(ADC_CALIBRATION_STS))
    ;

  /* Configure and enable ADC interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Initializes(&NVIC_InitStructure);
  /* Enable JEOC interrupt */
  ADC_Interrupts_Enable(ADC_INT_JENDC); // 所有注入通道中断使能
	ADC_Interrupts_Enable(ADC_INT_JENDCA); // 所有注入通道中断使能

  /* Enable ADC DMA */
  // ADC_DMA_Transfer_Enable();
  ADC_DMA_Transfer_Disable(); // 失能DMA
  /* Enable ADC external trigger */
  //ADC_External_Trigger_Conversion_Config(ADC_EXTTRIGCONV_REGULAR_ENABLE);
  /* Enable ADC inj external trigger */
  ADC_External_Trigger_Conversion_Config(ADC_EXTTRIGCONV_INJECTED_ENABLE);
	ADC_ON(); // 0->1:唤醒ADC;1->1:使能ADC转换
  // DMA_AdcSequenceIntiall();
}
