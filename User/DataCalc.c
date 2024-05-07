#include "HeadFile.h"

extern uint16_t SampleCurr_1st, SampleCurr_2nd;
/**
 * @brief      Data_Limit function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
int32_t Data_Limit(int32_t data, uint8_t bit)
{
    int32_t Data_Max;
    int32_t Data_Min;

    Data_Max = (1 << (bit - 1)) - 1;
    Data_Min = ~Data_Max;

    if (data > Data_Max)
    {
        return (Data_Max);
    }
    else if (data < Data_Min)
    {
        return (Data_Min);
    }
    else
    {
        return (data);
    }
}

/**
 * @brief      AngleAmp_Get function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
inline uint16_t AngleAmp_Get(AXIS_DEF Axis, uint16_t *pAmp)
{
    int32_t AbsReal;
    int32_t AbsImag;
    uint32_t Index;
    uint32_t Angle;
    uint32_t TableValue;

    AbsReal = Axis.Real;
    if (AbsReal < 0)
    {
        AbsReal = -AbsReal;
    }
    AbsImag = Axis.Imag;
    if (AbsImag < 0)
    {
        AbsImag = -AbsImag;
    }

    if (AbsImag <= AbsReal)
    {
        Index = ((uint32_t)(AbsImag) * 1024) / ((uint32_t)AbsReal);
        TableValue = Table_Arctan[Index];
        *pAmp = ((uint32_t)(AbsReal)*Table_Amp[Index]) >> 15u;

        if (Axis.Real > 0)
        {
            if (Axis.Imag > 0)
            {
                Angle = TableValue;
            }
            else
            {
                Angle = 0x10000u - TableValue;
            }
        }
        else
        {
            if (Axis.Imag > 0)
            {
                Angle = 0x8000u - TableValue;
            }
            else
            {
                Angle = 0x8000u + TableValue;
            }
        }
    }
    else
    {
        Index = ((uint32_t)(AbsReal) * 1024) / ((uint32_t)AbsImag);
        TableValue = Table_Arctan[Index];
        *pAmp = ((uint32_t)(AbsImag)*Table_Amp[Index]) >> 15u;

        if (Axis.Real > 0)
        {
            if (Axis.Imag > 0)
            {
                Angle = 0x4000u - TableValue;
            }
            else
            {
                Angle = 0xC000u + TableValue;
            }
        }
        else
        {
            if (Axis.Imag > 0)
            {
                Angle = 0x4000u + TableValue;
            }
            else
            {
                Angle = 0xC000u - TableValue;
            }
        }
    }

    return (uint16_t)(Angle);
}

/**
 * @brief      BiasDetect function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void BiasDetect(FOC_DEF *pFoc)
{
    static uint16_t DetectCnt = 0;
    uint16_t DetectTime = 64;

    if (DetectCnt < DetectTime)
    {
        DetectCnt++;
        pFoc->Sample_Curr.SampleCurrSum_1st += SampleCurr_1st;
        pFoc->Sample_Curr.SampleCurrSum_2nd += SampleCurr_2nd;
    }
    else
    {
        DetectCnt = 0;
        pFoc->Sample_Curr.Offset_1st = pFoc->Sample_Curr.SampleCurrSum_1st >> 6;
        pFoc->Sample_Curr.Offset_2nd = pFoc->Sample_Curr.SampleCurrSum_2nd >> 6;
				pFoc->Sample_Curr.SampleCurrSum_1st = 0;
				pFoc->Sample_Curr.SampleCurrSum_2nd = 0;		
    }
}
