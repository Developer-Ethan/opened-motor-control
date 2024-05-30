#ifndef _TIMER_H
#define _TIMER_H
#include <stdbool.h>
#include "Z20K116M.h"
#include "Z20K11xM_tdg.h"
#include "AppHeadFile.h"
static bool isPwmEnabled = false;
static tim_reg_w_t *TIMx_w = (tim_reg_w_t *)(TIM0_BASE_ADDR);

#define CCW (1)
#define CW (0)
/**
 *  @brief CCV elements type definition
 */
typedef struct
{
    uint32_t CCV0; // Output: Timx_ccv0
    uint32_t CCV1; // Output: Timx_ccv1
    uint32_t CCV2; // Output: Timx_ccv0
    uint32_t CCV3; // Output: Timx_ccv1
    uint32_t CCV4; // Output: Timx_ccv0
    uint32_t CCV5; // Output: Timx_ccv1
} Hal_CvType;

/**
 * @brief      Update the offset data of TDG function.
 *
 * @param[in]  Ch1Delay: TDG chn1 offset value.
 * @param[in]  Ch2Delay: TDG chn2 offset value.
 *
 * @return     None.
 *
 */

static inline void Hal_UpdateTdgDelayOut(uint32_t Ch1Delay, uint32_t Ch2Delay)
{
    tdg_reg_t *TDGx = (tdg_reg_t *)(TDG0_BASE_ADDR);
    tdg_reg_w_t *TDGxw = (tdg_reg_w_t *)(TDG0_BASE_ADDR);
    TDGxw->TDG_CHCFG[TDG_CHANNEL_1].TDG_CHDOOFS[0] = (uint16_t)Ch1Delay;
    TDGxw->TDG_CHCFG[TDG_CHANNEL_1].TDG_CHCTRL = 0x00000100;
    TDGxw->TDG_CHCFG[TDG_CHANNEL_2].TDG_CHDOOFS[0] = (uint16_t)Ch2Delay;
    TDGxw->TDG_CHCFG[TDG_CHANNEL_2].TDG_CHCTRL = 0x00000100;
    TDGx->TDG_CTRL1.CFGUP = 1U;
}

/**
 * @brief      Update the CCV of pwm function.
 *
 * @param[in]  ObjPtr: PWM CCV value.
 *
 * @return     None.
 *
 */
static inline void Hal_UpdateAsymmetricOutput(Hal_CvType *ObjPtr)
{
#if CW
    TIMx_w->TIM_CCVn[HAL_PWM_UH_CHN] = ObjPtr->CCV2;
    TIMx_w->TIM_CCVn[HAL_PWM_UL_CHN] = ObjPtr->CCV3;
    TIMx_w->TIM_CCVn[HAL_PWM_VH_CHN] = ObjPtr->CCV0;
    TIMx_w->TIM_CCVn[HAL_PWM_VL_CHN] = ObjPtr->CCV1;
    TIMx_w->TIM_CCVn[HAL_PWM_WH_CHN] = ObjPtr->CCV4;
    TIMx_w->TIM_CCVn[HAL_PWM_WL_CHN] = ObjPtr->CCV5;
#elif CCW
    TIMx_w->TIM_CCVn[HAL_PWM_UH_CHN] = ObjPtr->CCV0;
    TIMx_w->TIM_CCVn[HAL_PWM_UL_CHN] = ObjPtr->CCV1;
    TIMx_w->TIM_CCVn[HAL_PWM_VH_CHN] = ObjPtr->CCV2;
    TIMx_w->TIM_CCVn[HAL_PWM_VL_CHN] = ObjPtr->CCV3;
    TIMx_w->TIM_CCVn[HAL_PWM_WH_CHN] = ObjPtr->CCV4;
    TIMx_w->TIM_CCVn[HAL_PWM_WL_CHN] = ObjPtr->CCV5;
#endif
    TIMx_w->TIM_RELOAD |= 0x0100U;
}
/**
 * @brief      PWM output disable function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
static inline void Hal_PwmOutputDis(void)
{
    TIMx_w->TIM_GLBCR &= 0xffffff00U;
    isPwmEnabled = false;
}

/**
 * @brief      PWM output enable function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
static inline void Hal_PwmOutputEn(void)
{
    if (!isPwmEnabled)
    {
        TIMx_w->TIM_GLBCR |= 0x0000003fU;
        isPwmEnabled = true;
    }
}

void HAL_setupPwms();
extern Hal_CvType PwmCv;
#endif