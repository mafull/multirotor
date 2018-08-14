#ifndef __PERIPHERAL_HPP
#define __PERIPHERAL_HPP

#include "Assert.hpp"

class Peripheral
{
protected:
    Peripheral() :
        m_initialised(false)
    {

    }
    
    bool m_initialised;
};

#endif  // __PERIPHERAL_HPP
