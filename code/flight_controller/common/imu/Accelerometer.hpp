#ifndef __ACCELEROMETER_HPP
#define __ACCELEROMETER_HPP

#include "peripherals/I2C.hpp"

using Accelerometer_Data_Element_t = float;

using Accelerometer_Data_t =
    struct Accelerometer_Data_t
    {
        Accelerometer_Data_Element_t x;
        Accelerometer_Data_Element_t y;
        Accelerometer_Data_Element_t z;
    };


class Accelerometer
{
public:
    Accelerometer();
    ~Accelerometer();

    virtual void initialise() = 0;

    const Accelerometer_Data_t& getData() const
    {
        return _data;
    }

    void setI2C(I2C *i2c)
    {
        ASSERT(i2c);
        _i2c = i2c;
    }

protected:

private:
    I2C *_i2c;

    Accelerometer_Data_t _data;
};

#endif  // __ACCELEROMETER_HPP
