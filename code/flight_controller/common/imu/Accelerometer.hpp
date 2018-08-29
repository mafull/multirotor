#ifndef __ACCELEROMETER_HPP
#define __ACCELEROMETER_HPP

#include "peripherals/I2C.hpp"

using Accelerometer_Data_t =
    struct Accelerometer_Data_t
    {
        bool isFilled;
    };


class Accelerometer
{
public:
    Accelerometer();
    ~Accelerometer();

    void setI2C(I2C *i2c)
    {
        ASSERT(i2c);
        _i2c = i2c;
    }

    void initialise();

    const Accelerometer_Data_t& getData() const
    {
        return _data;
    }

protected:

private:
    I2C *_i2c;

    Accelerometer_Data_t _data;
};

#endif  // __ACCELEROMETER_HPP
