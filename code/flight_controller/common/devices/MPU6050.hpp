#ifndef __MPU6050_HPP
#define __MPU6050_HPP

#include "peripherals/I2C.hpp"
#include "sensors/Accelerometer.hpp"
#include "sensors/Gyroscope.hpp"
#include "sensors/TemperatureSensor.hpp"


using MPU6050_Offset_t = int16_t;
using MPU6050_ScaleFactor_t = float;

using MPU6050_Calibration_Data_t = 
    struct MPU6050_Calibration_Data_t
    {
        struct
        {
            MPU6050_ScaleFactor_t scaleFactor;
            struct
            {
                MPU6050_Offset_t x;
                MPU6050_Offset_t y;
                MPU6050_Offset_t z;
            } offsets;
        } accelerometer, gyroscope;
        struct
        {
            MPU6050_ScaleFactor_t scaleFactor;
            MPU6050_Offset_t offset;
        } temperatureSensor;
    };

using MPU6050_Data_t = 
    struct MPU6050_Data_t
    {
        // @todo: Timestamp
        Accelerometer_Data_t accelerometer;
        Gyroscope_Data_t gyroscope;
        TemperatureSensor_Data_t temperatureSensor;
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

    // TemperatureSensor-derived subclass
    class MPU6050_TemperatureSensor : public TemperatureSensor
    {
        friend class MPU6050;

    public:
        MPU6050_TemperatureSensor(MPU6050& parent);

        void initialise();
        void update();

    private:
        MPU6050& _parent;
    };

public:
    MPU6050(I2C& i2c);

    MPU6050_Accelerometer accelerometer;
    MPU6050_Gyroscope gyroscope;
    MPU6050_TemperatureSensor temperatureSensor;

private:
    void initialise();
    void update();

    bool readRawDataFromDevice();

    void applyCalibrationOffsetsToData(MPU6050_Data_t& data);
    void decodeRawData(MPU6050_Data_t& data);
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
