#ifndef __UART_H
#define __UART_H


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 *
 */
typedef enum UART_Instance_e
{
    UART_Instance_UART1 = 0u,
    UART_Instance_UART2,

    UART_Instance_MAX
} UART_Instance_t;


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool UART_Initialise(UART_Instance_t instance);

/**
 *
 */
bool UART_Write(UART_Instance_t instance, char *message);


#endif // __UART_H
