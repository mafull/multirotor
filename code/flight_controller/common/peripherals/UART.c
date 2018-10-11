// Public include
#include "UART.h"

// Private include
#define __UART_C
#include "UART_private.h"
#undef __UART_C


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool UART_Write(UART_Instance_t instance, uint8_t *data)
{
    UART_Handle_t hUART = UART_handles[(uint8_t)instance];

    HAL_UART_Transmit(hUART,
                      );
}