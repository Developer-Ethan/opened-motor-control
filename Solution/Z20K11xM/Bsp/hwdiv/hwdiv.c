#include "AppHeadFile.h"

/**
 * @brief      HWDIV Config function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
void HAL_setupHwdiv()
{
    /* Enable HWDIV module */
    SYSCTRL_EnableModule(SYSCTRL_HWDIV);
    /* Init HWDIV module set signed divide DZE=0*/
    HWDIV_Init();
    /* Enable the Divider Fast Start Mode */
    HWDIV_DisableDivFastStart(DISABLE);
}