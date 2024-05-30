#include "AppHeadFile.h"

/**
 * @brief      Stim config function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void HAL_setupStim()
{
    /* Enable STIM module */
    SYSCTRL_EnableModule(SYSCTRL_STIM);
    /* STIM configuration */
    const STIM_Config_t stimConfig =
        {
            .workMode = STIM_FREE_COUNT,
            .compareValue = SLOW_TIMER_MS * 64000, /*counter clock is 64M, compare value =64000,  period = 1ms*/
            .countResetMode = STIM_INCREASE_FROM_0,
            .clockSource = STIM_FUNCTION_CLOCK,
        };

    /* Init STIM_0*/
    STIM_Init(STIM_0, &stimConfig);
    /*Disable STIM*/
    STIM_Disable(STIM_0);
}