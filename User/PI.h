#ifndef _PI_H_
#define _PI_H_
#include "stdint.h"

typedef struct
{
    int32_t I_Out;
    int16_t OutMin;
    int16_t OutMax;
    int16_t Pid_Kp;
    int16_t Pid_Ki;
    int32_t Error;
    int16_t InputRef;
    int16_t Pid_Output;
} PI_DEF;

typedef struct
{
    PI_DEF Pi_D;
    PI_DEF Pi_Q;
    /* data */
} PI_DQ_DEF;

int16_t PID_Ctr(PI_DEF *pPi, int32_t error);
#endif // !1
