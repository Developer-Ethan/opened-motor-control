#ifndef _LPF_H_
#define _LPF_H_
#include "stdint.h"
typedef struct
{
    int16_t Coeff;
    int32_t Out;
    float BandWidthPu;
    /* data */
} LPF_DEF;

int16_t LPF_Ctr(LPF_DEF *pLPF, int16_t Input);
#endif
