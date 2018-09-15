#include "HMC5883L.hpp"

HMC5883L::HMC5883L(I2C& i2c) :
    // Base constructors
    Magnetometer(),
    // Private members
    _i2c(i2c)
{

}

HMC5883L::~HMC5883L()
{

}

void HMC5883L::initialise()
{

}

void HMC5883L::update()
{

}