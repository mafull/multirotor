#ifndef __HMC5883_L_HPP
#define __HMC5883_L_HPP

#include "imu/Magnetometer.hpp"
#include "peripherals/I2C.hpp"

class HMC5883L : public Magnetometer
{
public:
    HMC5883L(I2C& i2c);
    ~HMC5883L();
    
    void initialise();
    void update();
    
protected:

private:
    I2C& _i2c;
};

#endif  // __HMC5883_L_HPP
