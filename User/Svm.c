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
    uint32_t Angle;
    uint16_t Sector;
    uint16_t Index;
    int32_t T1; // the first simple width
    int32_t T2; // the second simple width
    int32_t T_temp;
    uint16_t Period;
    uint16_t Diff;
    uint16_t CompareValue_SimplePoint1;
    uint16_t CompareValue_SimplePoint2;
    int16_t X, Y, Z;

    Period = TimerPeriod;

    Angle = ((uint32_t)pSvm->Angle) * 6u;
    Sector = (Angle >> 16u) & 7;
    pSvm->Sector = Sector;
    Index = (Angle >> 8u) & 0xFFu;
    pSvm->ModulCoeff = ((int16_t)((float)((2 * TimerPeriod * SQRT_3 >> SHIFT_15BITS) << SHIFT_15BITS) / Foc.Sample_Volt));
    X = (pSvm->ModulCoeff * pAxis->Imag) >> SHIFT_15BITS;
    Y = (pSvm->ModulCoeff * (((28376 * pAxis->Real) >> SHIFT_15BITS) + ((16384 * pAxis->Imag) >> SHIFT_15BITS))) >> SHIFT_15BITS;
    Z = (pSvm->ModulCoeff * (((16384 * pAxis->Imag) >> SHIFT_15BITS) - ((28376 * pAxis->Real) >> SHIFT_15BITS))) >> SHIFT_15BITS;
    // T1 = (uint16_t)(((float)pSvm->Amp / Foc.Sample_Volt) * pSvm->ModulCoeff) * Table_Sin60[255 - Index] >> SHIFT_15BITS;
    //T1 = T1 >> 2; // shift prepare for following calc
    // T2 = (uint16_t)(((float)pSvm->Amp / Foc.Sample_Volt) * pSvm->ModulCoeff) * Table_Sin60[Index] >> SHIFT_15BITS;
    //T2 = T2 >> 2; // shift prepare for following calc
    //pSvm->T1 = T1;
    //pSvm->T2 = T2;

    switch (Sector) // 4->6->2->3->1->5->4
    {
    case (0u):
        T1 = -Z;
        T2 = X;
        T1 = T1 >> 2;
        T2 = T2 >> 2;
        pSvm->T1 = T1;
        pSvm->T2 = T2;
        pSvm->ComparePoint_1st_Up = ((int32_t)Period / 2u) - pSvm->T1 - pSvm->T2; // Ta = T0 / 2 = (Ts-T4-T6)/4
        pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_1st_Up + 2 * pSvm->T1;     // Tb = Ta + T4/2
        pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_2nd_Up + 2 * pSvm->T2;     // Tc = Tb + T6/2

        pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Up;
        pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Up;
        pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Up;

#if SHIFT_PHASE_EN
        T1 = 2 * T1;
        T2 = 2 * T2;
        if (T1 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - T1;
            pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up - Diff;
            if (pSvm->ComparePoint_1st_Up < 0)
            {
                pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up_Last;
            }
            pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down + Diff;
        }
        if (T2 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - T2;
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

    case (1u):
        T1 = Z;
        T2 = Y;
        T1 = T1 >> 2;
        T2 = T2 >> 2;
        pSvm->T1 = T1;
        pSvm->T2 = T2;
        pSvm->ComparePoint_2nd_Up = ((int32_t)Period / 2u) - pSvm->T2 - pSvm->T1; // Tb = T0 / 2 = (Ts-T2-T4)/4
        pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_2nd_Up + 2 * pSvm->T2;     // Ta = Tb + T2/2 = Ta + 2*pSvm->T2
        pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_1st_Up + 2 * pSvm->T1;     // Tc = Ta + T6/2

        pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Up;
        pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Up;
        pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Up;

#if SHIFT_PHASE_EN
        T_temp = T1;
        T1 = T2;
        T2 = T_temp; // function time is not changed,only change the name of the first function time and the second function time

        T1 = 2 * T1;
        T2 = 2 * T2;
        if (T1 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - T1;
            pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up - Diff;
            if (pSvm->ComparePoint_2nd_Up < 0)
            {
                pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up_Last;
            }
            pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down + Diff;
        }
        if (T2 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - T2;
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

    case (2u):
        T1 = X;
        T2 = -Y;
        T1 = T1 >> 2;
        T2 = T2 >> 2;
        pSvm->T1 = T1;
        pSvm->T2 = T2;
        pSvm->ComparePoint_2nd_Up = ((int32_t)Period / 2u) - pSvm->T1 - pSvm->T2; // Tb = T0 / 2 = (Ts-T2-T3)/4
        pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_2nd_Up + 2 * pSvm->T1;     // Tc = Tb + T2/2
        pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_3th_Up + 2 * pSvm->T2;     // Ta = Tc + T3/2

        pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Up;
        pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Up;
        pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Up;

#if SHIFT_PHASE_EN
        T1 = 2 * T1;
        T2 = 2 * T2;
        if (T1 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - T1;
            pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up - Diff;
            if (pSvm->ComparePoint_2nd_Up < 0)
            {
                pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up_Last;
            }
            pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down + Diff;
        }
        if (T2 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - T2;
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

    case (3u):
        T1 = -X;
        T2 = Z;
        T1 = T1 >> 2;
        T2 = T2 >> 2;
        pSvm->T1 = T1;
        pSvm->T2 = T2;
        pSvm->ComparePoint_3th_Up = ((int32_t)Period / 2u) - pSvm->T2 - pSvm->T1; // Tc = T0 / 2 = (Ts-T1-T3)/4
        pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_3th_Up + 2 * pSvm->T2;     // Tb = Tc + T1/2
        pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_2nd_Up + 2 * pSvm->T1;     // Ta = Tb + T3/2

        pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Up;
        pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Up;
        pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Up;

#if SHIFT_PHASE_EN
        T_temp = T1;
        T1 = T2;
        T2 = T_temp; // function time is not changed,only change the name of the first function time and the second function time

        T1 = 2 * T1;
        T2 = 2 * T2;
        if (T1 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - T1;
            pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up - Diff;
            if (pSvm->ComparePoint_3th_Up < 0)
            {
                pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up_Last;
            }
            pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down + Diff;
        }
        if (T2 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - T2;
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

    case (4u):
        T1 = -Y;
        T2 = -Z;
        T1 = T1 >> 2;
        T2 = T2 >> 2;
        pSvm->T1 = T1;
        pSvm->T2 = T2;
        pSvm->ComparePoint_3th_Up = ((int32_t)Period / 2u) - pSvm->T1 - pSvm->T2; // Tc = T0 / 2 = (Ts-T1-T5)/4
        pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_3th_Up + 2 * pSvm->T1;     // Ta = Tc + T1/2
        pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_1st_Up + 2 * pSvm->T2;     // Tb = Ta + T5/2

        pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Up;
        pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Up;
        pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Up;

#if SHIFT_PHASE_EN
        T1 = 2 * T1;
        T2 = 2 * T2;
        if (T1 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - T1;
            pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up - Diff;
            if (pSvm->ComparePoint_3th_Up < 0)
            {
                pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up_Last;
            }
            pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down + Diff;
        }
        if (T2 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - T2;
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

    case (5u):
        T1 = Y;
        T2 = -X;
        T1 = T1 >> 2;
        T2 = T2 >> 2;
        pSvm->T1 = T1;
        pSvm->T2 = T2;
        pSvm->ComparePoint_1st_Up = ((int32_t)Period / 2u) - pSvm->T2 - pSvm->T1; // Ta = T0 / 2 = (Ts-T4-T5)/4
        pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_1st_Up + 2 * pSvm->T2;     // Tc = Ta + T4/2
        pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_3th_Up + 2 * pSvm->T1;     // Tb = Tc + T5/2

        pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Up;
        pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Up;
        pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Up;

#if SHIFT_PHASE_EN
        T_temp = T1;
        T1 = T2;
        T2 = T_temp; // function time is not changed,only change the name of the first function time and the second function time

        T1 = 2 * T1;
        T2 = 2 * T2;
        if (T1 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - T1;
            pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up - Diff;
            if (pSvm->ComparePoint_1st_Up < 0)
            {
                pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up_Last;
            }
            pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down + Diff;
        }
        if (T2 < pSvm->StableScale)
        {
            Diff = pSvm->StableScale - T2;
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
    TIM_Compare7_Set(TIM1, CompareValue_SimplePoint1);
    TIM_Compare8_Set(TIM1, CompareValue_SimplePoint2);

    pSvm->ComparePoint_1st_Up_Last = pSvm->ComparePoint_1st_Up;
    pSvm->ComparePoint_2nd_Up_Last = pSvm->ComparePoint_2nd_Up;
    pSvm->ComparePoint_3th_Up_Last = pSvm->ComparePoint_3th_Up;
}
