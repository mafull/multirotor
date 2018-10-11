// --- Public header ---
#include "UART.h"

// --- Private header ---
#define UART_PRIVATE
    #include "UART_private.h"
#undef UART_PRIVATE

// Standard includes
#include <string.h>


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool UART_Initialise(UART_Instance_t instance)
{
    ENSURE(instance < UART_Instance_MAX);

    UART_HandleTypeDef *halHandle = &UART_handles[(uint8_t)instance].halHandle; // @todo: Maybe make this a macro

    return (HAL_UART_Init(halHandle) == HAL_OK);
}


bool UART_Write(UART_Instance_t instance, char *message)
{
    ENSURE(instance < UART_Instance_MAX);

    UART_HandleTypeDef *halHandle = &UART_handles[(uint8_t)instance].halHandle; // @todo: Maybe make this a macro
    uint8_t *data = (uint8_t)message;
    uint16_t length = strlen(message);

    return (HAL_UART_Transmit(halHandle, data, length) == HAL_OK);
}
