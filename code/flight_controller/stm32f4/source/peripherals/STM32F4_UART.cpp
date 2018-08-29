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

    // Ensure that the initialisation was successful
    ASSERT(_initialised);
}


#include <cstdint>
#include <string>
void STM32F4_UART::write(const std::string& data)
{
    ASSERT(_initialised);

    uint32_t timeout = 100;
    HAL_UART_Transmit(
        &_handle,
        reinterpret_cast<uint8_t *>(const_cast<char *>(data.c_str())),
        data.size(),
        timeout);
}
