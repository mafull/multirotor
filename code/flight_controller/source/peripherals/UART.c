// --- Public header ---
#include "peripherals/UART.h"

// --- Private header ---
#define UART_PRIVATE
    #include "peripherals/UART_private.h"
#undef UART_PRIVATE

// Standard includes
#include <string.h>


#define ENSURE(x) // @todo: Implement externally


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool UART_Initialise(UART_Instance_t instance)
{
    ENSURE(instance < UART_Instance_MAX);

    UART_Handle_t *const handle = &UART_handles[(uint8_t)instance];

    ENSURE(instance == handle->instance);
    ENSURE(!handle->initialised);

    handle->initialised = (HAL_UART_Init(&handle->halHandle) == HAL_OK);

    return handle->initialised;
}


bool UART_Write(UART_Instance_t instance, char *message)
{
    ENSURE(instance < UART_Instance_MAX);

    UART_Handle_t *const handle = &UART_handles[(uint8_t)instance]; // @todo: Maybe make this a macro

    ENSURE(handle->initialised);

    return (HAL_UART_Transmit(&handle->halHandle,
                              (uint8_t *)message,
                              strnlen(message, 128), // @todo: Add max length define
                              UART_TRANSMIT_TIMEOUT) == HAL_OK);
}



void HAL_MspInit(void)
{
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    /* System interrupt init*/
    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if(huart->Instance==USART1)
    {
        __USART1_CLK_ENABLE();
        __GPIOA_CLK_ENABLE(); // @todo: Make this dependent on port
  
        GPIO_InitStruct.Pin         = GPIO_PIN_10;
        GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull        = GPIO_NOPULL;
        GPIO_InitStruct.Speed       = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate   = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin         = GPIO_PIN_9;
        GPIO_InitStruct.Alternate   = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        HAL_NVIC_SetPriority(USART1_IRQn, 1, 1);
        HAL_NVIC_EnableIRQ(USART1_IRQn);

        // @todo: Add to class? Like enabling EXTI for button press
        __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
    }
}
