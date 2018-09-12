#ifndef __MPU6050_HPP
#define __MPU6050_HPP

#include "imu/Accelerometer.hpp"
#include "imu/Gyroscope.hpp"

class MPU6050
{
    // Accelerometer-derived subclass
    class MPU6050_Accelerometer : public Accelerometer
    {
        friend class MPU6050;

    public:
        MPU6050_Accelerometer(MPU6050& parent);

        void initialise();
        void update();

    private:
        MPU6050& _parent;
    };

    // Gyroscope-derived subclass
    class MPU6050_Gyroscope : public Gyroscope
    {
        friend class MPU6050;

    public:
        MPU6050_Gyroscope(MPU6050& parent);

        void initialise();
        void update();

    private:
        MPU6050& _parent;
    };






public:
    MPU6050();

    ~MPU6050();

    void update();
    bool readFromDevice();

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

    uint8_t _rawData[14];
};

#endif  // __MPU6050_HPP