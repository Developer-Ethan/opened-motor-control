#include "HeadFile.h"
SAMPLE_CURR_DEF Sample_Curr;
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
