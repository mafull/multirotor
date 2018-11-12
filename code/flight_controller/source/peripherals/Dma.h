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
typedef enum Dma_Instance_e
{
    Dma2_7 = 0u,

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


#endif // __DMA_H
