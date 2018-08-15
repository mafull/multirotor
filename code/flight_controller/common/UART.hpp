#ifndef __UART_HPP
#define __UART_HPP

#include "Peripheral.hpp"

class UART : public Peripheral
{
public:
    virtual void write() = 0;

protected:
    UART() :
        Peripheral(Peripheral_Type_UART)
    {        
    }
};

#endif  // __UART_HPP
