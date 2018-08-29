#ifndef __MAGNETOMETER_HPP
#define __MAGNETOMETER_HPP

#include "peripherals/I2C.hpp"

using Magnetometer_Data_t =
    struct Magnetometer_Data_t
    {
        bool isFilled;
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
