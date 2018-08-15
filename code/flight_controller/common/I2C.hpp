#ifndef __I2C_HPP
#define __I2C_HPP

#include "Peripheral.hpp"

class I2C : public Peripheral
{
public:
    
protected:
    I2C() :
        Peripheral(Peripheral_Type_I2C)
    {        
    }
};

#endif  // __I2C_HPP
