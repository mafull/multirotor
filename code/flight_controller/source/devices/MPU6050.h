#ifndef __MPU6050_H
#define __MPU6050_H


// --- Project includes ---

// --- Library includes ---

// --- Standard includes ---
#include <stdbool.h>
#include <stdint.h>


/******************************************************************************
  Public Defines
 ******************************************************************************/


/******************************************************************************
  Public Data Types
 ******************************************************************************/
typedef uint32_t Timestamp_t; // @todo: MOVE THIS
typedef struct Timestamp_s
{
    bool hasValue;
    Timestamp_t value;
} OptionalTimestamp_t; // @todo: MOVE THIS

/**
 *
 */
typedef float MPU6060_DataType_t;

/**
 * 
 * @note  The struct members used to store sensor readings must occur first and
          their order must not be changed - they match the MPU6050 device's data
          register order
 */
typedef struct MPU6050_RawData_s
{
    // Sensor readings
    uint16_t accelX;
    uint16_t accelY;
    uint16_t accelZ;
    uint16_t temperature;
    uint16_t gyroX;
    uint16_t gyroY;
    uint16_t gyroZ;

    // Other data
    Timestamp_t timestamp;  // @todo: Maybe make optional
} MPU6050_RawData_t;

/**
 *
 */
typedef struct MPU6050_Data_s
{
    struct
    {
        MPU6060_DataType_t x;
        MPU6060_DataType_t y;
        MPU6060_DataType_t z;
    } accel, gyro;

    MPU6060_DataType_t temperature;

    Timestamp_t timestamp; // @todo: Maybe make optional
} MPU6050_Data_t;

/**
 *
 */
typedef struct MPU6050_CalibrationData_s
{
    // Scale facotrs
    MPU6050_DataType_t accelScale;
    MPU6050_DataType_t gyroScale;

    // Calibrated offsets (scaled)
    struct
    {
        MPU6050_DataType_t x;
        MPU6050_DataType_t y;
        MPU6050_DataType_t z;

        /* The accelerometer/gyroscope can be calibrated separately so need
        their own timestamps */
        OptionalTimestamp timestamp;
    } accelOffsets, gyroOffsets;
} MPU6050_CalibrationData_t;


/******************************************************************************
  Public Data
 ******************************************************************************/


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool MPU6050_Initialise(void);

/**
 *
 */
void MPU6050_ProcessRawData(const MPU6050_RawData_t *const rawData,
                            MPU6050_Data_t *const data);


#endif // __MPU6050_H
