#include "AppHeadFile.h"

/**
 * @brief      Tmu config function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void Hal_SetupTmu(void)
{
    TMU_SetUnlockForModule(HAL_TMU_OUTPUT);
    TMU_SetSourceForModule(HAL_TMU_INPUT, HAL_TMU_OUTPUT);
    TMU_ModuleCmd(HAL_TMU_OUTPUT, ENABLE);
    TMU_SetLockForModule(HAL_TMU_OUTPUT);
}