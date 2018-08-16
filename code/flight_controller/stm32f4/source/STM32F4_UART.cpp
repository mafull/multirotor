#include "STM32F4_UART.hpp"

STM32F4_UART::STM32F4_UART() :
    _configured(false)
{
    // Do nothing
}

void STM32F4_UART::setConfiguration(USART_TypeDef *instance, UART_InitTypeDef& init)
{
    // Ensure it is not already initialised
    ASSERT(!_initialised);

    // Store the configuration in the handle
    _handle.Instance = instance;
    _handle.Init = init;

    _configured = true;
}

void STM32F4_UART::initialise()
{
    // Ensure it is configured but not already initialised
    ASSERT(_configured && !_initialised);

    // Attempt to initialise the UART peripheral
    _initialised = (HAL_UART_Init(&_handle) == HAL_OK);

    // Ensure that the initialsation was successful
    ASSERT(_initialised);
}
#include <string.h>
void STM32F4_UART::write(const char *str)
{
    ASSERT(_initialised);

    // uint8_t *pData;
    // uint16_t size = 0;
    uint32_t timeout = 100;
    HAL_UART_Transmit(&_handle, (uint8_t *)str, strlen(str), timeout);
}
