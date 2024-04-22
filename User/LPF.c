#include "HeadFile.h"

/**
 * @brief      LPF_Ctr function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */ 
inline int16_t LPF_Ctr(LPF_DEF *pLPF, int16_t Input)
{
    int32_t Out;

    Out = pLPF->Out;
    Out = Data_Limit(Out + ((int32_t)pLPF->CoefA * (int32_t)Input) - ((int32_t)pLPF->CoefB * (Out >> 15u)), 31u);
    pLPF->Out = Out;

    return (int16_t)(Out >> 15u);
}

