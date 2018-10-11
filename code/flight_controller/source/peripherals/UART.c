// --- Public header ---
#include "peripherals/UART.h"

// --- Private header ---
#define UART_PRIVATE
    #include "peripherals/UART_private.h"
#undef UART_PRIVATE

// Standard includes
#include <string.h>


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool UART_Initialise(UART_Instance_t instance)
{
    ENSURE(instance < UART_Instance_MAX);

    UART_Handle_t *const handle = &UART_handles[(uint8_t)instance];

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
                              strlen(message),
                              UART_TRANSMIT_TIMEOUT) == HAL_OK);
}
