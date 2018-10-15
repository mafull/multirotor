// 
#ifndef UART_PRIVATE
    #error Private interface should not be included here!
#endif // UART_PRIVATE

#ifndef __UART_PRIVATE_H
#define __UART_PRIVATE_H


// --- Public header ---
#include "peripherals/Uart.h"

// --- Library includes ---
// HAL_Driver
#include "stm32f4xx_hal.h"


/******************************************************************************
  Private Defines
 ******************************************************************************/

/**
 *
 */
#define UART_TRANSMIT_TIMEOUT   HAL_MAX_DELAY // @todo: Change this


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 *
 */
typedef struct Uart_Handle_s
{
    Uart_Instance_t instance;

    bool initialised;
    Uart_Callback_Function_t callback;

    UART_HandleTypeDef halHandle;

    GPIO_InitTypeDef rxInitStruct;
    GPIO_TypeDef *rxPort;
    GPIO_InitTypeDef txInitStruct;
    GPIO_TypeDef *txPort;
} Uart_Handle_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern Uart_Handle_t Uart_handles[Uart_Instance_MAX];


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 * Enable a GPIO port clock
 *
 * @param port The GPIO port whose clock is to be enabled
 */
void Uart_EnablePortClock(GPIO_TypeDef *port);

/**
 * Enable a UART peripheral clock
 *
 * @param instance The UART peripheral whose clock is to be enabled
 */
void Uart_EnableUartClock(USART_TypeDef *instance);

/**
 * Get the relevant interrupt number for the UART instance
 *
 * @param instance The UART peripheral whose interrupt number is required
 *
 * @return The interrupt number for the desired UART instance
 */
IRQn_Type Uart_GetUartInterruptNumber(USART_TypeDef *instance);


#endif // __UART_PRIVATE_H
