#include "MPU6050.hpp"

#define MPU6050_I2C_DEVICE_ADDRESS          0x68
#define MPU6050_I2C_MEMORY_ADDRESS_DATA     0x3B

static int16_t int16FromTwoUint8(uint8_t& high, uint8_t low)
{
    return static_cast<int16_t>((high << 8) | low);
}

MPU6050::MPU6050() :
    accelerometer(*this),
    gyroscope(*this),
    _i2c(nullptr),
    _rawData()
{

}

MPU6050::~MPU6050()
{

}

void MPU6050::update()
{
    // 
    if (!readFromDevice())
    {
        return;
    }

    accelerometer._data.x = int16FromTwoUint8(_rawData[0], _rawData[1]);
    accelerometer._data.y = int16FromTwoUint8(_rawData[2], _rawData[3]);
    accelerometer._data.z = int16FromTwoUint8(_rawData[4], _rawData[5]);

    //     // MPU6050_Data_Raw.temperature = (float)((float)((int16_t)((tmp[6] << 8) | tmp[7])) / (float)340.0f + (float)36.53f);

    gyroscope._data.x = int16FromTwoUint8( _rawData[8],  _rawData[9]);
    gyroscope._data.y = int16FromTwoUint8(_rawData[10], _rawData[11]);
    gyroscope._data.z = int16FromTwoUint8(_rawData[12], _rawData[13]);
}

bool MPU6050::readFromDevice()
{
    ASSERT(_i2c);

    // ADD CHECK FOR MAXIMUM READ RATE (e.g. read acc then gyro instantly)
    bool newData = true;
    
    _i2c->readMemory(
        MPU6050_I2C_DEVICE_ADDRESS,
        MPU6050_I2C_MEMORY_ADDRESS_DATA,
        _rawData,
        14);

    return newData;
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
    _parent.update();
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
    _parent.update();
}
