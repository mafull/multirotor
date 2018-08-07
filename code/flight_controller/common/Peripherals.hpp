#ifndef __PERIPHERALS_HPP
#define __PERIPHERALS_HPP

#include <vector>

#include "UART.hpp"

class Peripherals
{
    public:
        Peripherals();
        ~Peripherals();
        
        void addUART(const UART& uart)
        {
            //m_UARTs.push_back(uart);
        }

    protected:

    private:
        //std::vector<UART&> m_UARTs;
};

#endif  // __PERIPHERALS_HPP
