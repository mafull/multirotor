// --- Public header ---
#include "peripherals/Uart.h"

// --- Private header ---
#define UART_PRIVATE
    #include "peripherals/Uart_private.h"
#undef UART_PRIVATE

// --- Project includes ---
#include "macros.h"
#include "peripherals/Gpio.h"

// Standard includes
#include <string.h>


/******************************************************************************
  Private Data
 ******************************************************************************/

UART_HandleTypeDef Uart_handles[Uart_Instance_MAX];

bool Uart_isInitialised = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool Uart_Initialise(void)
{
    ENSURE(!Uart_isInitialised);


    ENSURE(Gpio_IsInitialised()); // @todo: Maybe make this the ret value, don't assert?

    bool success = true;
    for (uint8_t i = 0; success && (i < Uart_Instance_MAX); i++)
    {
        const Uart_ConfigData_t *const conf = &Uart_configData[i];
        UART_HandleTypeDef *const handle = &Uart_handles[i];

        // Link RX DMA
        if (conf->dmaInstanceRx != Dma_Instance_MAX)
        {
            DMA_HandleTypeDef *const dmaHandleRx = Dma_GetHandle(conf->dmaInstanceRx);
            ENSURE(dmaHandleRx);
            __HAL_LINKDMA(handle, hdmarx, *dmaHandleRx);
        }

        // Link TX DMA
        if (conf->dmaInstanceTx != Dma_Instance_MAX)
        {
            DMA_HandleTypeDef *const dmaHandleTx = Dma_GetHandle(conf->dmaInstanceTx);
            ENSURE(dmaHandleTx);
            __HAL_LINKDMA(handle, hdmatx, *dmaHandleTx);
        }

        // Configure the interrupt handler
        IRQn_Type irqn = Uart_GetUartInterruptNumber(conf->halInstance);
        HAL_NVIC_SetPriority(irqn, 0, 0); // @todo: Configurable priorities
        HAL_NVIC_EnableIRQ(irqn);

        // Enable the RXNE interrupt
        // __HAL_UART_ENABLE_IT(handle, UART_IT_RXNE);
        __HAL_UART_ENABLE_IT(handle, UART_IT_TC);
        __HAL_UART_ENABLE_IT(handle, UART_IT_ERR);

        Uart_EnableUartClock(conf->halInstance);

        // Attempt to initialise the UART peripheral itself
        handle->Instance = conf->halInstance;
        handle->Init = conf->initStruct;
        success = (HAL_UART_Init(handle) == HAL_OK);
    }

    Uart_isInitialised = success;
    return Uart_isInitialised;
}


bool Uart_IsInitialised(void)
{
    return Uart_isInitialised;
}


// void Uart_SetCallback(Uart_Instance_t instance, Uart_CallbackFunction_t callback)
// {
//     ENSURE(instance < Uart_Instance_MAX);
//     ENSURE(callback);

//     Uart_handles[(uint8_t)instance].callback = callback;
// }


bool Uart_Write(Uart_Instance_t instance, char *message)
{
    ENSURE(instance < Uart_Instance_MAX);
    ENSURE(message);
    ENSURE(Uart_isInitialised);

    UART_HandleTypeDef *const handle = &Uart_handles[instance]; // @todo: Maybe make this a macro

    // Attempt to send the message
    return (HAL_UART_Transmit(handle,
                              (uint8_t *)message,
                              strnlen(message, 128u), // @todo: Add max length define
                              UART_TRANSMIT_TIMEOUT) == HAL_OK);
}

bool Uart_WriteDMA(Uart_Instance_t instance, char *message)
{
    ENSURE(instance < Uart_Instance_MAX);
    ENSURE(message);
    ENSURE(Uart_isInitialised);

    UART_HandleTypeDef *const handle = &Uart_handles[instance]; // @todo: Maybe make this a macro

    static char tmp[128] = "";
    strncpy(tmp, message, 128);

    // Attempt to send the message
    return (HAL_UART_Transmit_DMA(handle,
                                  (uint8_t *)tmp,
                                  strnlen(tmp, 128u)) == HAL_OK);
}


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

void Uart_EnableUartClock(USART_TypeDef *instance)
{
    ENSURE(instance);

    if      (instance == USART1)    __HAL_RCC_USART1_CLK_ENABLE();
    else if (instance == USART2)    __HAL_RCC_USART2_CLK_ENABLE();
    else if (instance == USART3)    __HAL_RCC_USART3_CLK_ENABLE();
    else if (instance == UART4)      __HAL_RCC_UART4_CLK_ENABLE();
    else if (instance == UART5)      __HAL_RCC_UART5_CLK_ENABLE();
    else if (instance == USART6)    __HAL_RCC_USART6_CLK_ENABLE();
    else                            UNREACHABLE();
}


IRQn_Type Uart_GetUartInterruptNumber(USART_TypeDef *instance)
{
    ENSURE(instance);

    IRQn_Type irqn;
    if      (instance == USART1)    irqn = USART1_IRQn;
    else if (instance == USART2)    irqn = USART2_IRQn;
    else if (instance == USART3)    irqn = USART3_IRQn;
    else if (instance == UART4)     irqn = UART4_IRQn;
    else if (instance == UART5)     irqn = UART5_IRQn;
    else if (instance == USART6)    irqn = USART6_IRQn;
    else                            UNREACHABLE();

    return irqn;
}


/******************************************************************************
  Callback Functions
 ******************************************************************************/

void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&Uart_handles[0]);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    ENSURE(huart);

    // Find the relevant handle
    // Uart_Handle_t *handle = NULL;
    // for (uint8_t i = 0u; i < Uart_Instance_MAX; i++)
    // {
    //     handle = &Uart_handles[i];
    //     if (handle->halHandle.Instance != huart->Instance)
    //     {
    //         handle = NULL;
    //         continue;
    //     }
    // }
    // ENSURE(handle);

    // if (!handle->callback)
    // {
    //     handle->callback(handle->halHandle.Instance->DR);
    // }
}

#include "peripherals/DigitalOutput.h"
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    DigitalOutput_ToggleState(AssertLed);
}


void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart)
{

}


void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

}