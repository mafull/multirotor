// 
#ifndef UART_PRIVATE
    #error Private interface should not be included here!
#endif // UART_PRIVATE

#ifndef __UART_PRIVATE_H
#define __UART_PRIVATE_H


// --- Public header ---
#include "UART.h"

// --- Library includes ---
#include "stm32f4xx.h"


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
