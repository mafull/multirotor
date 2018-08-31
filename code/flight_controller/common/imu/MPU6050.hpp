#ifndef __MPU6050_HPP
#define __MPU6050_HPP

#include "imu/Accelerometer.hpp"
#include "imu/Gyroscope.hpp"

class MPU6050
{




    class MPU6050_Accelerometer : public Accelerometer
    {
    public:
        MPU6050_Accelerometer(MPU6050& parent);

        void initialise();
        void update();

    protected:

    private:
        MPU6050& _parent;
    };


    class MPU6050_Gyroscope : public Gyroscope
    {
    public:
        MPU6050_Gyroscope(MPU6050& parent);

        void initialise();
        void update();

    protected:

    private:
        MPU6050& _parent;
    };






public:
    MPU6050();

    ~MPU6050();

    void update(
        Accelerometer_Data_t *accelerometerData,
        Gyroscope_Data_t *gyroscopeData);
    void readFromDevice();

    void setI2C(I2C *i2c)
    {
        ASSERT(i2c);
        _i2c = i2c;
    }

    MPU6050_Accelerometer accelerometer;
    MPU6050_Gyroscope gyroscope;
    
protected:

private:
    I2C *_i2c;
};

#endif  // __MPU6050_HPP
