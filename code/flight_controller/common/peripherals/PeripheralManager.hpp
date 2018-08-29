#ifndef __PERIPHERAL_MANAGER_HPP
#define __PERIPHERAL_MANAGER_HPP

#include "DigitalOutput.hpp"
#include "I2C.hpp"
#include "UART.hpp"

#include <cstdint>
#include <vector>

#define CREATE_PERIPHERAL_FUNCTIONS(upper, lower) \
    /* Function to store a pointer to the peripheral in a vector */ \
    void add##upper(upper *lower) { _##upper##s.push_back(lower); } \
    /* Function to return a reference to the peripheral */ \
    upper& lower(uint8_t idx) \
    { \
        ASSERT(idx < _##upper##s.size()); \
        return static_cast<upper&>(*_##upper##s[idx]); \
    }

#define CREATE_PERIPHERAL_VECTORS(upper, lower) \
    /* Vector to store pointers to added peripherals */ \
    std::vector<upper *> _##upper##s;

#define PERIPHERALS(MACRO) \
    MACRO(DigitalOutput, digitalOutput) \
    MACRO(I2C, i2c) \
    MACRO(UART, uart)

class PeripheralManager
{
public:
    PeripheralManager() {}

    PERIPHERALS(CREATE_PERIPHERAL_FUNCTIONS)
    
private:
    PERIPHERALS(CREATE_PERIPHERAL_VECTORS)
};

#undef CREATE_PERIPHERAL_FUNCTIONS
#undef CREATE_PERIPHERAL_VECTORS
#undef PERIPHERALS

#endif  // __PERIPHERAL_MANAGER_HPP
