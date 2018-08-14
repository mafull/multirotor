#include "STM32F4_UART.hpp"

STM32F4_UART::STM32F4_UART(USART_TypeDef *instance)
{
    m_handle.Instance = instance;
}

//STM32F4_UART::~STM32F4_UART()
//{
//
//}


void STM32F4_UART::initialise(UART_InitTypeDef& init)
{
    m_handle.Init = init;
    //ASSERT(HAL_UART_Init(&m_handle) == HAL_OK);

    m_initialised = true;
}

void STM32F4_UART::write()
{
    ASSERT(m_initialised);

    uint8_t *pData;
    uint16_t size = 0;
    uint32_t timeout = 100;
    HAL_UART_Transmit(&m_handle, pData, size, timeout);
}
