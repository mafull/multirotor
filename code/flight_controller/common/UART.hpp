#ifndef __UART_HPP
#define __UART_HPP

#include "Peripheral.hpp"

class UART : public Peripheral
{
public:
    virtual void write() = 0;
};

#endif  // __UART_HPP
