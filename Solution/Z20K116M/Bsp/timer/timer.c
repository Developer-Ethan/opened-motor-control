#include "AppHeadFile.h"

Hal_CvType PwmCv;
/**
 * @brief      PWM config function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void HAL_setupPwms()
{
    /*TIM module enable*/
    SYSCTRL_ResetModule(SYSCTRL_TIM0);
    SYSCTRL_EnableModule(SYSCTRL_TIM0);

    SYSCTRL_ResetModule(SYSCTRL_TIM2);
    SYSCTRL_EnableModule(SYSCTRL_TIM2);

    /* TIM complementary PWM output channel 4 and channel 5 config struct :disable fault ctrl and disable ccv sync function */
    TIM_CompPwmChannelConfig_t cPwmChConfig0 =
        {
            TIM_PAIR_CHANNEL_1,
            TIM_PWM_HIGH_TRUE_PULSE,
            TIM_POL_HIGH,
            // 0.5*(1-a)*PWM_MAX a is the ratio of caculated ccv
            (PWM_MOD_COUNTER * 25 / 100),
            // 0.5*(1+a)*PWM_MAX a is the ratio of caculated ccv
            (PWM_MOD_COUNTER * 75 / 100),
            ENABLE,
            ENABLE,
            ENABLE};
    /* TIM complementary PWM output channel 6 and channel 7 config struct*/
    TIM_CompPwmChannelConfig_t cPwmChConfig1 =
        {
            TIM_PAIR_CHANNEL_0,
            TIM_PWM_HIGH_TRUE_PULSE,
            TIM_POL_HIGH,
            (PWM_MOD_COUNTER * 25 / 100),
            (PWM_MOD_COUNTER * 75 / 100),
            ENABLE,
            ENABLE,
            ENABLE};
    /* TIM complementary PWM output channel 0 and channel 1 config struct*/
    TIM_CompPwmChannelConfig_t cPwmChConfig2 =
        {
            TIM_PAIR_CHANNEL_2,
            TIM_PWM_HIGH_TRUE_PULSE,
            TIM_POL_HIGH,
            (PWM_MOD_COUNTER * 25 / 100),
            (PWM_MOD_COUNTER * 75 / 100),
            ENABLE,
            ENABLE,
            ENABLE};

    /* TIM complementary PWM output config array*/
    TIM_CompPwmChannelConfig_t cPwmChConfig[3] = {cPwmChConfig0, cPwmChConfig1, cPwmChConfig2};

    /* TIM complementary PWM output Config*/
    TIM_CompPwmConfig_t cPwmConfig =
        {
            3,                   /*pair number*/
            0,                   /*counter init value*/
            PWM_MOD_COUNTER - 1, /*counter max value*/
            TIM_PRESCALER_4,     /*dead PRESCALER*/
            0,                   /*dead clock, dead time = TIM_PRESCALER_1 * 128 set 2us was 32 for 4910 has this funciton*/
            cPwmChConfig         /*channel config pointer*/
        };

    /*match relaod*/
    TIM_ChannelMatchConfig_t channelMatchConfig[6] =
        {
            {TIM_CHANNEL_4, DISABLE},
            {TIM_CHANNEL_5, DISABLE},
            {TIM_CHANNEL_2, DISABLE},
            {TIM_CHANNEL_3, DISABLE},
            {TIM_CHANNEL_0, DISABLE},
            {TIM_CHANNEL_1, DISABLE}};

    /*TIM reload config*/
    TIM_ReloadConfig_t reloadConfig =
        {
            TIM_RELOAD_FULL_CYCLE,
            1,
            6,
            channelMatchConfig};

    /*TIM sync config for update ccv*/
    TIM_PwmSyncConfig_t syncConfig =
        {
            TIM_UPDATE_PWM_SYN,
            TIM_UPDATE_PWM_SYN,
            DISABLE,
            ENABLE,
            &reloadConfig};

    /* GPIO config */
    PORT_PinmuxConfig(PORT_A, GPIO_2, PTA2_TIM0_CH0); // AHI
    PORT_PinmuxConfig(PORT_C, GPIO_1, PTC1_TIM0_CH1); // ALO

    PORT_PinmuxConfig(PORT_C, GPIO_2, PTC2_TIM0_CH2); // BHI
    PORT_PinmuxConfig(PORT_C, GPIO_3, PTC3_TIM0_CH3); // BLO

    PORT_PinmuxConfig(PORT_B, GPIO_4, PTB4_TIM0_CH4); // CHI
    PORT_PinmuxConfig(PORT_B, GPIO_5, PTB5_TIM0_CH5); // CLO

    /* set up-counting mode */
    TIM_CountingModeConfig(PWM_TIM_ID, TIM_COUNTING_UP);

    /* output complementary init*/
    TIM_OutputComplementaryPwmConfig(PWM_TIM_ID, &cPwmConfig);

    /* reload config*/
    TIM_SyncConfig(PWM_TIM_ID, &syncConfig);

    // Disable the pwm output
    Hal_PwmOutputDis();
	TIM_IntMask(TIM0_ID, TIM_INT_TO, MASK);
	TIM_IntMask(TIM0_ID, TIM_INT_RLD, MASK);
    TIM_StopCounter(PWM_TIM_ID);

    /* TIM fault control config struct definition */
    const TIM_PwmFaultCtrlConfig_t config =
        {
            ENABLE, TIM_INPUT_FILTER_15, TIM_LOW_STATE, TIM_Fault_MANUAL_CLEAR, {
                                                                                    {DISABLE, DISABLE, TIM_POL_LOW}, /* TIM_POL_LOW: 0 is active fault0 input*/
                                                                                    {ENABLE, ENABLE, TIM_POL_LOW},   /* TIM_FAULT_CHANNEL_1 */
                                                                                }};
    /* TIM initialise fault control config */
    TIM_FaultControlConfig(FAULT_TIM_ID, &config);
    // PORT_PinmuxConfig(PORT_E, GPIO_9, PTE9_TIM2_FLT0);
    PORT_PinmuxConfig(Z20A8300A_DIAG_PORT, Z20A8300A_DIAG_PIN, Z20A8300A_DIAG_PINMUX);
    /* enable function */
    TIM_IntClear(FAULT_TIM_ID, TIM_INT_FAULT);
    TIM_InitTriggerCmd(PWM_TIM_ID, ENABLE);
    // TIM_IntMask(PWM_TIM_ID,TIM_INT_TO,UNMASK);

    // PWM_IN about duty capure
    //PORT_PinmuxConfig(PORT_A, GPIO_12, PTA12_TIM2_CH2);
    /* input config, the TIM input channel should be in low level if it is set to capture rising edge first when TIM is in input capture mode*/
    /* TIM input capture channel config struct  initial:channelId, falling,rising, disable filter, continue capture */
    TIM_DualEdgeChannelConfig_t chconfig1 =
        {
            TIM_PAIR_CHANNEL_1, TIM_INPUT_EDGE_RISING, TIM_INPUT_EDGE_FAILING, TIM_INPUT_FILTER_DISABLED, TIM_CONTINUOUS_PULSE_CAPTURE};

    /* TIM input capture global config struct initial:  number 1,mod value 0xFFFF, input capture channel config struct  */
    const TIM_DualEdgeCaptureConfig_t config1 =
        {
            1, 0xFFFF, &chconfig1};
    /*input capture init*/
    TIM_DualEdgeCaptureInit(TIM2_ID, &config1);
    TIM_SetCounterInitialVal(TIM2_ID, 0x0000);
    /* counting mode: up counting mode */
    TIM_CountingModeConfig(TIM2_ID, TIM_COUNTING_UP);
    /*start counter*/
    TIM_StartCounter(TIM2_ID, TIM_CLK_SOURCE_FUNCTION, TIM_CLK_DIVIDE_32);
    /* reload flag clear */
    TIM_IntClear(TIM2_ID, TIM_INT_RLD);
    /* clear CHF before dual edge capture */
    TIM_IntClear(TIM2_ID, TIM_INT_CH2);
    TIM_IntClear(TIM2_ID, TIM_INT_CH3);
    /* enable the interrupt */
    TIM_IntMask(TIM2_ID, TIM_INT_CH3, UNMASK);
    TIM_IntMask(TIM2_ID, TIM_INT_TO, UNMASK);

    // PWM_OUT
    //PORT_PinmuxConfig(PWM_OUT_PORT, PWM_OUT_PIN, PWM_OUT_PINMUX);
    GPIO_SetPinDir(PWM_OUT_PORT, PWM_OUT_PIN, GPIO_OUTPUT);
}