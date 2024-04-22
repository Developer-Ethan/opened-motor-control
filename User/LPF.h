#ifndef _LPF_H_
#define _LPF_H_
#include "stdint.h"
typedef struct
{
    int16_t CoefA;
    int16_t CoefB;
    int32_t Out;
    /* data */
}LPF_DEF;



int16_t LPF_Ctr(LPF_DEF *pLPF,int16_t Input);
#endif
