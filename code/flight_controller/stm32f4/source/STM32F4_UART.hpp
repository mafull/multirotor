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
    void write(const char *str);

protected:

private:
    bool _configured;
    UART_HandleTypeDef _handle;
};

#endif  // __STM32F4_UART_HPP
