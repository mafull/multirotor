// Incorrect usage guard
#ifndef MPU6050_PRIVATE
    #error Private interface should not be included here!
#endif // MPU6050_PRIVATE

#ifndef __MPU6050_PRIVATE_H
#define __MPU6050_PRIVATE_H


// --- Public header ---
#include "devices/MPU6050.h"

// --- Project includes ---

// --- Library includes ---

// --- Standard includes ---


/******************************************************************************
  Private Defines
 ******************************************************************************/

/**
 *
 */
#define MPU6050_DEVICE_ADDR           0x68u


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 *
 */
typedef enum MPU6050_Register_e
{
    SELF_TEST_X         = 0x0D,
    SELF_TEST_Y,
    SELF_TEST_Z,
    SELF_TEST_A,

    SMPLRT_DIV          = 0x19,
    CONFIG,
    GYRO_CONFIG,
    ACCEL_CONFIG,

    FIFO_EN             = 0x23,
    I2C_MST_CTRL,
    I2C_SLV0_ADDR,
    I2C_SLV0_REG,
    I2C_SLV0_CTRL,
    I2C_SLV1_ADDR,
    I2C_SLV1_REG,
    I2C_SLV1_CTRL,
    I2C_SLV2_ADDR,
    I2C_SLV2_REG,
    I2C_SLV2_CTRL,
    I2C_SLV3_ADDR,
    I2C_SLV3_REG,
    I2C_SLV3_CTRL,
    I2C_SLV4_ADDR,
    I2C_SLV4_REG,
    I2C_SLV4_DO,
    I2C_SLV4_CTRL,
    I2C_SLV4_DI,
    I2C_MST_STATUS,
    INT_PIN_CFG,
    INT_ENABLE,

    INT_STATUS          = 0x3A,
    ACCEL_XOUT_H,
    ACCEL_XOUT_L,
    ACCEL_YOUT_H,
    ACCEL_YOUT_L,
    ACCEL_ZOUT_H,
    ACCEL_ZOUT_L,
    TEMP_OUT_H,
    TEMP_OUT_L,
    GYRO_XOUT_H,
    GYRO_XOUT_L,
    GYRO_YOUT_H,
    GYRO_YOUT_L,
    GYRO_ZOUT_h,
    GYRO_ZOUT_L,
    EXT_SENS_DATA_00,
    EXT_SENS_DATA_01,
    EXT_SENS_DATA_02,
    EXT_SENS_DATA_03,
    EXT_SENS_DATA_04,
    EXT_SENS_DATA_05,
    EXT_SENS_DATA_06,
    EXT_SENS_DATA_07,
    EXT_SENS_DATA_08,
    EXT_SENS_DATA_09,
    EXT_SENS_DATA_10,
    EXT_SENS_DATA_11,
    EXT_SENS_DATA_12,
    EXT_SENS_DATA_13,
    EXT_SENS_DATA_14,
    EXT_SENS_DATA_15,
    EXT_SENS_DATA_16,
    EXT_SENS_DATA_17,
    EXT_SENS_DATA_18,
    EXT_SENS_DATA_19,
    EXT_SENS_DATA_20,
    EXT_SENS_DATA_21,
    EXT_SENS_DATA_22,
    EXT_SENS_DATA_23,

    I2C_SLV0_DO         = 0x63,
    I2C_SLV1_DO,
    I2C_SLV2_DO,
    I2C_SLV3_DO,
    I2C_MST_DELAY_CTRL,
    SIGNAL_PATH_RESET,

    USER_CTRL           = 0x6A,
    POWER_MGMT_1,
    POWER_MGMT_2,

    FIFO_COUNTH        = 0x72,
    FIFO_COUNTL,
    FIFO_R_W,
    WHO_AM_I
} MPU6050_Register_t;


/******************************************************************************
  Private Data
 ******************************************************************************/


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool MPU6050_ReadRegister(MPU6050_Register_t registerAddress, uint8_t *data);

/**
 *
 */
bool MPU6050_WriteRegister(MPU6050_Register_t registerAddress, uint8_t data);


#endif // __MPU6050_PRIVATE_H
