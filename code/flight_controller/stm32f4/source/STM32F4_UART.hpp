#ifndef __STM32_F4_UART_HPP
#define __STM32_F4_UART_HPP

#include "UART.hpp"

class STM32F4_UART : public UART
{
    public:
        STM32F4_UART();
        ~STM32F4_UART();
        
        void write();
    protected:

    private:

};

#endif  // __STM32_F4_UART_HPP
