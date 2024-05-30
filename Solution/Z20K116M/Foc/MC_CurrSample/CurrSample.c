#include "HeadFile.h"
SAMPLE_CURR_DEF Sample_Curr;
int16_t SampleCurr_1st, SampleCurr_2nd;
/**
 * @brief      PhaseCurr_Get function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
PHASE_CURR_DEF PhaseCurr_Get(SAMPLE_CURR_DEF *pCurrSample)
{
    uint16_t Sector_Last;
    Sector_Last = Svm.Sector;
    PHASE_CURR_DEF Phase_Curr_Temp = {0, 0, 0};
    switch (Sector_Last)
    {
    case 0: /* constant-expression */
        /* code */
        pCurrSample->PhaseCurr.PhaseU = pCurrSample->Curr_SamplePoint_1st;
        pCurrSample->PhaseCurr.PhaseW = -pCurrSample->Curr_SamplePoint_2nd;
        pCurrSample->PhaseCurr.PhaseV = -(pCurrSample->PhaseCurr.PhaseU + pCurrSample->PhaseCurr.PhaseW);

        break;

    case 1:
        pCurrSample->PhaseCurr.PhaseV = pCurrSample->Curr_SamplePoint_1st;
        pCurrSample->PhaseCurr.PhaseW = -pCurrSample->Curr_SamplePoint_2nd;
        pCurrSample->PhaseCurr.PhaseU = -(pCurrSample->PhaseCurr.PhaseV + pCurrSample->PhaseCurr.PhaseW);

        break;

    case 2:
        pCurrSample->PhaseCurr.PhaseV = pCurrSample->Curr_SamplePoint_1st;
        pCurrSample->PhaseCurr.PhaseU = -pCurrSample->Curr_SamplePoint_2nd;
        pCurrSample->PhaseCurr.PhaseW = -(pCurrSample->PhaseCurr.PhaseV + pCurrSample->PhaseCurr.PhaseU);

        break;

    case 3:
        pCurrSample->PhaseCurr.PhaseW = pCurrSample->Curr_SamplePoint_1st;
        pCurrSample->PhaseCurr.PhaseU = -pCurrSample->Curr_SamplePoint_2nd;
        pCurrSample->PhaseCurr.PhaseV = -(pCurrSample->PhaseCurr.PhaseW + pCurrSample->PhaseCurr.PhaseU);

        break;

    case 4:
        pCurrSample->PhaseCurr.PhaseW = pCurrSample->Curr_SamplePoint_1st;
        pCurrSample->PhaseCurr.PhaseV = -pCurrSample->Curr_SamplePoint_2nd;
        pCurrSample->PhaseCurr.PhaseU = -(pCurrSample->PhaseCurr.PhaseW + pCurrSample->PhaseCurr.PhaseV);

        break;

    case 5:
        pCurrSample->PhaseCurr.PhaseU = pCurrSample->Curr_SamplePoint_1st;
        pCurrSample->PhaseCurr.PhaseV = -pCurrSample->Curr_SamplePoint_2nd;
        pCurrSample->PhaseCurr.PhaseW = -(pCurrSample->PhaseCurr.PhaseU + pCurrSample->PhaseCurr.PhaseV);
        break;
    }

    Phase_Curr_Temp = pCurrSample->PhaseCurr;
    return Phase_Curr_Temp;
}

/**
 * @brief      BiasDetect function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void BiasDetect(SAMPLE_CURR_DEF *pCurrSample)
{
    static uint16_t DetectCnt = 0;
    uint16_t DetectTime = 64;

    if (DetectCnt < DetectTime)
    {
        DetectCnt++;
        pCurrSample->SampleCurrSum_1st += SampleCurr_1st;
        pCurrSample->SampleCurrSum_2nd += SampleCurr_2nd;
    }
    else
    {
        DetectCnt = 0;
        pCurrSample->Offset_1st = pCurrSample->SampleCurrSum_1st >> 6;
        pCurrSample->Offset_2nd = pCurrSample->SampleCurrSum_2nd >> 6;
        pCurrSample->SampleCurrSum_1st = 0;
        pCurrSample->SampleCurrSum_2nd = 0;
    }
}
