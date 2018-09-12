#ifndef __IMU_HPP
#define __IMU_HPP

#include "imu/Accelerometer.hpp"
#include "imu/Gyroscope.hpp"
#include "imu/Magnetometer.hpp"
#include "peripherals/I2C.hpp"

using IMU_Data_Element_t = float;

using IMU_Data_t = 
    struct IMU_Data_t
    {
        // TIME DATATYPE timestamp;

        struct
        {
            IMU_Data_Element_t roll;
            IMU_Data_Element_t pitch;
            IMU_Data_Element_t yaw;
        } gyroscope;

        struct
        {
            IMU_Data_Element_t roll;
            IMU_Data_Element_t pitch;
            IMU_Data_Element_t yaw;
        } accelerometer;

        struct
        {
            IMU_Data_Element_t heading;
        } magnetometer;

        IMU_Data_Element_t roll;
        IMU_Data_Element_t pitch;
        IMU_Data_Element_t yaw;
    };

class IMU
{
public:
    IMU();
    ~IMU();
    
    void setConfiguration(I2C *i2c);

    void initialise();

    void update();

    const IMU_Data_t& getData() const
    {
        return _data;
    }

    void setAccelerometer(Accelerometer *accelerometer)
    {
        ASSERT(accelerometer);
        _accelerometer = accelerometer;
    }

    void setGyroscope(Gyroscope *gyroscope)
    {
        ASSERT(gyroscope);
        _gyroscope = gyroscope;
    }

    void setMagnetometer(Magnetometer *magnetometer)
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

    IMU_Data_t _data;
};

#endif  // __IMU_HPP