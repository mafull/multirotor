#include "MPU6050.hpp"

#define MPU6050_I2C_DEVICE_ADDRESS              0x68

#define MPU6050_I2C_MEMORY_ADDRESS_ACCEL_CONFIG 0x1C
#define MPU6050_I2C_MEMORY_ADDRESS_CONFIG       0x1A
#define MPU6050_I2C_MEMORY_ADDRESS_DATA         0x3B
#define MPU6050_I2C_MEMORY_ADDRESS_GYRO_CONFIG  0x1B
#define MPU6050_I2C_MEMORY_ADDRESS_PWR_MGMT_1   0x6B
#define MPU6050_I2C_MEMORY_ADDRESS_SMPLRT_DIV   0x19
#define MPU6050_I2C_MEMORY_ADDRESS_WHO_AM_I     0x75


static inline int16_t int16FromTwoUint8(uint8_t high, uint8_t low)
{
    return static_cast<int16_t>((high << 8) | low);
}

MPU6050::MPU6050(I2C& i2c) :
    // Public members
    accelerometer(*this),
    gyroscope(*this),
    // Private members
    _initialised(false),
    _i2c(i2c)
{

}

void MPU6050::initialise()
{
    ASSERT(!_initialised);

    ASSERT(initWhoAmI());
    ASSERT(initPowerManagement());
    ASSERT(initSampleRate());
    ASSERT(initConfig());
    ASSERT(initGyroscopeConfig());
    ASSERT(initAccelerometerConfig());

    _initialised = true;
}

bool MPU6050::readRawDataFromDevice()
{
    // @todo: Add check for maximum read rate (e.g. readring acc then gyro instantly)
    bool newData = true;
    
    _i2c.readMemory(MPU6050_I2C_DEVICE_ADDRESS,
                    MPU6050_I2C_MEMORY_ADDRESS_DATA,
                    _rawData,
                    14);

    return newData;
}

void MPU6050::update()
{
    // Read data from the device
    const bool newData = readRawDataFromDevice();
    if (!newData) // No new data was read
    {
        // Return without updating accelerometer/gyroscope data
        return;
    }

    // Update accelerometer data
    accelerometer._data.x = int16FromTwoUint8(_rawData[0], _rawData[1]);
    accelerometer._data.y = int16FromTwoUint8(_rawData[2], _rawData[3]);
    accelerometer._data.z = int16FromTwoUint8(_rawData[4], _rawData[5]);
    // @todo: Timestamp

    // Update temperature data
    // MPU6050_Data_Raw.temperature = (float)((float)((int16_t)((tmp[6] << 8) | tmp[7])) / (float)340.0f + (float)36.53f);

    // Update gyroscope data
    gyroscope._data.x = int16FromTwoUint8( _rawData[8],  _rawData[9]);
    gyroscope._data.y = int16FromTwoUint8(_rawData[10], _rawData[11]);
    gyroscope._data.z = int16FromTwoUint8(_rawData[12], _rawData[13]);
    // @todo: Timestamp
}

void MPU6050::i2cReadMemory(I2C_Address_t memoryAddress,
                            uint8_t *data,
                            uint8_t amount)
{
    _i2c.readMemory(MPU6050_I2C_DEVICE_ADDRESS,
                    memoryAddress,
                    data,
                    amount);
}

void MPU6050::i2cWriteMemory(I2C_Address_t memoryAddress,
                             uint8_t *data,
                             uint8_t amount)
{
    _i2c.writeMemory(MPU6050_I2C_DEVICE_ADDRESS,
                     memoryAddress,
                     data,
                     amount);
}

bool MPU6050::initAccelerometerConfig()
{
    // Set accelerometer range to +-4 g (AFS_SEL = 1)
    uint8_t tmp;
    i2cReadMemory(MPU6050_I2C_MEMORY_ADDRESS_ACCEL_CONFIG,
                  &tmp,
                  1);
    tmp = (tmp & 0xE7) | ((uint8_t)1 << 3);
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_ACCEL_CONFIG,
                   &tmp,
                   1);

    return true; // @todo: Add check
}

bool MPU6050::initConfig()
{
    // Set DLPF setting @todo: What is the value?
    uint8_t tmp;
    i2cReadMemory(MPU6050_I2C_MEMORY_ADDRESS_CONFIG,
                  &tmp,
                  1);
    tmp = (tmp & 0xFB) | (uint8_t)2;
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_CONFIG,
                   &tmp,
                   1);

    return true; // @todo: Add check
}

bool MPU6050::initGyroscopeConfig()
{
    // Set gyroscope range to +-500 deg/s (FS_SEL = 1)
    uint8_t tmp;
    i2cReadMemory(MPU6050_I2C_MEMORY_ADDRESS_GYRO_CONFIG,
                  &tmp,
                  1);
    tmp = (tmp & 0xE7) | ((uint8_t)1 << 3);
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_GYRO_CONFIG,
                   &tmp,
                   1);

    return true; // @todo: Add check
}

bool MPU6050::initPowerManagement()
{
    // Wake up the device and wait for the PLL to get established @todo: Make func. desc.
    uint8_t tmp = 0x00;
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_PWR_MGMT_1,
                   &tmp,
                   1);
    // Delay(1000); @todo: Somehow add a delay here (+ check?)

    // Set the time source to the (stable) PLL gyro-x reference
    tmp = 0x01;
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_PWR_MGMT_1,
                   &tmp,
                   1);

    return true; // @todo: Add check
}

bool MPU6050::initSampleRate()
{
    // Set sample rate to 1kHz
    uint8_t tmp = 7;
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_SMPLRT_DIV,
                   &tmp,
                   1);

    return true; // @todo: Add check
}

bool MPU6050::initWhoAmI()
{
    // Check the WHO_AM_I register @todo: Make func. desc.
    uint8_t tmp;
    i2cReadMemory(MPU6050_I2C_MEMORY_ADDRESS_WHO_AM_I,
                  &tmp,
                  1);
    return (tmp == 0x68);
}



MPU6050::MPU6050_Accelerometer::MPU6050_Accelerometer(MPU6050& parent) :
    _parent(parent)
{

}

void MPU6050::MPU6050_Accelerometer::initialise()
{
    _parent.initialise();
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
    _parent.initialise();
}

void MPU6050::MPU6050_Gyroscope::update()
{
    _parent.update();
}
