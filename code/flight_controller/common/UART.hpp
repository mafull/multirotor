#ifndef __UART_HPP
#define __UART_HPP

#include "Peripheral.hpp"

#include <string>

class UART : public Peripheral
{
public:
    virtual void write(const std::string& data) = 0;

protected:
    UART() :
        Peripheral(Peripheral_Type_UART)
    {
    }
};

#endif  // __UART_HPP
