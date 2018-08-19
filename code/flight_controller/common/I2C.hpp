#ifndef __I2C_HPP
#define __I2C_HPP

#include "Peripheral.hpp"

#include <cstdint>

typedef uint16_t I2C_Address_t;

class I2C : public Peripheral
{
public:
    virtual void writeMemory(
        I2C_Address_t deviceAddress,
        I2C_Address_t memoryAddress,
        uint8_t *data,
        uint8_t amount) = 0;
    virtual void readMemory(
        I2C_Address_t deviceAddress,
        I2C_Address_t memoryAddress,
        uint8_t *data,
        uint8_t amount) = 0;

protected:
    I2C() :
        Peripheral(Peripheral_Type_I2C)
    {
    }
};

#endif  // __I2C_HPP
