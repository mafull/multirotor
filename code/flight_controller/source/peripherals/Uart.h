#ifndef __UART_H
#define __UART_H


// Standard includes
#include <stdbool.h>


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 *
 */
typedef void (*Uart_Callback_Function_t)(char);

/**
 *
 */
typedef enum Uart_Instance_e
{
    Uart1 = 0u,
    Uart2,

    Uart_Instance_MAX
} Uart_Instance_t;


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool Uart_Initialise(Uart_Instance_t instance);

/**
 *
 */
bool Uart_IsInitialised(Uart_Instance_t instance);

/**
 *
 */
void Uart_SetCallback(Uart_Instance_t instance,
                      Uart_Callback_Function_t callback);

/**
 *
 */
bool Uart_Write(Uart_Instance_t instance, char *message);


#endif // __UART_H
