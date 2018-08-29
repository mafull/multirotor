#ifndef __GYROSCOPE_HPP
#define __GYROSCOPE_HPP

#include "peripherals/I2C.hpp"

using Gyroscope_Data_t =
    struct Gyroscope_Data_t
    {
        bool isFilled;
    };

class Gyroscope
{
public:
    Gyroscope();
    ~Gyroscope();
    
    void setI2C(I2C *i2c)
    {
        ASSERT(i2c);
        _i2c = i2c;
    }
    
    void initialise();

    const Gyroscope_Data_t& getData() const
    {
        return _data;
    }

protected:

private:
    I2C *_i2c;

    Gyroscope_Data_t _data;
};

#endif  // __GYROSCOPE_HPP
