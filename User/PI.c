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
    int32_t Temp;
    int32_t Min;
    int32_t Max;

    I_Out = pPi->I_Out + ((int32_t)error * (int32_t)pPi->Pid_Ki);

    Min = ((int32_t)(pPi->Iout_Min)) << 15u;
    Max = ((int32_t)(pPi->Iout_Max)) << 15u;

    if (I_Out < Min)
    {
        I_Out = Min;
    }
    else if (I_Out > Max)
    {
        I_Out = Max;
    }

    pPi->I_Out = I_Out;

    Temp = Data_Limit((int32_t)error * (int32_t)pPi->Pid_Kp, 31u - 6u);

    Pi_Out = (I_Out + (Temp << 6u)) >> 15u;

    Min = (int32_t)pPi->Out_Min;
    Max = (int32_t)pPi->Out_Max;

    if (Pi_Out < Min)
    {
        Pi_Out = Min;
    }
    else if (Pi_Out > Max)
    {
        Pi_Out = Max;
    }
    pPi->Pid_Output = (int16_t)(Pi_Out);
    return (pPi->Pid_Output);
}
