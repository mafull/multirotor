#ifndef __PERIPHERAL_HPP
#define __PERIPHERAL_HPP

#include "Assert.hpp"

typedef enum Peripheral_Type_t
{
    Peripheral_Type_None = 0,

    Peripheral_Type_DigitalInput,
    Peripheral_Type_DigitalOutput,
    Peripheral_Type_I2C,
    Peripheral_Type_PWMInput,
    Peripheral_Type_PWMOutput,
    Peripheral_Type_UART,

    Peripheral_Type_MAX
} Peripheral_Type_t;


class Peripheral
{
public:
    virtual void initialise() = 0;
    virtual bool isInitialised() { return _initialised; }

protected:
    Peripheral(Peripheral_Type_t type) :
        _initialised(false),
        _type(type)
    {
    }
    
    bool _initialised;
    Peripheral_Type_t _type;
};

#endif  // __PERIPHERAL_HPP
