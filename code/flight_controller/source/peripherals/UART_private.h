// 
#ifndef UART_PRIVATE
    #error Private interface should not be included here!
#endif // UART_PRIVATE

#ifndef __UART_PRIVATE_H
#define __UART_PRIVATE_H


// --- Public header ---
#include "peripherals/UART.h"

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
typedef struct UART_Handle_s
{
    UART_Instance_t instance;
    bool initialised;

    UART_HandleTypeDef halHandle;
} UART_Handle_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern UART_Handle_t UART_handles[UART_Instance_MAX];


#endif // __UART_PRIVATE_H
