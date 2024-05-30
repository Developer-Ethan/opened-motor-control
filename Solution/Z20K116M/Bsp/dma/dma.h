#ifndef _DMA_H
#define _DMA_H

#include "Z20K11xM_drv.h"
/**
 * @brief      Clear DMA int flag function.
 *
 * @param[in]  None.
 *
 * @return     None.
 *
 */
__ramfunc static inline void Hal_ClearDMAINT(void)
{
    dma_reg_w_t *DMAW = (dma_reg_w_t *)(DMA_BASE_ADDR);
    DMAW->DMA_GCC = 0x00808000U; // todo 0x00808080U
}

uint8_t Hal_SetupDma(isr_cb_t *DMADoneCbf);
#endif