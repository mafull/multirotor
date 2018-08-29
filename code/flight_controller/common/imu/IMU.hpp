#ifndef __IMU_HPP
#define __IMU_HPP

#include "imu/Accelerometer.hpp"
#include "imu/Gyroscope.hpp"
#include "imu/Magnetometer.hpp"
#include "peripherals/I2C.hpp"

class IMU
{
public:
    IMU();
    ~IMU();
    
    void setConfiguration(I2C *i2c);

    void initialise();

    void addAccelerometer(Accelerometer *accelerometer)
    {
        ASSERT(accelerometer);
        _accelerometer = accelerometer;
    }

    void addGyroscope(Gyroscope *gyroscope)
    {
        ASSERT(gyroscope);
        _gyroscope = gyroscope;
    }

    void addMagnetometer(Magnetometer *magnetometer)
    {
        ASSERT(magnetometer);
        _magnetometer = magnetometer;
    }

    void getAccelerometerData(Accelerometer_Data_t *data)
    {
        ASSERT(data);
        *data = _accelerometer->getData();
    }

    void getGyroscopeData(Gyroscope_Data_t *data)
    {
        ASSERT(data);
        *data = _gyroscope->getData();
    }

    void getMagnetometerData(Magnetometer_Data_t *data)
    {
        ASSERT(data);
        *data = _magnetometer->getData();
    }

protected:

private:
    bool _configured;
    bool _initialised;

    Accelerometer *_accelerometer;
    Gyroscope *_gyroscope;
    Magnetometer *_magnetometer;
};

#endif  // __IMU_HPP
