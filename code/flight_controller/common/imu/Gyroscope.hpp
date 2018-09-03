#ifndef __GYROSCOPE_HPP
#define __GYROSCOPE_HPP

#include "peripherals/I2C.hpp"

using Gyroscope_Data_Element_t = float;

using Gyroscope_Data_t =
    struct Gyroscope_Data_t
    {
        Gyroscope_Data_Element_t x;
        Gyroscope_Data_Element_t y;
        Gyroscope_Data_Element_t z;
    };

class Gyroscope
{
public:
    Gyroscope();
    ~Gyroscope();
    
    virtual void initialise() = 0;
    virtual void update() = 0;

    const Gyroscope_Data_t& getData() const
    {
        return _data;
    }

    void setI2C(I2C *i2c)
    {
        ASSERT(i2c);
        _i2c = i2c;
    }

protected:
    I2C *_i2c;

    Gyroscope_Data_t _data;
    
private:

};

#endif  // __GYROSCOPE_HPP
