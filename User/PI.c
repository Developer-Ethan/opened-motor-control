#include "HeadFile.h"

/**
 * @brief      PID_Ctr function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
inline int16_t PID_Ctr(PI_DEF *pPi, int16_t error)
{
    int32_t I_Out;
    int32_t Pi_Out;
    int32_t Integral;
    int32_t Proportion;

    error = Data_Limit(error, 16);
    Integral = (error * pPi->Pid_Ki) >> SHIFT_15BITS;
    Integral = Data_Limit(Integral, 16);
    I_Out = pPi->I_Out + Integral;

    if (I_Out < pPi->Iout_Min)
    {
        I_Out = pPi->Iout_Min;
    }
    else if (I_Out > pPi->Iout_Max)
    {
        I_Out = pPi->Iout_Max;
    }

    pPi->I_Out = I_Out;

    Proportion = (error * pPi->Pid_Kp) >> SHIFT_15BITS;
    Proportion = Data_Limit(Proportion, 16);

    Pi_Out = pPi->I_Out + Proportion;

    if (Pi_Out < pPi->Out_Min)
    {
        Pi_Out = pPi->Out_Min;
    }
    else if (Pi_Out > pPi->Out_Max)
    {
        Pi_Out = pPi->Out_Max;
    }
    pPi->Pid_Output = (int16_t)(Pi_Out);
    return (pPi->Pid_Output);
}
