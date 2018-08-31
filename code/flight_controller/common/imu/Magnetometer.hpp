#ifndef __MAGNETOMETER_HPP
#define __MAGNETOMETER_HPP

#include "peripherals/I2C.hpp"

using Magnetometer_Data_Element_t = float;

using Magnetometer_Data_t =
    struct Magnetometer_Data_t
    {
        Magnetometer_Data_Element_t x;
        Magnetometer_Data_Element_t y;
        Magnetometer_Data_Element_t z;
    };

class Magnetometer
{
public:
    Magnetometer();
    ~Magnetometer();
    
    void setI2C(I2C *i2c)
    {
        ASSERT(i2c);
        _i2c = i2c;
    }

    void initialise();

    const Magnetometer_Data_t& getData() const
    {
        return _data;
    }

protected:

private:
    I2C *_i2c;

    Magnetometer_Data_t _data;
};

#endif  // __MAGNETOMETER_HPP
