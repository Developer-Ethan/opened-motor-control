#include "AppHeadFile.h"

uint32_t AdcMapData[2] = {0};
uint32_t IRQn_AdcMapData[5] = {0, 0, 0, 0, 0};
uint32_t IRQn_AdcMapDataVal[5] = {0, 0, 0, 0, 0};
/**
 * @brief      ADC Config function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
uint8_t Hal_SetupAdcs(void)
{
    uint8_t TDGFaultFlag;
    ADC_Config_t SubcaseAdcCfg =
        {
            /* resolution */
            ADC_RESOLUTION_12BIT,
            /* vref */
            ADC_VREF_INTERNAL,
            /* trigger mode */
            ADC_TDG_TRIGGER,
            /* conversion mode */
            ADC_CONVERSION_SINGLE,
            /* average disabled */
            ADC_AVGS_DISABLED,
            /* Set sample interval > 500ns */
            50,
        };

    ADC_ChannelConfig_t AdcChannelCfg0 =
        {
            ADC_SINGLE_MODE,  /* Single-Ended Mode Selected */
            HAL_ADC_TEMP_CHN, /* Single mode, channel[12] and vssa */
            ADC_N_NONE,       /* Single mode, N-channel donn't need to configure */
        };

    ADC_ChannelConfig_t AdcChannelCfg1 =
        {
            ADC_SINGLE_MODE,  /* Single-Ended Mode Selected */
            HAL_ADC_VMOT_CHN, /* Single mode, channel[12] and vssa */
            ADC_N_NONE,       /* Single mode, N-channel donn't need to configure */
        };

    ADC_ChannelConfig_t AdcChannelCfg2 =
        {
            ADC_SINGLE_MODE, /* Single-Ended Mode Selected */
            HAL_ADC_IV_CHN,  /* Single mode, channel[12] and vssa */
            ADC_N_NONE,      /* Single mode, N-channel donn't need to configure */
        };

    ADC_ChannelConfig_t AdcChannelCfg3 =
        {
            ADC_SINGLE_MODE,        /* Single-Ended Mode Selected */
            HAL_ADC_BUSCURRENT_CHN, /* Single mode, channel[12] and vssa */
            ADC_N_NONE,             /* Single mode, N-channel donn't need to configure */
        };

    ADC_TDGTriggerConfig_t AdcTriggerConfig =
        {
            /* Loop mode Selected */
            ADC_MAPPING_MODE,
            /* CMD0: channel 15; */
            HAL_ADC_VMOT_CHN,
            /* CMD1: channel 14; */
            HAL_ADC_IV_CHN,
            /* CMD2: channel 13; */
            HAL_ADC_IV_CHN,
            /* CMD3: channel 12; */
            HAL_ADC_TEMP_CHN,
            /* CMD4: channel 7; */
            HAL_ADC_BUSCURRENT_CHN,
            /* CMD5: channel 7; all CMDs can be Configured as different channels */
            HAL_ADC_IV_CHN,
        };

    /* mod value, single, divide4, SW trig, clear to mod */
    TDG_InitConfig_t Config =
        {
            PWM_MOD_COUNTER * 2U - 1, TDG_COUNT_SINGLE, TDG_CLK_DIVIDE_1, TDG_TRIG_EXTERNAL, TDG_UPDATE_IMMEDIATELY, TDG_CLEAR_MODULATOR};

    /* 001*1/64Tclock */
    TDG_DelayOutputConfig_t Doconfig =
        {
            TDG_DO_0,
            9,
            ENABLE,
        };

    TDG_ChannelConfig_t Chconfig =
        {
            TDG_CHANNEL_0,
            0U,
            1U,
            &Doconfig,
        };

    /* Reset ADC */
    SYSCTRL_ResetModule(HAL_ADC_SYSCTRL_MODULE);
    /* Enable ADC clock */
    SYSCTRL_EnableModule(HAL_ADC_SYSCTRL_MODULE);
    /* adc pinmux */
    /* PTB22/ADC0_CH19 for motor V_current */
    PORT_PinmuxConfig(HAL_ADC_IV_PORT, HAL_ADC_IV_PIN, HAL_ADC_IV_PINMUX);
    /* PTC17/ADC0_CH15 for motor bus volatage */
    PORT_PinmuxConfig(HAL_ADC_VMOT_PORT, HAL_ADC_VMOT_PIN, HAL_ADC_VMOT_PINMUX);
    /* PTA7/ADC0_CH3 for motor temperature */
    PORT_PinmuxConfig(HAL_ADC_TEMP_PORT, HAL_ADC_TEMP_PIN, HAL_ADC_TEMP_PINMUX);
    /* PTA7/ADC0_CH3 for motor temperature */
    PORT_PinmuxConfig(HAL_ADC_BUSCURRENT_PORT, HAL_ADC_BUSCURRENT_PIN, HAL_ADC_BUSCURRENT_PINMUX);
    /* Reset software */
    ADC_SoftwareReset(HAL_ADC_ID);
    /* Self calibration */
    // ADC_SelfCalibration(HAL_ADC_ID);
    /* Initialize ADC */
    ADC_Init(HAL_ADC_ID, &SubcaseAdcCfg);
    /* Redefine the depth the function */
    ADC_FifoDepthRedefine(HAL_ADC_ID, 6);
    /* Set ADC watermark */
    /* fifo WM > 3, that is when WM=4,flag will be set */
    ADC_FifoWatermarkConfig(HAL_ADC_ID, VALUE_WM);
    /* Configure input channel */
    ADC_ChannelConfig(HAL_ADC_ID, &AdcChannelCfg0);
    ADC_ChannelConfig(HAL_ADC_ID, &AdcChannelCfg1);
    ADC_ChannelConfig(HAL_ADC_ID, &AdcChannelCfg2);
    ADC_ChannelConfig(HAL_ADC_ID, &AdcChannelCfg3);

    /* Mask FIFO watermark interrupt */
    ADC_IntMask(HAL_ADC_ID, ADC_FWM_INT, UNMASK);

    /* Set trigger mode */
    ADC_TDGTriggerConfig(HAL_ADC_ID, &AdcTriggerConfig);
    /* Clear TCOMP interrupt */
    ADC_IntClear(HAL_ADC_ID, ADC_TCOMP_INT);
    /* Enable ADC module */
    ADC_Enable(HAL_ADC_ID);
    /* Enable ADC dma request */
    ADC_DmaRequestCmd(HAL_ADC_ID, DISABLE);

    /*Enable TDG module */
    SYSCTRL_EnableModule(HAL_TDG_SYSID);
    /* Initialize TDG */
    TDG_InitConfig(HAL_TGD_ID, &Config);
    /* Set TDG delay output */
    TDG_ChannelDelayOutputConfig(HAL_TGD_ID, &Chconfig, ENABLE);

    Chconfig.channelId = TDG_CHANNEL_1;
    Doconfig.offset = (uint16_t)PWM_MOD_COUNTER / 5;
    TDG_ChannelDelayOutputConfig(HAL_TGD_ID, &Chconfig, ENABLE);

    Chconfig.channelId = TDG_CHANNEL_2;
    Doconfig.offset = (uint16_t)PWM_MOD_COUNTER / 4;
    TDG_ChannelDelayOutputConfig(HAL_TGD_ID, &Chconfig, ENABLE);

