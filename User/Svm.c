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
    int16_t T0, T1, T2, Tsum;
    uint16_t Period;
    uint16_t Diff;
    uint16_t CompareValue_SimplePoint1;
    uint16_t CompareValue_SimplePoint2;
    int16_t X, Y, Z;
    int16_t Vref1, Vref2, Vref3;
    uint8_t N;
    int16_t Ta, Tb, Tc;

    Period = TimerPeriod;

    pSvm->ModulCoeff = (int16_t)(((2 * Period * SQRT_3 >> SHIFT_15BITS) << SHIFT_15BITS) / Foc.Sample_Volt);
    X = (pSvm->ModulCoeff * pAxis->Imag) >> SHIFT_15BITS;
    Y = (pSvm->ModulCoeff * ((28376 * pAxis->Real + 16384 * pAxis->Imag) >> SHIFT_15BITS)) >> SHIFT_15BITS;
    Z = (pSvm->ModulCoeff * ((16384 * pAxis->Imag - 28376 * pAxis->Real) >> SHIFT_15BITS)) >> SHIFT_15BITS;

    Vref1 = pAxis->Imag;
    Vref2 = (28376 * pAxis->Real - 16384 * pAxis->Imag) >> SHIFT_15BITS;
    Vref3 = (-28376 * pAxis->Real - 16384 * pAxis->Imag) >> SHIFT_15BITS;

    N = 4 * SIGN(Vref3,0,1) + 2 * SIGN(Vref2,0,1) + SIGN(Vref1,0,1);

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

		Tsum = (T1 + T2) >> 1u;
		if(Tsum > Period)
		{
				T1 = T1 * Period / Tsum;
				T2 = T2 * Period / Tsum;
		}
		
    T1 = T1 >> 1;
    T2 = T2 >> 1;
    T0 = Period - T1 - T2;
		
    pSvm->T1 = T1;
    pSvm->T2 = T2;
    pSvm->T0 = T0 >> 1;
		pSvm->T0 = SATURATE(pSvm->T0,0,Period);
		pSvm->T1 = SATURATE(pSvm->T1,0,Period);
		pSvm->T2 = SATURATE(pSvm->T2,0,Period);
		
    Ta = pSvm->T0;
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
        if ((pSvm->T1 < pSvm->StableScale) && (pSvm->T2 < pSvm->StableScale)) // belongs to the first Non-observation area
        {
            Diff = pSvm->StableScale - pSvm->T1;
            pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up - Diff;
            pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down + Diff;
						if(pSvm->ComparePoint_1st_Up < 0)
						{
								pSvm->ComparePoint_1st_Up = 0;
						}

            Diff = pSvm->StableScale - pSvm->T2;
            pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up + Diff;
            pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down - Diff;
        }
        else if ((pSvm->T1 < pSvm->StableScale) && (pSvm->T2 > pSvm->StableScale))
        {
            if ((pSvm->T1 + pSvm->T0) > pSvm->StableScale) // sector transitin belongs to the second  Non-observation area
            {
                Diff = pSvm->StableScale - pSvm->T1;
                pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up - Diff;
                pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down + Diff;
            }
            else
            {
                Diff = pSvm->T0;
                pSvm->ComparePoint_1st_Up = 0;
                pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down + Diff;
                if ((pSvm->T0 + pSvm->T1 + pSvm->T2) >= 2 * pSvm->StableScale) // saturation of phase shifting
                {
                    Diff = pSvm->StableScale - (pSvm->T1 + pSvm->T0);
                    pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up + Diff;
                    pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down - Diff;
                }
                else
                {
                }
            }
        }
        else if ((pSvm->T1 > pSvm->StableScale) && (pSvm->T2 < pSvm->StableScale))
        {
            if ((pSvm->T2 + pSvm->T0) > pSvm->StableScale) // sector transitin belongs to the second  Non-observation area
            {
                Diff = pSvm->StableScale - pSvm->T2;
                pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up + Diff;
                pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down - Diff;
            }
            else
            {
                Diff = pSvm->T0;
                pSvm->ComparePoint_3th_Up = Period;
                pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down - Diff;
                if ((pSvm->T0 + pSvm->T1 + pSvm->T2) >= 2 * pSvm->StableScale) // saturation of phase shifting
                {
                    Diff = pSvm->StableScale - (pSvm->T2 + pSvm->T0);
                    pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up - Diff;
                    pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down + Diff;
                }
                else
                {
                }
            }
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
        if ((pSvm->T1 < pSvm->StableScale) && (pSvm->T2 < pSvm->StableScale)) // belongs to the first Non-observation area
        {
            Diff = pSvm->StableScale - pSvm->T1;
            pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up - Diff;
            pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down + Diff;
						if(pSvm->ComparePoint_2nd_Up < 0)
						{
								pSvm->ComparePoint_2nd_Up = 0;
						}
						
            Diff = pSvm->StableScale - pSvm->T2;
            pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up + Diff;
            pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down - Diff;
        }
        else if ((pSvm->T1 < pSvm->StableScale) && (pSvm->T2 > pSvm->StableScale))
        {
            if ((pSvm->T1 + pSvm->T0) > pSvm->StableScale) // sector transitin belongs to the second  Non-observation area
            {
                Diff = pSvm->StableScale - pSvm->T1;
                pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up - Diff;
                pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down + Diff;
            }
            else
            {
                Diff = pSvm->T0;
                pSvm->ComparePoint_2nd_Up = 0;
                pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down + Diff;
                if ((pSvm->T0 + pSvm->T1 + pSvm->T2) >= 2 * pSvm->StableScale) // saturation of phase shifting
                {
                    Diff = pSvm->StableScale - (pSvm->T1 + pSvm->T0);
                    pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up + Diff;
                    pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down - Diff;
                }
                else
                {
                }
            }
        }
        else if ((pSvm->T1 > pSvm->StableScale) && (pSvm->T2 < pSvm->StableScale))
        {
            if ((pSvm->T2 + pSvm->T0) > pSvm->StableScale) // sector transitin belongs to the second  Non-observation area
            {
                Diff = pSvm->StableScale - pSvm->T2;
                pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up + Diff;
                pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down - Diff;
            }
            else
            {
                Diff = pSvm->T0;
                pSvm->ComparePoint_3th_Up = Period;
                pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down - Diff;
                if ((pSvm->T0 + pSvm->T1 + pSvm->T2) >= 2 * pSvm->StableScale) // saturation of phase shifting
                {
                    Diff = pSvm->StableScale - (pSvm->T2 + pSvm->T0);
                    pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up - Diff;
                    pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down + Diff;
                }
                else
                {
                }
            }
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
        if ((pSvm->T1 < pSvm->StableScale) && (pSvm->T2 < pSvm->StableScale)) // belongs to the first Non-observation area
        {
            Diff = pSvm->StableScale - pSvm->T1;
            pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up - Diff;
            pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down + Diff;
						if(pSvm->ComparePoint_2nd_Up < 0)
						{
								pSvm->ComparePoint_2nd_Up = 0;
						}
						
            Diff = pSvm->StableScale - pSvm->T2;
            pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up + Diff;
            pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down - Diff;
        }
        else if ((pSvm->T1 < pSvm->StableScale) && (pSvm->T2 > pSvm->StableScale))
        {
            if ((pSvm->T1 + pSvm->T0) > pSvm->StableScale) // sector transitin belongs to the second  Non-observation area
            {
                Diff = pSvm->StableScale - pSvm->T1;
                pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up - Diff;
                pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down + Diff;
            }
            else
            {
                Diff = pSvm->T0;
                pSvm->ComparePoint_2nd_Up = 0;
                pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down + Diff;
                if ((pSvm->T0 + pSvm->T1 + pSvm->T2) >= 2 * pSvm->StableScale) // saturation of phase shifting
                {
                    Diff = pSvm->StableScale - (pSvm->T1 + pSvm->T0);
                    pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up + Diff;
                    pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down - Diff;
                }
                else
                {
                }
            }
        }
        else if ((pSvm->T1 > pSvm->StableScale) && (pSvm->T2 < pSvm->StableScale))
        {
            if ((pSvm->T2 + pSvm->T0) > pSvm->StableScale) // sector transitin belongs to the second  Non-observation area
            {
                Diff = pSvm->StableScale - pSvm->T2;
                pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up + Diff;
                pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down - Diff;
            }
            else
            {
                Diff = pSvm->T0;
                pSvm->ComparePoint_1st_Up = Period;
                pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down - Diff;
                if ((pSvm->T0 + pSvm->T1 + pSvm->T2) >= 2 * pSvm->StableScale) // saturation of phase shifting
                {
                    Diff = pSvm->StableScale - (pSvm->T2 + pSvm->T0);
                    pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up - Diff;
                    pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down + Diff;
                }
                else
                {
                }
            }
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
        if ((pSvm->T1 < pSvm->StableScale) && (pSvm->T2 < pSvm->StableScale)) // belongs to the first Non-observation area
        {
            Diff = pSvm->StableScale - pSvm->T1;
            pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up - Diff;
            pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down + Diff;
						if(pSvm->ComparePoint_3th_Up < 0)
						{
								pSvm->ComparePoint_3th_Up = 0;
						}
						
            Diff = pSvm->StableScale - pSvm->T2;
            pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up + Diff;
            pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down - Diff;
        }
        else if ((pSvm->T1 < pSvm->StableScale) && (pSvm->T2 > pSvm->StableScale))
        {
            if ((pSvm->T1 + pSvm->T0) > pSvm->StableScale) // sector transitin belongs to the second  Non-observation area
            {
                Diff = pSvm->StableScale - pSvm->T1;
                pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up - Diff;
                pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down + Diff;
            }
            else
            {
                Diff = pSvm->T0;
                pSvm->ComparePoint_3th_Up = 0;
                pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down + Diff;
                if ((pSvm->T0 + pSvm->T1 + pSvm->T2) >= 2 * pSvm->StableScale) // saturation of phase shifting
                {
                    Diff = pSvm->StableScale - (pSvm->T1 + pSvm->T0);
                    pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up + Diff;
                    pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down - Diff;
                }
                else
                {
                }
            }
        }
        else if ((pSvm->T1 > pSvm->StableScale) && (pSvm->T2 < pSvm->StableScale))
        {
            if ((pSvm->T2 + pSvm->T0) > pSvm->StableScale) // sector transitin belongs to the second  Non-observation area
            {
                Diff = pSvm->StableScale - pSvm->T2;
                pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up + Diff;
                pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down - Diff;
            }
            else
            {
                Diff = pSvm->T0;
                pSvm->ComparePoint_1st_Up = Period;
                pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down - Diff;
                if ((pSvm->T0 + pSvm->T1 + pSvm->T2) >= 2 * pSvm->StableScale) // saturation of phase shifting
                {
                    Diff = pSvm->StableScale - (pSvm->T2 + pSvm->T0);
                    pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up - Diff;
                    pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down + Diff;
                }
                else
                {
                }
            }
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
        if ((pSvm->T1 < pSvm->StableScale) && (pSvm->T2 < pSvm->StableScale)) // belongs to the first Non-observation area
        {
            Diff = pSvm->StableScale - pSvm->T1;
            pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up - Diff;
            pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down + Diff;
						if(pSvm->ComparePoint_3th_Up < 0)
						{
								pSvm->ComparePoint_3th_Up = 0;
						}
						
            Diff = pSvm->StableScale - pSvm->T2;
            pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up + Diff;
            pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down - Diff;
        }
        else if ((pSvm->T1 < pSvm->StableScale) && (pSvm->T2 > pSvm->StableScale))
        {
            if ((pSvm->T1 + pSvm->T0) > pSvm->StableScale) // sector transitin belongs to the second  Non-observation area
            {
                Diff = pSvm->StableScale - pSvm->T1;
                pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up - Diff;
                pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down + Diff;
            }
            else
            {
                Diff = pSvm->T0;
                pSvm->ComparePoint_3th_Up = 0;
                pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down + Diff;
                if ((pSvm->T0 + pSvm->T1 + pSvm->T2) >= 2 * pSvm->StableScale) // saturation of phase shifting
                {
                    Diff = pSvm->StableScale - (pSvm->T1 + pSvm->T0);
                    pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up + Diff;
                    pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down - Diff;
                }
                else
                {
                }
            }
        }
        else if ((pSvm->T1 > pSvm->StableScale) && (pSvm->T2 < pSvm->StableScale))
        {
            if ((pSvm->T2 + pSvm->T0) > pSvm->StableScale) // sector transitin belongs to the second  Non-observation area
            {
                Diff = pSvm->StableScale - pSvm->T2;
                pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up + Diff;
                pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down - Diff;
            }
            else
            {
                Diff = pSvm->T0;
                pSvm->ComparePoint_2nd_Up = Period;
                pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down - Diff;
                if ((pSvm->T0 + pSvm->T1 + pSvm->T2) >= 2 * pSvm->StableScale) // saturation of phase shifting
                {
                    Diff = pSvm->StableScale - (pSvm->T2 + pSvm->T0);
                    pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up - Diff;
                    pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down + Diff;
                }
                else
                {
                }
            }
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
        if ((pSvm->T1 < pSvm->StableScale) && (pSvm->T2 < pSvm->StableScale)) // belongs to the first Non-observation area
        {
            Diff = pSvm->StableScale - pSvm->T1;
            pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up - Diff;
            pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down + Diff;
						if(pSvm->ComparePoint_1st_Up < 0)
						{
								pSvm->ComparePoint_1st_Up = 0;
						}
						
            Diff = pSvm->StableScale - pSvm->T2;
            pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up + Diff;
            pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down - Diff;
        }
        else if ((pSvm->T1 < pSvm->StableScale) && (pSvm->T2 > pSvm->StableScale))
        {
            if ((pSvm->T1 + pSvm->T0) > pSvm->StableScale) // sector transitin belongs to the second  Non-observation area
            {
                Diff = pSvm->StableScale - pSvm->T1;
                pSvm->ComparePoint_1st_Up = pSvm->ComparePoint_1st_Up - Diff;
                pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down + Diff;
            }
            else
            {
                Diff = pSvm->T0;
                pSvm->ComparePoint_1st_Up = 0;
                pSvm->ComparePoint_1st_Down = pSvm->ComparePoint_1st_Down + Diff;
                if ((pSvm->T0 + pSvm->T1 + pSvm->T2) >= 2 * pSvm->StableScale) // saturation of phase shifting
                {
                    Diff = pSvm->StableScale - (pSvm->T1 + pSvm->T0);
                    pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up + Diff;
                    pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down - Diff;
                }
                else
                {
                }
            }
        }
        else if ((pSvm->T1 > pSvm->StableScale) && (pSvm->T2 < pSvm->StableScale))
        {
            if ((pSvm->T2 + pSvm->T0) > pSvm->StableScale) // sector transitin belongs to the second  Non-observation area
            {
                Diff = pSvm->StableScale - pSvm->T2;
                pSvm->ComparePoint_2nd_Up = pSvm->ComparePoint_2nd_Up + Diff;
                pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down - Diff;
            }
            else
            {
                Diff = pSvm->T0;
                pSvm->ComparePoint_2nd_Up = Period;
                pSvm->ComparePoint_2nd_Down = pSvm->ComparePoint_2nd_Down - Diff;
                if ((pSvm->T0 + pSvm->T1 + pSvm->T2) >= 2 * pSvm->StableScale) // saturation of phase shifting
                {
                    Diff = pSvm->StableScale - (pSvm->T2 + pSvm->T0);
                    pSvm->ComparePoint_3th_Up = pSvm->ComparePoint_3th_Up - Diff;
                    pSvm->ComparePoint_3th_Down = pSvm->ComparePoint_3th_Down + Diff;
                }
                else
                {
                }
            }
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
}
