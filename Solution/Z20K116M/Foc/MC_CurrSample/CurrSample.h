#ifndef _CURRSAMPLE_H_
#define _CURRSAMPLE_H_
#include "stdint.h"
typedef struct
{
    int16_t PhaseU;
    int16_t PhaseV;
    int16_t PhaseW;
    /* data */
} PHASE_CURR_DEF;

typedef struct
{
    PHASE_CURR_DEF PhaseCurr;
    int16_t Curr_SamplePoint_1st;
    int16_t Curr_SamplePoint_2nd;
    int16_t Offset_1st;
    int16_t Offset_2nd;
    uint16_t SampleCurr[5];
    int32_t SampleCurrSum_1st;
    int32_t SampleCurrSum_2nd;
    /* data */
} SAMPLE_CURR_DEF;

PHASE_CURR_DEF PhaseCurr_Get(SAMPLE_CURR_DEF *pCurrSample);
void BiasDetect(SAMPLE_CURR_DEF *pCurrSample);
extern SAMPLE_CURR_DEF Sample_Curr;
extern int16_t SampleCurr_1st, SampleCurr_2nd;
#endif
