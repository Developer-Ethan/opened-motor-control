#include "HeadFile.h"

/**
 * @brief      ClarkeTransform function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
AXIS_DEF ClarkeTransform(PHASE_CURR_DEF *pPhaseCurr)
{
    AXIS_DEF StatCurr = {0, 0};

    StatCurr.Real = (int16_t)pPhaseCurr->PhaseU;
    StatCurr.Imag = (pPhaseCurr->PhaseV - pPhaseCurr->PhaseW) * SQRT1_3 >> SHIFT_15BITS;

    return StatCurr;
}

/**
 * @brief      ParkTransform function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
AXIS_DEF ParkTransform(AXIS_DEF *pAxis, uint16_t ElecAngle)
{
    AXIS_DEF RotaCurr = {0, 0};
    int32_t Cos;
    int32_t Sin;
    uint32_t Angle_Temp;

    Angle_Temp = ElecAngle >> 6u;

    Cos = pTable_Cos[Angle_Temp];
    Sin = Table_Sin[Angle_Temp];

    RotaCurr.Real = Data_Limit((pAxis->Real * Cos + pAxis->Imag * Sin) >> SHIFT_15BITS, BIT_MAX);
    RotaCurr.Imag = Data_Limit((pAxis->Imag * Cos - pAxis->Real * Sin) >> SHIFT_15BITS, BIT_MAX);

    return RotaCurr;
}

/**
 * @brief      iParkTransform function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
AXIS_DEF iParkTransform(AXIS_DEF *pAxis, uint16_t ElecAngle)
{
    AXIS_DEF StatVolt = {0, 0};
    int32_t Cos;
    int32_t Sin;
    uint32_t Angle_Temp;

    Angle_Temp = ElecAngle >> 6u;

    Cos = pTable_Cos[Angle_Temp];
    Sin = Table_Sin[Angle_Temp];

    StatVolt.Real = Data_Limit((DataMult_Q15(pAxis->Real, Cos)) - (DataMult_Q15(pAxis->Imag, Sin)), BIT_MAX);
    StatVolt.Imag = Data_Limit((DataMult_Q15(pAxis->Real, Sin)) + (DataMult_Q15(pAxis->Imag, Cos)), BIT_MAX);

    return StatVolt;
}
