#include "IMU.hpp"

IMU::IMU() :
    _configured(false),
    _initialised(false),
    // Peripherals
    _accelerometer(nullptr),
    _gyroscope(nullptr),
    _magnetometer(nullptr)
{

}

IMU::~IMU()
{

}

void IMU::setConfiguration(I2C *i2c)
{
    ASSERT(i2c);

    // Ensure it is not already initialised
    ASSERT(!_initialised);

    // Ensure the required peripherals have been added
    ASSERT(_accelerometer && _gyroscope && _magnetometer);

    // Pass the I2C handle to the peripherals
    _accelerometer->setI2C(i2c);
    _gyroscope->setI2C(i2c);
    _magnetometer->setI2C(i2c);

    _configured = true;
}

void IMU::initialise()
{
    // Ensure it is configured but not already initialised
    ASSERT(_configured && !_initialised);

    // Initialise the peripherals
    _accelerometer->initialise();
    _gyroscope->initialise();
    _magnetometer->initialise();

    _initialised = true;
}
