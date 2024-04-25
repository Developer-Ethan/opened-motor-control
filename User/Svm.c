#include "HeadFile.h"

SVM_DEF Svm;
/**
 * @brief      Svm_Ctr function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void Svm_Ctr(SVM_DEF *pSvm, AXIS_DEF *pAxis)
{
    int32_t T1; // the first simple width
    int32_t T2; // the second simple width
    uint16_t Period;
    uint16_t Diff;
    uint16_t CompareValue_SimplePoint1;
    uint16_t CompareValue_SimplePoint2;
    int16_t X, Y, Z;
    int16_t Vref1, Vref2, Vref3;
    uint8_t A, B, C, N;
    int16_t Ta, Tb, Tc;

    Period = TimerPeriod;

    pSvm->ModulCoeff = (int16_t)(((2 * Period * SQRT_3 >> SHIFT_15BITS) << SHIFT_15BITS) / Foc.Sample_Volt);
    X = (pSvm->ModulCoeff * pAxis->Imag) >> SHIFT_15BITS;
    Y = (pSvm->ModulCoeff * (((28376 * pAxis->Real) >> SHIFT_15BITS) + ((16384 * pAxis->Imag) >> SHIFT_15BITS))) >> SHIFT_15BITS;
    Z = (pSvm->ModulCoeff * (((16384 * pAxis->Imag) >> SHIFT_15BITS) - ((28376 * pAxis->Real) >> SHIFT_15BITS))) >> SHIFT_15BITS;

    Vref1 = pAxis->Imag;
    Vref2 = ((28376 * pAxis->Real) >> SHIFT_15BITS) - ((16384 * pAxis->Imag) >> SHIFT_15BITS);
    Vref3 = -((28376 * pAxis->Real) >> SHIFT_15BITS) - ((16384 * pAxis->Imag) >> SHIFT_15BITS);

    if (Vref1 > 0)
    {
        A = 1;
    }
    else
    {
        A = 0;
    }
    if (Vref2 > 0)
    {
        B = 1;
    }
    else
    {
        B = 0;
    }
    if (Vref3 > 0)
    {
        C = 1;
    }
    else
    {
        C = 0;
    }

    N = 4 * C + 2 * B + A;

    switch (N)
    {
    case 1:
        /* code */
        T1 = Z;
        T2 = Y;
        pSvm->Sector = 1;
        break;
    case 2:
        /* code */
        T1 = Y;
        T2 = -X;
        pSvm->Sector = 5;
        break;
    case 3:
        /* code */
        T1 = -Z;
        T2 = X;
        pSvm->Sector = 0;
        break;
    case 4:
        /* code */
        T1 = -X;
        T2 = Z;
        pSvm->Sector = 3;
        break;
    case 5:
        /* code */
        T1 = X;
        T2 = -Y;
        pSvm->Sector = 2;
        break;
    case 6:
        /* code */
        T1 = -Y;
        T2 = -Z;
        pSvm->Sector = 4;
        break;
    }

    T1 = T1 >> 1;
    T2 = T2 >> 1;
    pSvm->T1 = T1;
    pSvm->T2 = T2;
    Ta = (int32_t)(Period) / 2 - (pSvm->T1 >> 1) - (pSvm->T2 >> 1);
    Tb = Ta + pSvm->T1;
    Tc = Tb + pSvm->T2;

    switch (pSvm->Sector) // 4->6->2->3->1->5->4
    {
    case (0u): // N 3
        pSvm->ComparePoint_1st_Up = Ta;
        pSvm->ComparePoint_2nd_Up = Tb;
        pSvm->ComparePoint_3th_Up = Tc;

        pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Up;
        pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Up;
        pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Up;

#if SHIFT_PHASE_EN
        if (pSvm->T1 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - pSvm->T1;
            pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up - Diff;
            if (pSvm->ComparePoint_1st_Up < 0)
            {
                pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up_Last;
            }
            pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down + Diff;
        }
        if (pSvm->T2 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - pSvm->T2;
            pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up + Diff;
            if (pSvm->ComparePoint_3th_Up > Period)
            {
                pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up_Last;
            }
            pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down - Diff;
        }
#endif
        CompareValue_SimplePoint1 = pSvm->ComparePoint_1st_Up + pSvm->ShiftScale;
        CompareValue_SimplePoint2 = pSvm->ComparePoint_2nd_Up + pSvm->ShiftScale;
        break;

    case (1u): // N 1
        pSvm->ComparePoint_1st_Up = Tb;
        pSvm->ComparePoint_2nd_Up = Ta;
        pSvm->ComparePoint_3th_Up = Tc;

        pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Up;
        pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Up;
        pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Up;

#if SHIFT_PHASE_EN
        if (pSvm->T1 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - pSvm->T1;
            pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up - Diff;
            if (pSvm->ComparePoint_2nd_Up < 0)
            {
                pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up_Last;
            }
            pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down + Diff;
        }
        if (pSvm->T2 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - pSvm->T2;
            pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up + Diff;
            if (pSvm->ComparePoint_3th_Up > Period)
            {
                pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up_Last;
            }
            pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down - Diff;
        }
#endif
        CompareValue_SimplePoint1 = pSvm->ComparePoint_2nd_Up + pSvm->ShiftScale;
        CompareValue_SimplePoint2 = pSvm->ComparePoint_1st_Up + pSvm->ShiftScale;
        break;

    case (2u): // N 5
        pSvm->ComparePoint_1st_Up = Tc;
        pSvm->ComparePoint_2nd_Up = Ta;
        pSvm->ComparePoint_3th_Up = Tb;

        pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Up;
        pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Up;
        pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Up;

#if SHIFT_PHASE_EN
        if (pSvm->T1 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - pSvm->T1;
            pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up - Diff;
            if (pSvm->ComparePoint_2nd_Up < 0)
            {
                pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up_Last;
            }
            pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down + Diff;
        }
        if (pSvm->T2 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - pSvm->T2;
            pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up + Diff;
            if (pSvm->ComparePoint_1st_Up > Period)
            {
                pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up_Last;
            }
            pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down - Diff;
        }
#endif
        CompareValue_SimplePoint1 = pSvm->ComparePoint_2nd_Up + pSvm->ShiftScale;
        CompareValue_SimplePoint2 = pSvm->ComparePoint_3th_Up + pSvm->ShiftScale;
        break;

    case (3u): // N 4
        pSvm->ComparePoint_1st_Up = Tc;
        pSvm->ComparePoint_2nd_Up = Tb;
        pSvm->ComparePoint_3th_Up = Ta;

        pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Up;
        pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Up;
        pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Up;

#if SHIFT_PHASE_EN
        if (pSvm->T1 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - pSvm->T1;
            pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up - Diff;
            if (pSvm->ComparePoint_3th_Up < 0)
            {
                pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up_Last;
            }
            pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down + Diff;
        }
        if (pSvm->T2 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - pSvm->T2;
            pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up + Diff;
            if (pSvm->ComparePoint_1st_Up > Period)
            {
                pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up_Last;
            }
            pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down - Diff;
        }
#endif
        CompareValue_SimplePoint1 = pSvm->ComparePoint_3th_Up + pSvm->ShiftScale;
        CompareValue_SimplePoint2 = pSvm->ComparePoint_2nd_Up + pSvm->ShiftScale;
        break;

    case (4u): // N 6
        pSvm->ComparePoint_1st_Up = Tb;
        pSvm->ComparePoint_2nd_Up = Tc;
        pSvm->ComparePoint_3th_Up = Ta;

        pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Up;
        pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Up;
        pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Up;

#if SHIFT_PHASE_EN
        if (pSvm->T1 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - pSvm->T1;
            pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up - Diff;
            if (pSvm->ComparePoint_3th_Up < 0)
            {
                pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up_Last;
            }
            pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down + Diff;
        }
        if (pSvm->T2 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - pSvm->T2;
            pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up + Diff;
            if (pSvm->ComparePoint_2nd_Up > Period)
            {
                pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up_Last;
            }
            pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down - Diff;
        }
#endif
        CompareValue_SimplePoint1 = pSvm->ComparePoint_3th_Up + pSvm->ShiftScale;
        CompareValue_SimplePoint2 = pSvm->ComparePoint_1st_Up + pSvm->ShiftScale;
        break;

    case (5u): // N 2
        pSvm->ComparePoint_1st_Up = Ta;
        pSvm->ComparePoint_2nd_Up = Tc;
        pSvm->ComparePoint_3th_Up = Tb;

        pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Up;
        pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Up;
        pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Up;

#if SHIFT_PHASE_EN
        if (pSvm->T1 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - pSvm->T1;
            pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up - Diff;
            if (pSvm->ComparePoint_1st_Up < 0)
            {
                pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up_Last;
            }
            pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down + Diff;
        }
        if (pSvm->T2 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - pSvm->T2;
            pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up + Diff;
            if (pSvm->ComparePoint_2nd_Up > Period)
            {
                pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up_Last;
            }
            pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down - Diff;
        }
#endif
        CompareValue_SimplePoint1 = pSvm->ComparePoint_1st_Up + pSvm->ShiftScale;
        CompareValue_SimplePoint2 = pSvm->ComparePoint_3th_Up + pSvm->ShiftScale;
        break;
    }

    TIM_Compare1_Set(TIM1, pSvm->ComparePoint_1st_Up);
    TIM_Compare2_Set(TIM1, pSvm->ComparePoint_2nd_Up);
    TIM_Compare3_Set(TIM1, pSvm->ComparePoint_3th_Up);
    TIM_Compare1_D_Set(TIM1, pSvm->ComparePoint_1st_Down);
    TIM_Compare2_D_Set(TIM1, pSvm->ComparePoint_2nd_Down);
    TIM_Compare3_D_Set(TIM1, pSvm->ComparePoint_3th_Down);
    // TIM_Compare7_Set(TIM1, CompareValue_SimplePoint1);
    // TIM_Compare8_Set(TIM1, CompareValue_SimplePoint2);

    pSvm->ComparePoint_1st_Up_Last = pSvm->ComparePoint_1st_Up;
    pSvm->ComparePoint_2nd_Up_Last = pSvm->ComparePoint_2nd_Up;
    pSvm->ComparePoint_3th_Up_Last = pSvm->ComparePoint_3th_Up;
}
