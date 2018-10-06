#include "MPU6050.hpp"

#define MPU6050_I2C_DEVICE_ADDRESS              0x68

#define MPU6050_I2C_MEMORY_ADDRESS_ACCEL_CONFIG 0x1C
#define MPU6050_I2C_MEMORY_ADDRESS_CONFIG       0x1A
#define MPU6050_I2C_MEMORY_ADDRESS_DATA         0x3B
#define MPU6050_I2C_MEMORY_ADDRESS_GYRO_CONFIG  0x1B
#define MPU6050_I2C_MEMORY_ADDRESS_INT_ENABLE   0x38
#define MPU6050_I2C_MEMORY_ADDRESS_INT_PIN_CFG  0x37
#define MPU6050_I2C_MEMORY_ADDRESS_PWR_MGMT_1   0x6B
#define MPU6050_I2C_MEMORY_ADDRESS_SMPLRT_DIV   0x19
#define MPU6050_I2C_MEMORY_ADDRESS_USER_CTRL    0x6A
#define MPU6050_I2C_MEMORY_ADDRESS_WHO_AM_I     0x75

#define MPU6050_CALIBRATION_DURATION_MS         5000u


static inline int16_t int16FromTwoUint8(uint8_t high, uint8_t low)
{
    return static_cast<int16_t>((high << 8) | low);
}


MPU6050::MPU6050(I2C& i2c) :
    // Public members
    accelerometer(*this),
    gyroscope(*this),
    temperatureSensor(*this),
    // Private members
    _calibrated(false),
    _initialised(false),
    _i2c(i2c)
{

}

void MPU6050::calibrate()
{
    ASSERT(_initialised);

    // Create new data to work on so we don't corrupt old data if calibration is not successful
    MPU6050_Calibration_Data_t calibrationData;
    // The scale factor and tempterature calibration data will be unchanged
    calibrationData.accelerometer.scaleFactor = _calibrationData.accelerometer.scaleFactor;
    calibrationData.gyroscope.scaleFactor = _calibrationData.gyroscope.scaleFactor;
    calibrationData.temperatureSensor = _calibrationData.temperatureSensor;

    // Create a data structure to read data into during calibration
    MPU6050_Data_t mpu6050Data;

    // Retain a count of the number of data reads for use in averaging calculations
    uint32_t numReads = 0;

    // endTime = now() + MPU6050_CALIBRATION_DURATION_MS; // @todo Implement this
    //while (now() < endTime)
    for (uint16_t i; i < MPU6050_CALIBRATION_DURATION_MS; i++) // @todo: Replace this line
    {
        // Get new data and scale it @todo: Handle a failed read
        const bool newData = readRawDataFromDevice();
        decodeRawData(mpu6050Data);
        scaleData(mpu6050Data);
        
        calibrationData.accelerometer.offsets.x += mpu6050Data.accelerometer.x;
        calibrationData.accelerometer.offsets.y += mpu6050Data.accelerometer.y;
        calibrationData.accelerometer.offsets.z += mpu6050Data.accelerometer.z;

        calibrationData.gyroscope.offsets.x += mpu6050Data.gyroscope.x;
        calibrationData.gyroscope.offsets.y += mpu6050Data.gyroscope.y;
        calibrationData.gyroscope.offsets.z += mpu6050Data.gyroscope.z;

        numReads++;
        // @todo: DELAY SOMEHOW
    }

    // Calculate accelerometer offsets
    // @todo: Maybe make this a single-line thing somehow
    calibrationData.accelerometer.offsets.x /= numReads;
    calibrationData.accelerometer.offsets.y /= numReads;
    calibrationData.accelerometer.offsets.z /= numReads;
    calibrationData.accelerometer.offsets.z += 1;        // Consider gravity

    // Calculate gyroscope offsets
    calibrationData.gyroscope.offsets.x /= numReads;
    calibrationData.gyroscope.offsets.y /= numReads;
    calibrationData.gyroscope.offsets.z /= numReads;

    // Store a timestamp so we know when the calibration data was calculated
    // calibrationData.timestamp = // @todo: Do this

    // Store the new calibration data
    _calibrationData = calibrationData;

    _calibrated = true;
}

void MPU6050::initialise()
{
    ASSERT(!_initialised);

    // @todo: These probably shouldn't be asserts
    // ASSERT(initWhoAmI());
    // ASSERT(initPowerManagement());
    // ASSERT(initSampleRate());
    // ASSERT(initConfig());
    // ASSERT(initGyroscopeConfig());
    // ASSERT(initAccelerometerConfig());
    // ASSERT(initInterruptPin());
    // ASSERT(initI2CBypass());
    initWhoAmI();
    initPowerManagement();
    initSampleRate();
    initConfig();
    initGyroscopeConfig();
    initAccelerometerConfig();
    initInterrupt();
    initI2CBypass();

    _initialised = true;
}

