// --- Public header ---
#include "peripherals/Dma.h"

// --- Private header ---
#define DMA_PRIVATE
    #include "peripherals/Dma_private.h"
#undef DMA_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

const Dma_ConfigData_t Dma_configData[Dma_Instance_MAX] = 
    {
        /*

        */
        [Dma2_7] = { DMA2_Stream7, { DMA_CHANNEL_4, DMA_MEMORY_TO_PERIPH, DMA_PINC_DISABLE, DMA_MINC_ENABLE, DMA_PDATAALIGN_BYTE, DMA_MDATAALIGN_BYTE, DMA_NORMAL, DMA_PRIORITY_HIGH, DMA_FIFOMODE_DISABLE } },
    };