//    Chconfig.channelId = TDG_CHANNEL_3;
//    Doconfig.offset = (uint16_t)((PWM_MOD_COUNTER / 2) + 400);
//    TDG_ChannelDelayOutputConfig(HAL_TGD_ID, &Chconfig, ENABLE);
//
//    Chconfig.channelId = TDG_CHANNEL_4;
//    Doconfig.offset = (uint16_t)((PWM_MOD_COUNTER / 2) + 900);
//    TDG_ChannelDelayOutputConfig(HAL_TGD_ID, &Chconfig, ENABLE);
    /* enable TDG */
    TDG_Enable(HAL_TGD_ID, ENABLE);
    /* Load channel Configuration */
    TDGFaultFlag = (uint8_t)TDG_LoadCmd(HAL_TGD_ID);
	
	TDG_IntMask(HAL_TGD_ID,TDG_INT_CH1,UNMASK);
	TDG_IntMask(HAL_TGD_ID,TDG_INT_CH2,UNMASK);
		
    ADC_IntClear(HAL_ADC_ID, ADC_FWM_INT);
    // ADC_IntMask(HAL_ADC_ID,ADC_TCOMP_INT, UNMASK);

    return TDGFaultFlag;
}

/**
 * @brief      ADC Config function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void GetAdcData(void)
{
    adc_reg_t *ADCx = (adc_reg_t *)(ADC0_BASE_ADDR);

    while (0U != ADCx->ADC_FCTRL.FCOUNT)
    {
        (void)ADCx->ADC_DATA_RD.ADC_DATA_RD;
    }

    IRQn_AdcMapDataVal[0] = IRQn_AdcMapData[0] & 0XFFF;
    IRQn_AdcMapDataVal[1] = IRQn_AdcMapData[1] & 0XFFF;
    IRQn_AdcMapDataVal[2] = IRQn_AdcMapData[2] & 0XFFF;
}