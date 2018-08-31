#include "MPU6050.hpp"

#define MPU6050_I2C_DEVICE_ADDRESS 0x68


MPU6050::MPU6050() :
    accelerometer(*this),
    gyroscope(*this)
{

}

MPU6050::~MPU6050()
{

}

const uint8_t bytesToRead = 14;
uint8_t data[bytesToRead];

void MPU6050::update(
    Accelerometer_Data_t *accelerometerData,
    Gyroscope_Data_t *gyroscopeData)
{
    readFromDevice();

    if (accelerometerData)
    {
        accelerometerData->x = data[1];
    }

    if (gyroscopeData)
    {

    }
}

void MPU6050::readFromDevice()
{
    ASSERT(_i2c);

    // ADD CHECK FOR MAXIMUM READ RATE (e.g. read acc then gyro instantly)

    
    _i2c->readMemory(
        MPU6050_I2C_DEVICE_ADDRESS,
        0x3B, // MPU6050_I2C_MEMORY_ADDRESS_data
        data,
        14);


}






MPU6050::MPU6050_Accelerometer::MPU6050_Accelerometer(MPU6050& parent) :
    _parent(parent)
{

}

void MPU6050::MPU6050_Accelerometer::initialise()
{
    _parent.setI2C(_i2c);
}

void MPU6050::MPU6050_Accelerometer::update()
{
    _parent.readFromDevice();
}







MPU6050::MPU6050_Gyroscope::MPU6050_Gyroscope(MPU6050& parent) :
    _parent(parent)
{

}

void MPU6050::MPU6050_Gyroscope::initialise()
{
    _parent.setI2C(_i2c);
}

void MPU6050::MPU6050_Gyroscope::update()
{
    _parent.readFromDevice();
}