void MPU6050::update()
{
    // Read data from the device
    const bool newData = readRawDataFromDevice();
    if (!newData) // No new data was read
    {
        // Return without updating device data
        return;
    }

    MPU6050_Data_t mpu6050Data;

    // Generate normalised Accelerometer/Gyroscope/Temperature data from the raw data
    decodeRawData(mpu6050Data);                 // Get raw Accelerometer/Gyroscope/Temperature data
    scaleData(mpu6050Data);                     // Scale the data
    applyCalibrationOffsetsToData(mpu6050Data); // Apply calibration offsets to the data
    // mpu6050Data.timestamp =                  // @todo: Do this

    // Update timestamps
    // @todo: Do this
    // mpu6050Data.accelerometer.timestamp = mpu6050Data.timestamp;
    // mpu6050Data.gyroscope.timestamp = mpu6050Data.timestamp;
    // mpu6050Data.temperature.timestamp = mpu6050Data.timestamp;

    // Update Accelerometer and Gyroscope data with this normalised data
    accelerometer._data = mpu6050Data.accelerometer;
    gyroscope._data = mpu6050Data.gyroscope;
    temperatureSensor._data = mpu6050Data.temperatureSensor;
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

void MPU6050::applyCalibrationOffsetsToData(MPU6050_Data_t& data)
{
    // Accelerometer
    data.accelerometer.x -= _calibrationData.accelerometer.offsets.x;
    data.accelerometer.y -= _calibrationData.accelerometer.offsets.y;
    data.accelerometer.z -= _calibrationData.accelerometer.offsets.z;

    // Gyroscope
    data.gyroscope.x -= _calibrationData.gyroscope.offsets.x;
    data.gyroscope.y -= _calibrationData.gyroscope.offsets.y;
    data.gyroscope.z -= _calibrationData.gyroscope.offsets.z;

    // Temperature
    data.temperatureSensor.temperature -= _calibrationData.temperatureSensor.offset;
}

void MPU6050::decodeRawData(MPU6050_Data_t& data)
{
    // Bytes 0 to 5 - Accelerometer
    data.accelerometer.x = int16FromTwoUint8(_rawData[0], _rawData[1]);
    data.accelerometer.y = int16FromTwoUint8(_rawData[2], _rawData[3]);
    data.accelerometer.z = int16FromTwoUint8(_rawData[4], _rawData[5]);

    // Bytes 6 to 7 - Temperature
    data.temperatureSensor.temperature = int16FromTwoUint8(_rawData[6], _rawData[7]);

    // Bytes 8 to 13 - Gyroscope
    data.gyroscope.x = int16FromTwoUint8( _rawData[8],  _rawData[9]);
    data.gyroscope.y = int16FromTwoUint8(_rawData[10], _rawData[11]);
    data.gyroscope.z = int16FromTwoUint8(_rawData[12], _rawData[13]);
}

void MPU6050::scaleData(MPU6050_Data_t& data)
{
    // Accelerometer
    data.accelerometer.x *= _calibrationData.accelerometer.scaleFactor;
    data.accelerometer.y *= _calibrationData.accelerometer.scaleFactor;
    data.accelerometer.z *= _calibrationData.accelerometer.scaleFactor;

    // Gyroscope
    data.gyroscope.x *= _calibrationData.gyroscope.scaleFactor;
    data.gyroscope.y *= _calibrationData.gyroscope.scaleFactor;
    data.gyroscope.z *= _calibrationData.gyroscope.scaleFactor;

    // Temperature
    data.temperatureSensor.temperature *= _calibrationData.temperatureSensor.scaleFactor;
}


void MPU6050::i2cReadMemory(I2C_Address_t memoryAddress,
                            uint8_t *data,
                            uint8_t amount)
{
    // Read data from the MPU6050' memory
    _i2c.readMemory(MPU6050_I2C_DEVICE_ADDRESS,
                    memoryAddress,
                    data,
                    amount);
}

void MPU6050::i2cWriteMemory(I2C_Address_t memoryAddress,
                             uint8_t *data,
                             uint8_t amount)
{
    // Write data to the MPU6050's memory
    _i2c.writeMemory(MPU6050_I2C_DEVICE_ADDRESS,
                     memoryAddress,
                     data,
                     amount);
}

/**
 *  Write to the ACCEL_CONFIG register to configure the accelerometer full-scale
 *  output range
 *
 *  @return true if successful
 */
bool MPU6050::initAccelerometerConfig()
{
    // Set accelerometer range to +-8 g (AFS_SEL = 2)
    uint8_t tmp = ((uint8_t)2u << 3u);
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_ACCEL_CONFIG,
                   &tmp,
                   1u);

    return true; // @todo: Add check
}

/**
 *  Write to the CONFIG register to disable FSYNC input and configure the DLPF
 *
 *  @return true if successful
 */
bool MPU6050::initConfig()
{

    /* Disable FSYNC and configure the DLPF for ~3ms delay
        DLPF setting 2: 2 in bits 0-2
        FSYNC disabled: 0 in bits 3-5
    */
    uint8_t tmp = 0x02u;
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_CONFIG,
                   &tmp,
                   1u);

    return true; // @todo: Add check
}

