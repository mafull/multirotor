#ifndef __STM32_F4_UART_HPP
#define __STM32_F4_UART_HPP

#include "UART.hpp"

#include "stm32f4xx.h"

class STM32F4_UART : public UART
{
public:
    STM32F4_UART(USART_TypeDef *instance);
//    ~STM32F4_UART();
    
    void initialise(UART_InitTypeDef& init);
    
    void write();

protected:

private:
    UART_HandleTypeDef m_handle;
};

#endif  // __STM32_F4_UART_HPP
