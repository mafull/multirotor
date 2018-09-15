#ifndef __MPU6050_HPP
#define __MPU6050_HPP

#include "imu/Accelerometer.hpp"
#include "imu/Gyroscope.hpp"
#include "peripherals/I2C.hpp"

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
    MPU6050(I2C& i2c);

    MPU6050_Accelerometer accelerometer;
    MPU6050_Gyroscope gyroscope;

private:
    void initialise();
    bool readRawDataFromDevice();
    void update();

    void i2cReadMemory(I2C_Address_t address,
                       uint8_t *data,
                       uint8_t amount);
    void i2cWriteMemory(I2C_Address_t address,
                        uint8_t *data,
                        uint8_t amount);

    bool initAccelerometerConfig();
    bool initConfig();
    bool initGyroscopeConfig();
    bool initPowerManagement();
    bool initSampleRate();
    bool initWhoAmI();

    bool _initialised;

    I2C& _i2c;

    uint8_t _rawData[14];
};

#endif  // __MPU6050_HPP
