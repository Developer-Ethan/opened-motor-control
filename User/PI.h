#ifndef _PI_H_
#define _PI_H_
#include "stdint.h"

typedef struct
{
    int32_t I_Out;
    int32_t Iout_Min;
    int32_t Iout_Max;
    int32_t Pid_Kp;
    int32_t Pid_Ki;
    int32_t Out_Min;
    int32_t Out_Max;
    int16_t InputRef;
    int16_t Pid_Output;
} PI_DEF;

typedef struct
{
    PI_DEF Pi_D;
    PI_DEF Pi_Q;
    /* data */
} PI_DQ_DEF;

int16_t PID_Ctr(PI_DEF *pPi, int16_t error);
#endif // !1
