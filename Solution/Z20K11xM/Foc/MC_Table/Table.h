#ifndef _TABLE_H_
#define _TABLE_H_
#include "stdint.h"

#define SIZE_SIN_COS (1024)
extern const uint16_t Table_Arctan[1025];
extern const uint16_t Table_Amp[];
extern const uint16_t Table_Sin60[];
extern const uint16_t Table_Sqrt[];
extern const int16_t Table_Sin[SIZE_SIN_COS + (SIZE_SIN_COS / 4u)];
extern const int16_t *pTable_Cos;
#endif // !_TABLE_H_
