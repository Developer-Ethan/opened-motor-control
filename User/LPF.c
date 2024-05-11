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
    Out = Data_Limit(Out * pLPF->Coeff + ((32767 - pLPF->Coeff) * Input), 31u);
    pLPF->Out = Out >> 15u;

    return (int16_t)(pLPF->Out);
}
