#ifndef _DATACALC_H_
#define _DATACALC_H_
#include "stdint.h"
#include "Foc.h"
#define Q13(dat) (int16_t)(dat * 8192)
#define Q14(dat) (int16_t)(dat * 16384)
#define Q15(dat) (int16_t)(dat * 32767)
#define Q16(dat) (uint16_t)(dat * 65535)
#define SHIFT_15BITS (15u)
#define SHIFT_16BITS (16u)
#define DataMult_Q15(DATA1, DATA2) (int16_t)(((int32_t)(DATA1) * (int32_t)(DATA2)) >> (SHIFT_15BITS))
#define DataMult_Q16(DATA1, DATA2) (uint16_t)(((int32_t)(DATA1) * (int32_t)(DATA2)) >> (SHIFT_16BITS))

#define ABS(dat) ((dat) < 0) ? -(dat) : (dat)
int32_t Data_Limit(int32_t data, uint8_t bit);
uint16_t AngleAmp_Get(AXIS_DEF Axis, uint16_t *pAmp);
void BiasDetect(FOC_DEF *pFoc);

#endif // !DATACALC_H_
