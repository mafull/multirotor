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

/**
 *
 */
#define MPU6050_MEM_ADDR_ACCEL_CONFIG 0x1Cu
#define MPU6050_MEM_ADDR_CONFIG       0x1Au
#define MPU6050_MEM_ADDR_DATA         0x3Bu
#define MPU6050_MEM_ADDR_GYRO_CONFIG  0x1Bu
#define MPU6050_MEM_ADDR_INT_ENABLE   0x38u
#define MPU6050_MEM_ADDR_INT_PIN_CFG  0x37u
#define MPU6050_MEM_ADDR_PWR_MGMT_1   0x6Bu
#define MPU6050_MEM_ADDR_SMPLRT_DIV   0x19u
#define MPU6050_MEM_ADDR_USER_CTRL    0x6Au
#define MPU6050_MEM_ADDR_WHO_AM_I     0x75u


/******************************************************************************
  Private Data Types
 ******************************************************************************/


/******************************************************************************
  Private Data
 ******************************************************************************/


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */

#endif // __MPU6050_PRIVATE_H
