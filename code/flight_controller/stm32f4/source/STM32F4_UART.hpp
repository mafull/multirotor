#ifndef __STM32F4_UART_HPP
#define __STM32F4_UART_HPP

#include "UART.hpp"

#include "stm32f4xx.h"

class STM32F4_UART : public UART
{
public:
    STM32F4_UART();

    void setConfiguration(USART_TypeDef *instance, UART_InitTypeDef& init);
    
    void initialise();
    void write();

protected:

private:
    bool m_configured;
    UART_HandleTypeDef m_handle;
};

#endif  // __STM32F4_UART_HPP
