// Incorrect usage guard
#ifndef DMA_PRIVATE
    #error Private interface should not be included here!
#endif // DMA_PRIVATE

#ifndef __DMA_PRIVATE_H
#define __DMA_PRIVATE_H


// --- Public header ---
#include "peripherals/Dma.h"

// --- Library includes ---
#include "stm32f4xx_hal.h"


/******************************************************************************
  Private Defines
 ******************************************************************************/


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 *
 */
typedef struct Dma_ConfigData_s
{
    DMA_Stream_TypeDef *halInstance;
    DMA_InitTypeDef initStruct;
} Dma_ConfigData_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern const Dma_ConfigData_t Dma_configData[Dma_Instance_MAX];

/**
 *
 */
extern DMA_HandleTypeDef Dma_handles[Dma_Instance_MAX];

/**
 *
 */
extern bool Dma_isInitialised;


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */
void Dma_EnableDmaClock(DMA_Stream_TypeDef *instance);

/**
 *
 */
DMA_HandleTypeDef *const Dma_GetHandle(Dma_Instance_t instance);


#endif // __DMA_PRIVATE_H
