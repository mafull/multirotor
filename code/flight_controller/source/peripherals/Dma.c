// --- Public header ---
#include "peripherals/Dma.h"

// --- Private header ---
#define DMA_PRIVATE
    #include "peripherals/Dma_private.h"
#undef DMA_PRIVATE


// --- Project includes ---
#include "macros.h"


/******************************************************************************
  Private Data
 ******************************************************************************/

DMA_HandleTypeDef Dma_handles[Dma_Instance_MAX] = { 0 };

bool Dma_isInitialised = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool Dma_Initialise(void)
{
    ENSURE(!Dma_isInitialised);

    bool success = true;
    for (uint8_t i = 0; success && (i < Dma_Instance_MAX); i++)
    {
        const Dma_ConfigData_t *const conf = &Dma_configData[i];
        DMA_HandleTypeDef *const handle = &Dma_handles[i];

        Dma_EnableDmaClock(conf->halInstance);

        handle->Instance = conf->halInstance;
        handle->Init = conf->initStruct;
        success = (HAL_DMA_Init(handle) == HAL_OK);

        // @todo: CHANGE
        HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 6u, 0);
        HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
    }

    Dma_isInitialised = success;
    return Dma_isInitialised;
}


bool Dma_IsInitialised(void)
{
    return Dma_isInitialised;
}

void Dma_SetTransferCompleteCallback(Dma_Instance_t instance,
                                     Dma_TransferCompleteCallback_t callback)
{
    ENSURE(instance < Dma_Instance_MAX);
    ENSURE(callback);

    // @todo: Do this
    LOG_ERROR("HAVEN'T IMPLEMENTED SETTING TRANSFER COMPLETE CALLBACK YET");
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

void Dma_EnableDmaClock(DMA_Stream_TypeDef *instance)
{
    ENSURE(instance);

    if (        (instance == DMA1_Stream0)
             || (instance == DMA1_Stream1)
             || (instance == DMA1_Stream2)
             || (instance == DMA1_Stream3)
             || (instance == DMA1_Stream4)
             || (instance == DMA1_Stream5)
             || (instance == DMA1_Stream6)
             || (instance == DMA1_Stream7))
    {
        __DMA1_CLK_ENABLE();
    }
    else if (   (instance == DMA2_Stream0)
             || (instance == DMA2_Stream1)
             || (instance == DMA2_Stream2)
             || (instance == DMA2_Stream3)
             || (instance == DMA2_Stream4)
             || (instance == DMA2_Stream5)
             || (instance == DMA2_Stream6)
             || (instance == DMA2_Stream7))
    {
        __DMA2_CLK_ENABLE();
    }
    else
    {
        UNREACHABLE();
    }
}


DMA_HandleTypeDef *const Dma_GetHandle(Dma_Instance_t instance)
{
    ENSURE(instance < Dma_Instance_MAX);
    ENSURE(Dma_isInitialised);

    return &Dma_handles[instance];
}


/******************************************************************************
  Callback Functions
 ******************************************************************************/

void DMA2_Stream7_IRQHandler(void)
{
    HAL_DMA_IRQHandler(&Dma_handles[0]);
}
