// --- Public header ---
#include "devices/MPU6050.h"

// --- Private header ---
#define MPU6050_PRIVATE
    #include "devices/MPU6050_private.h"
#undef MPU6050_PRIVATE


// --- Project includes ---
#include "Logger.h"
#include "macros.h"
#include "peripherals/ExternalInterrupt.h"
#include "peripherals/I2c.h"

// --- Library includes ---
// FreeRTOS
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"


// --- Standard includes ---


// @todo: Move these
#define CLEAR_BIT(byte, bit)           CLEAR_BITS(byte, bit, 1u)
#define CLEAR_BITS(byte, offset, mask) ((byte) ^ ((mask) << (offset)))

#define SET_BIT(byte, bit)             SET_BITS(byte, bit, 1u)
#define SET_BITS(byte, offset, mask)   ((byte) | ((mask) << (offset)))


/******************************************************************************
  Private Data
 ******************************************************************************/

MPU6050_DataReadyCallback_t MPU6050_dataReadyCallback = NULL;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool MPU6050_Initialise(void)
{
    // ENSURE(!MPU6050_isInitialised);
    ENSURE(I2c_IsInitialised());
    // ENSURE(ExternalInterrupt_IsInitialised()); // @todo: Make MPU6050_Int a config thing
    // ENSURE(Dma_IsInitialised()); // @todo: Make DMA a config thing



    bool success = true;
    uint8_t tmp = 0x00u;


    // @todo: Clean this all up
    // @todo: Add "WriteThenReadCheck" function to read back the written value



    // WHO_AM_I
    // Check WHO_AM_I equals the device address
    success =    MPU6050_ReadRegister(WHO_AM_I, &tmp)
              && (tmp == MPU6050_DEVICE_ADDR);
    // if (!success) return false;
    LOG_DEBUG("WHO_AM_I: 0x%02x", tmp);



    // PWM_MGMT_1
    // Reset the device
    tmp = SET_BIT(0x00, 7u); // DEVICE_RESET
    success = MPU6050_WriteRegister(POWER_MGMT_1, tmp);
    if (!success) return false;
    // Wait for the PLL to get established (gyro to stabilise)
    vTaskDelay(1000);
    // Wake the device and configure the clock source
    tmp = 0x00;                  //  SLEEP = 0
    tmp = SET_BITS(tmp, 0u, 3u); // CLKSEL = 3 (PLL with gyro Z-axis reference)
    success = MPU6050_WriteRegister(POWER_MGMT_1, tmp);
    if (!success) return false;

    // SMPLRT_DIV
    // Configure the sample rate
    tmp = SET_BITS(0x00, 0u, 7u); // SMPLRT_DIV = 7 (1kHz)
    success = MPU6050_WriteRegister(SMPLRT_DIV, tmp);
    if (!success) return false;

    // CONFIG
    // Configure FSYNC and DLPF
    tmp = 0x00;                  // EXT_SYNC_SET = 0 (FSYNC disabled)
    tmp = SET_BITS(tmp, 0u, 2u); //     DLPF_CFG = 2 (~3ms delay)
    success = MPU6050_WriteRegister(CONFIG, tmp);
    if (!success) return false;

    // GYRO_CONFIG
    // Configure gyroscope range
    tmp = SET_BITS(0x00, 3u, 1u); // FS_SEL = 1 (+-500 deg/s)
    success = MPU6050_WriteRegister(GYRO_CONFIG, tmp);
    if (!success) return false;

    // ACCEL_CONFIG
    // Configure accelerometer range
    tmp = SET_BITS(0x00, 3u, 2u); // AFS_SEL = 2 (+-8 g)
    success = MPU6050_WriteRegister(ACCEL_CONFIG, tmp);
    if (!success) return false;
    
    // INT_PIN_CFG
    // Configure I2C bypass
    tmp = SET_BIT(0x00, 1u); // I2C_BYPASS_EN = 1 (Bypass auxiliary I2C bus)
    success = MPU6050_WriteRegister(INT_PIN_CFG, tmp);
    if (!success) return false;

    // USER_CTRL
    // Configure I2C bypass///////////////
    // success = MPU6050_ReadRegister(USER_CTRL, &tmp);
    // if (!success) return false;

    LOG_DEBUG("Finished with MPU6050 0x%02x", tmp);



    // success = I2c_ReadMemory(I2c1,
    //                          0x1E,
    //                          0x10,
    //                          &tmp,
    //                          1u);// && (tmp == 0x48);
    // if (!success) return false;

    LOG_DEBUG("Finished with HMC5883L, id: 0x%02x", tmp);


  #if 0

    LOG_DEBUG("Interrupt pin");
    // Interrupt pin
    // INT_PIN_CFG
    // Read the current value so as not to change any other settings
    success = I2c_ReadMemory(I2c1,
                             MPU6050_DEVICE_ADDR,
                             MPU6050_MEM_ADDR_INT_PIN_CFG,
                             &tmp,
                             1u);
    if (!success) return false;
    // Configure the interrupt pin
    tmp |= ((uint8_t)1u << 4u); // Interrupt status bits cleared after any read
    success = I2c_WriteMemory(I2c1,
                              MPU6050_DEVICE_ADDR,
                              MPU6050_MEM_ADDR_INT_PIN_CFG,
                              &tmp,
                              1u);
    if (!success) return false;

    // INT_ENABLE
    // Enable the data ready interrupt
    tmp = ((uint8_t)1u << 0u);
    success = I2c_WriteMemory(I2c1,
                              MPU6050_DEVICE_ADDR,
                              MPU6050_MEM_ADDR_INT_ENABLE,
                              &tmp,
                              1u);
    if (!success) return false;

    LOG_DEBUG("I2C bypass");
    // I2C bypass
    // INT_PIN_CFG
    // Read the current value so as not to change any other settings
    success = I2c_ReadMemory(I2c1,
                             MPU6050_DEVICE_ADDR,
                             MPU6050_MEM_ADDR_INT_PIN_CFG,
                             &tmp,
                             1u);
    if (!success) return false;
    // Enable the I2C bypass
    tmp |= ((uint8_t)1u << 1u);
    success = I2c_WriteMemory(I2c1,
                              MPU6050_DEVICE_ADDR,
                              MPU6050_MEM_ADDR_INT_PIN_CFG,
                              &tmp,
                              1u);
    if (!success) return false;
#endif
#if 0
    // USER_CTRL
    // Same as before
    success = I2c_ReadMemory(I2c1,
                             MPU6050_DEVICE_ADDR,
                             MPU6050_MEM_ADDR_USER_CTRL,
                             &tmp,
                             1u);
    if (!success) return false;
    // Disable I2C master mode
    tmp &= ~((uint8_t)1u << 5u); // &= ~ not ^= in case the bit is not pre-set
    success = I2c_WriteMemory(I2c1,
                              MPU6050_DEVICE_ADDR,
                              MPU6050_MEM_ADDR_USER_CTRL,
                              &tmp,
                              1u);
    if (!success) return false;
#endif

    ExternalInterrupt_SetCallback(MPU6050_Int, &MPU6050_InterruptHandler); // @todo: Config instance
    ExternalInterrupt_Enable(MPU6050_Int);
    Dma_SetTransferCompleteCallback(Dma2_7, &MPU6050_DataReadyHandler); // @todo: Config instance

    return success;
}