/**
 *  Write to the GYRO_CONFIG register to configure the gyroscope full-scale
 *  output range
 *
 *  @return true if successful
 */
bool MPU6050::initGyroscopeConfig()
{
    // Set gyroscope range to +-500 deg/s (FS_SEL = 1)
    uint8_t tmp = ((uint8_t)1u << 3u);
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_GYRO_CONFIG,
                   &tmp,
                   1u);

    return true; // @todo: Add check
}

/**
 *  Write to the INT_PIN_CFG and USER_CTRL registers to enable the I2C bypass to
 *  allow the host MCU to communicate with auxiliary devices
 *
 *  @return true if successful
 */
bool MPU6050::initI2CBypass()
{
    uint8_t tmp;

    // INT_PIN_CFG
    // Read the current value so as not to change any other settings
    i2cReadMemory(MPU6050_I2C_MEMORY_ADDRESS_INT_PIN_CFG,
                  &tmp,
                  1u);

    // Enable the I2C bypass
    tmp |= ((uint8_t)1u << 1u);
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_INT_PIN_CFG,
                   &tmp,
                   1u);

    // USER_CTRL
    // Same as before
    i2cReadMemory(MPU6050_I2C_MEMORY_ADDRESS_USER_CTRL,
                  &tmp,
                  1u);

    // Disable I2C master mode
    tmp &= ~((uint8_t)1u << 5u); // &= ~ not ^= in case the bit is not pre-set
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_USER_CTRL,
                   &tmp,
                   1u);


    return true; // @todo: Add check
}

/**
 *  Write to the INT_PIN_CFG and INT_ENABLE registers to configure the interrupt
 *  pin and enable the interrupt
 *
 *  @return true if successful
 */
bool MPU6050::initInterrupt()
{
    uint8_t tmp;

    // INT_PIN_CFG
    // Read the current value so as not to change any other settings
    i2cReadMemory(MPU6050_I2C_MEMORY_ADDRESS_INT_PIN_CFG,
                  &tmp,
                  1u);

    // Configure the interrupt pin
    tmp |= ((uint8_t)1u << 4u); // Interrupt status bits cleared after any read
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_INT_PIN_CFG,
                   &tmp,
                   1u);

    // INT_ENABLE
    // Enable the data ready interrupt
    tmp |= ((uint8_t)1u << 0u);
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_INT_ENABLE,
                   &tmp,
                   1u);

    return true; // @todo: Add check
}

/**
 *  Write to the PWR_MGMT_1 register to reset the device, wake it up and
 *  configure the clock source
 *
 *  @return true if successful
 */
bool MPU6050::initPowerManagement()
{
    uint8_t tmp;
    
    // Reset and wake up the device
    tmp = ((uint8_t)1u << 7u); // @todo: Make BIT SET macro/func
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_PWR_MGMT_1,
                   &tmp,
                   1u);
    
    // Wait for the PLL to get established (gyro to stabilise)
    // Delay(50); @todo: Somehow add a delay here (+ check?)
    for (int i = 0u; i < 1e6; i++) {}

    // Set the time source to the (stable) PLL gyro-z reference
    tmp = 0x03u;
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_PWR_MGMT_1,
                   &tmp,
                   1u);

    return true; // @todo: Add check
}

/**
 *  Write to the SMPLRT_DIV register to configure the sample rate
 *
 *  @return true if successful
 */
bool MPU6050::initSampleRate()
{
    /* From the docs:
        Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV)
        so
        SMPLRT_DIV = (Gyroscope Output Rate / Sample Rate) - 1

       Gyro rate is 1kHz when DLPF enabled
       so
       Sample rate of 1kHz:
        SMPLRT_DIV = (1000 / 1000) - 1
        SMPLRT_DIV = 0
    */

    // Set sample rate to 1kHz
    uint8_t tmp = 0x00u;
    i2cWriteMemory(MPU6050_I2C_MEMORY_ADDRESS_SMPLRT_DIV,
                   &tmp,
                   1u);

    return true; // @todo: Add check
}

/**
 *  Read from the WHO_AM_I register to check that communication is working
 *
 *  @return true if successful
 */
bool MPU6050::initWhoAmI()
{
    // Read the value of WHO_AM_I
    uint8_t tmp;
    i2cReadMemory(MPU6050_I2C_MEMORY_ADDRESS_WHO_AM_I,
                  &tmp,
                  1u);

    // Check that it matches the device address
    return (tmp == MPU6050_I2C_DEVICE_ADDRESS);
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


MPU6050::MPU6050_TemperatureSensor::MPU6050_TemperatureSensor(MPU6050& parent) :
    _parent(parent)
{

}

void MPU6050::MPU6050_TemperatureSensor::initialise()
{
    _parent.initialise();
}

void MPU6050::MPU6050_TemperatureSensor::update()
{
    _parent.update();
}
