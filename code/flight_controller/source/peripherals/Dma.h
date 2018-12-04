#ifndef __DMA_H
#define __DMA_H


// --- Standard includes ---
#include <stdbool.h>


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 *
 */
typedef void (*Dma_TransferCompleteCallback_t)(void);

/**
 *
 */
typedef void (*Dma_TransferErrorCallback_t)(void);

/**
 *
 */
typedef enum Dma_Instance_e
{
    // Dma1_5 = 0u,    // I2C1 Rx
    // Dma1_6,         // I2C1 Tx
    Dma2_7,         // USART1 Tx

    Dma_Instance_MAX
} Dma_Instance_t;


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool Dma_Initialise(void);

/**
 *
 */
bool Dma_IsInitialised(void);

/**
 *
 */
void Dma_SetTransferCompleteCallback(Dma_Instance_t instance,
                                     Dma_TransferCompleteCallback_t callback);

/**
 *
 */
void Dma_SetTransferErrorCallback(Dma_Instance_t instance,
                                  Dma_TransferCompleteCallback_t callback);



#endif // __DMA_H
