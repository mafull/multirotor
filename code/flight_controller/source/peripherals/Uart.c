// --- Public header ---
#include "peripherals/Uart.h"

// --- Private header ---
#define UART_PRIVATE
    #include "peripherals/Uart_private.h"
#undef UART_PRIVATE

// --- Project includes ---
#include "macros.h"

// Standard includes
#include <string.h>


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool Uart_Initialise(Uart_Instance_t instance)
{
    ENSURE(instance < Uart_Instance_MAX);

    // Get the relevant handle
    Uart_Handle_t *const handle = &Uart_handles[(uint8_t)instance];

    // Ensure its instance is configured correctly and it's not initialised
    ENSURE(instance == handle->instance);
    ENSURE(!handle->initialised);

    // Initialise rx and tx pins
    Uart_EnablePortClock(handle->rxPort);
    Uart_EnablePortClock(handle->txPort);
    HAL_GPIO_Init(handle->rxPort, &handle->rxInitStruct);
    HAL_GPIO_Init(handle->txPort, &handle->txInitStruct);

    // Configure the interrupt handler
    IRQn_Type irqn = Uart_GetUartInterruptNumber(handle->halHandle.Instance);
    HAL_NVIC_SetPriority(irqn, 1u, 1u); // @todo: Configurable priorities
    HAL_NVIC_EnableIRQ(irqn);

    // Enable the RXNE interrupt
    __HAL_UART_ENABLE_IT(&handle->halHandle, UART_IT_RXNE);

    // Attempt to initialise the UART peripheral itself
    Uart_EnableUartClock(handle->halHandle.Instance);
    handle->initialised = (HAL_UART_Init(&handle->halHandle) == HAL_OK);

    return handle->initialised;
}


bool Uart_IsInitialised(Uart_Instance_t instance)
{
    ENSURE(instance < Uart_Instance_MAX);
    return Uart_handles[(uint8_t)instance].initialised;
}


void Uart_SetCallback(Uart_Instance_t instance, Uart_CallbackFunction_t callback)
{
    ENSURE(instance < Uart_Instance_MAX);
    ENSURE(callback);

    Uart_handles[(uint8_t)instance].callback = callback;
}


bool Uart_Write(Uart_Instance_t instance, char *message)
{
    ENSURE(instance < Uart_Instance_MAX);

    // Get the relevant handle and ensure it is initialised
    Uart_Handle_t *const handle = &Uart_handles[(uint8_t)instance]; // @todo: Maybe make this a macro
    ENSURE(handle->initialised);

    // Attempt to send the message
    return (HAL_UART_Transmit(&handle->halHandle,
                              (uint8_t *)message,
                              strnlen(message, 128u), // @todo: Add max length define
                              UART_TRANSMIT_TIMEOUT) == HAL_OK);
}


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

void Uart_EnablePortClock(GPIO_TypeDef *port)
{
    ENSURE(port);

    if      (port == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    else if (port == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    else if (port == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    else if (port == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
    else if (port == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();
    else if (port == GPIOF) __HAL_RCC_GPIOF_CLK_ENABLE();
    else if (port == GPIOG) __HAL_RCC_GPIOG_CLK_ENABLE();
    else if (port == GPIOH) __HAL_RCC_GPIOH_CLK_ENABLE();
    else                    UNREACHABLE();
}

void Uart_EnableUartClock(USART_TypeDef *instance)
{
    ENSURE(instance);

    if      (instance == USART1)    __USART1_CLK_ENABLE();
    else if (instance == USART2)    __USART2_CLK_ENABLE();
    else if (instance == USART3)    __USART3_CLK_ENABLE();
    else if (instance == UART4)      __UART4_CLK_ENABLE();
    else if (instance == UART5)      __UART5_CLK_ENABLE();
    else if (instance == USART6)    __USART6_CLK_ENABLE();
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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    ENSURE(huart);

    // Find the relevant handle
    Uart_Handle_t *handle = NULL;
    for (uint8_t i = 0u; i < Uart_Instance_MAX; i++)
    {
        handle = &Uart_handles[i];
        if (handle->halHandle.Instance != huart->Instance)
        {
            handle = NULL;
            continue;
        }
    }
    ENSURE(handle);

    if (!handle->callback)
    {
        handle->callback(handle->halHandle.Instance->DR);
    }
}
