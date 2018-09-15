#ifndef __MPU6050_HPP
#define __MPU6050_HPP

#include "imu/Accelerometer.hpp"
#include "imu/Gyroscope.hpp"
#include "peripherals/I2C.hpp"

// @todo: Move this to Accelerometer-equivalent Temperature class
using Temperature_Data_t = 
    struct Temperature_Data_t
    {
        // @todo: Timestamp
        float temperature;
    };

using MPU6050_Offset_t = int16_t;
using MPU6050_ScaleFactor_t = float;

using MPU6050_Calibration_Data_t = 
    struct MPU6050_Calibration_Data_t
    {
        struct
        {
            struct
            {
                MPU6050_Offset_t x;
                MPU6050_Offset_t y;
                MPU6050_Offset_t z;
            } offsets;
            
            MPU6050_ScaleFactor_t scaleFactor;
        } accelerometer, gyroscope;
    };

using MPU6050_Data_t = 
    struct MPU6050_Data_t
    {
        Accelerometer_Data_t accelerometer;
        Gyroscope_Data_t gyroscope;
        Temperature_Data_t temperature;
    };


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
    void update();

    bool readRawDataFromDevice();

    void decodeRawData(MPU6050_Data_t& data);
    void applyCalibrationOffsetsToData(MPU6050_Data_t& data);
    void scaleData(MPU6050_Data_t& data);

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
    
    MPU6050_Calibration_Data_t _calibrationData;
};

#endif  // __MPU6050_HPP
