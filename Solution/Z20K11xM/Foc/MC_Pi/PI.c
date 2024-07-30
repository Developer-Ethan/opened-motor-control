#include "HeadFile.h"

/**
 * @brief      PID_Ctr function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
int16_t PID_Ctr(PI_DEF *pPi, int32_t error)
{
  int32_t I_Out;
  int16_t Pi_Out;
  int32_t Integral;
  int32_t Proportion;
  int32_t OutMax, OutMin;

  OutMin = pPi->OutMin << 14u;
  OutMax = pPi->OutMax << 14u;

  pPi->Error = Data_Limit(error, 16);

  Integral = pPi->Error * pPi->Pid_Ki;
  I_Out = pPi->I_Out + Integral;
  I_Out = SATURATE(I_Out, OutMin, OutMax);
  pPi->I_Out = I_Out;

  Proportion = (pPi->Error * pPi->Pid_Kp) >> 14u;
  Proportion = Data_Limit(Proportion, 16);

  Pi_Out = (pPi->I_Out >> 14u) + Proportion;
  Pi_Out = SATURATE(Pi_Out, pPi->OutMin, pPi->OutMax);
  pPi->Pid_Output = (int16_t)(Pi_Out);
  return (pPi->Pid_Output);
}