void MPU6050_ProcessRawData(MPU6050_Data_t *const data)
{
    ENSURE(data);

    // @todo: Check that the device is initialised (and that the scale factors have values)

    // Static convenience
    static MPU6050_CalibrationData_t *const calib = &MPU6050_calibrationData;
    static MPU6050_RawData_t *const rawData = &MPU6050_rawData;
    ENSURE(rawData.timestamp.hasValue);

    /* Raise a warning if the accelerometer/gyroscope offsets have not been
    initialised. Their default (zero) values will be used */
    if (!calib->accelOffsets.timestamp.hasValue)
    {
        LOG_WARNING("Accelerometer offsets have not been loaded or calibrated");
    }
    if (!calib->gyroOffsets.timestamp.hasValue)
    {
        LOG_WARNING("Gyroscope offsets have not been loaded or calibrated");
    }

    // Scale and offset accelerometer data
    data.accel.x = (rawData.accelX * calib->accelScale) - calib->accelOffsets.x;
    data.accel.y = (rawData.accelY * calib->accelScale) - calib->accelOffsets.y;
    data.accel.z = (rawData.accelZ * calib->accelScale) - calib->accelOffsets.z;

    // Generate a temperature value in degrees celcius
    data.temperature = (rawData.temperature / 340.0f) + 36.53f;

    // Scale and offset gyroscope data
    data.gyro.x = (rawData.gyroX * calib->gyroScale) - calib->gyroOffsets.x;
    data.gyro.y = (rawData.gyroY * calib->gyroScale) - calib->gyroOffsets.y;
    data.gyro.z = (rawData.gyroZ * calib->gyroScale) - calib->gyroOffsets.z;

    // Copy across the timestamp
    data.timestamp = rawData.timestamp;
}


void MPU6050_SetDataReadyCallback(MPU6050_DataReadyCallback_t callback);
{
    ENSURE(callback);

    MPU6050_dataReadyCallback = callback;
    LOG_INFO("\"Data Ready\" callback set");
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

void MPU6050_DataReadyHandler(void)
{
    if (MPU6050_dataReadyCallback) // Callback has been set
    {
        MPU6050_dataReadyCallback();
    }
}


void MPU6050_InterruptHandler(ExternalInterrupt_State_t state)
{
    ENSURE(state == Risen); // @todo: Config?

    // Trigger a DMA read of the sensor data
    (void)I2c_ReadMemory(I2c1, // @todo: Config, ret value
                        MPU6050_DEVICE_ADDR,
                        (uint16_t)ACCEL_XOUT_H,
                        (uint8_t *)&MPU6050_rawData, // Struct must be in order
                        14u,
                        I2c_Dma);
}


bool MPU6050_ReadRegister(MPU6050_Register_t registerAddress, uint8_t *data)
{
    return I2c_ReadMemory(I2c1, // @todo: Config
                          MPU6050_DEVICE_ADDR,
                          (uint16_t)registerAddress,
                          data,
                          1u);
}


bool MPU6050_WriteRegister(MPU6050_Register_t registerAddress, uint8_t data)
{
    return I2c_WriteMemory(I2c1, // @todo: Config
                           MPU6050_DEVICE_ADDR,
                           (uint16_t)registerAddress,
                           &data,
                           1u);
}
