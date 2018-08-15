#include "STM32F4_UART.hpp"

STM32F4_UART::STM32F4_UART() :
    m_configured(false)
{
    // Do nothing
}

void STM32F4_UART::setConfiguration(USART_TypeDef *instance, UART_InitTypeDef& init)
{
    // Ensure it is not already initialised
    ASSERT(!m_initialised);

    // Store the configuration in the handle
    m_handle.Instance = instance;
    m_handle.Init = init;

    m_configured = true;
}

void STM32F4_UART::initialise()
{
    // Ensure it is configured but not already initialised
    ASSERT(m_configured && !m_initialised);

    // Attempt to initialise the UART peripheral
    m_initialised = (HAL_UART_Init(&m_handle) == HAL_OK);

    // Ensure that the initialsation was successful
    ASSERT(m_initialised);
}
#include <string.h>
void STM32F4_UART::write(const char *str)
{
    ASSERT(m_initialised);

    // uint8_t *pData;
    // uint16_t size = 0;
    uint32_t timeout = 100;
    HAL_UART_Transmit(&m_handle, (uint8_t *)str, strlen(str), timeout);
}
