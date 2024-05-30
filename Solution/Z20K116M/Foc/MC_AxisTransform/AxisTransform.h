#ifndef _AXISTRANSFORM_H_
#define _AXISTRANSFORM_H_
#include "stdint.h"
#include "CurrSample.h"
typedef struct
{
    int16_t Real;
    int16_t Imag;
    /* data */
} AXIS_DEF;

AXIS_DEF ClarkeTransform(PHASE_CURR_DEF *pPhaseCurr);
AXIS_DEF ParkTransform(AXIS_DEF *pAxis, uint16_t ElecAngle);
AXIS_DEF iParkTransform(AXIS_DEF *pAxis, uint16_t ElecAngle);
#endif
