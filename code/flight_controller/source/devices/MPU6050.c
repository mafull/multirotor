// --- Public header ---
#include "devices/MPU6050.h"

// --- Private header ---
#define MPU6050_PRIVATE
    #include "devices/MPU6050_private.h"
#undef MPU6050_PRIVATE


// --- Project includes ---
#include "macros.h"
#include "peripherals/ExternalInterrupt.h"
#include "peripherals/I2c.h"
#include "peripherals/Uart.h"

// --- Library includes ---

// --- Standard includes ---


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool MPU6050_Initialise(void)
{
    // ENSURE(!MPU6050_isInitialised);
    ENSURE(I2c_IsInitialised());
    // ENSURE(ExternalInterrupt_IsInitialised()); // @todo: Make MPU6050_Int a config thing

    bool success = true;
    uint8_t tmp = 0x00u;


    // @todo: Clean this all up
    // @todo: Add "WriteThenReadCheck" function to read back the written value
    Uart_Write(Uart1, "WHO_AM_I\n");
    // WHO_AM_I
    // Check WHO_AM_I equals the device address
    success = (I2c_ReadMemory(I2c1,
                              MPU6050_DEVICE_ADDR,
                              MPU6050_MEM_ADDR_WHO_AM_I,
                              &tmp,
                              1u) && (tmp == MPU6050_DEVICE_ADDR));
    if (!success) return false;

    Uart_Write(Uart1, "PWM_MGMT_1\n");
    // PWM_MGMT_1
    // Reset and wake up the device
    tmp = 0x00u; //((uint8_t)1u << 7u);
    success = I2c_WriteMemory(I2c1,
                              MPU6050_DEVICE_ADDR,
                              MPU6050_MEM_ADDR_PWR_MGMT_1,
                              &tmp,
                              1u);
    if (!success) return false;
    // Wait for the PLL to get established (gyro to stabilise)
    HAL_Delay(1000);
    // Set the time source to the (stable) PLL gyro-z reference
    tmp = 0x03u;
    success = I2c_WriteMemory(I2c1,
                              MPU6050_DEVICE_ADDR,
                              MPU6050_MEM_ADDR_PWR_MGMT_1,
                              &tmp,
                              1u);
    if (!success) return false;

    Uart_Write(Uart1, "SMPLRT_DIV\n");
    // SMPLRT_DIV
    // Set the sample rate to 1kHz
    tmp = 0x07u; // 0x00u;
    success = I2c_WriteMemory(I2c1,
                              MPU6050_DEVICE_ADDR,
                              MPU6050_MEM_ADDR_SMPLRT_DIV,
                              &tmp,
                              1u);
    if (!success) return false;

    Uart_Write(Uart1, "CONFIG\n");
    // CONFIG
    // Disable FSYNC input and configure the DLPF for ~3ms delay
    tmp = 0x02u;
    success = I2c_WriteMemory(I2c1,
                              MPU6050_DEVICE_ADDR,
                              MPU6050_MEM_ADDR_CONFIG,
                              &tmp,
                              1u);
    if (!success) return false;

    Uart_Write(Uart1, "GYRO_CONFIG\n");
    // GYRO_CONFIG
    // Set gyroscope range to +-500 deg/s (FS_SEL = 1)
    tmp = ((uint8_t)1u << 3u);
    success = I2c_WriteMemory(I2c1,
                              MPU6050_DEVICE_ADDR,
                              MPU6050_MEM_ADDR_GYRO_CONFIG,
                              &tmp,
                              1u);
    if (!success) return false;

    Uart_Write(Uart1, "ACCEL_CONFIG\n");
    // ACCEL_CONFIG
    // Set accelerometer range to +-8 g (AFS_SEL = 2)
    tmp = ((uint8_t)2u << 3u);
    success = I2c_WriteMemory(I2c1,
                              MPU6050_DEVICE_ADDR,
                              MPU6050_MEM_ADDR_ACCEL_CONFIG,
                              &tmp,
                              1u);
    if (!success) return false;

    Uart_Write(Uart1, "Interrupt pin\n");
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

    Uart_Write(Uart1, "I2C bypass\n");
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
    return success;
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/
