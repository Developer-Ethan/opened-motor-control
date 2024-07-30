#include "AppHeadFile.h"

/**
 * @brief      DMA Config function.
 *
 * @param[in]  DMADoneCbf: done int Callback that will be registered for this channel.
 *
 * @return     None.
 *
 */
uint8_t Hal_SetupDma(isr_cb_t *DMADoneCbf)
{
    uint8_t McuFaultFlag;
    DMA_TransferConfig_t GtDMATransferConfig;
    /* Select DMA channel 0 transfer */
    GtDMATransferConfig.channel = DMA_CHANNEL0;
    /* Select ADC as the DMA request for channel 0 */
    GtDMATransferConfig.source = DMA_REQ_ADC0;
    /* DMA channel priority */
    GtDMATransferConfig.channelPriority = DMA_CHN_PRIORITY0;
    /* Unmask done interrupt */
    GtDMATransferConfig.doneIntMask = UNMASK;
    /* Mask error interrupt */
    GtDMATransferConfig.errorIntMask = MASK;

    /* Address pointing to the source data */
    GtDMATransferConfig.srcAddr = (uint32_t)HAL_ADC_DATA_ADDRESS;
    /* Address pointing to the destination data */
    GtDMATransferConfig.destAddr = (uint32_t)AdcMapData;
    /* Number of minor loop in a major loop: 1 */
    GtDMATransferConfig.minorLoopNum = 1U;
    /* Source address offset in minor loop */
    GtDMATransferConfig.minorLoopSrcOffset = 0;
    /* Destination address offset in minor loop */
    GtDMATransferConfig.minorLoopDestOffset = 4;
    /* Source address offset after a major loop done */
    GtDMATransferConfig.majorLoopSrcOffset = 0;
    /* Destination address offset after a major loop done */
    GtDMATransferConfig.majorLoopDestOffset = -20;

    /* Source data transfer size */
    GtDMATransferConfig.srcTransferSize = DMA_TRANSFER_SIZE_4B;
    /* Destination data transfer size */
    GtDMATransferConfig.destTransferSize = DMA_TRANSFER_SIZE_4B;
    /* Transfer bytes number */
    GtDMATransferConfig.transferByteNum = 20;
    /* Disable request after done control */
    GtDMATransferConfig.disableRequestAfterDoneCmd = DISABLE;
    /* DMA transfer Configure */
    if (ERR == DMA_ConfigTransfer(&GtDMATransferConfig))
    {
        McuFaultFlag = 1U;
    }
    else
    {
        McuFaultFlag = 0U;
    }

    DMA_InstallCallBackFunc(DMA_CHANNEL0, DMA_INT_DONE, DMADoneCbf);
    /* Enable dma channel request */
    DMA_ChannelRequestEnable(DMA_CHANNEL0);

    return McuFaultFlag;
}