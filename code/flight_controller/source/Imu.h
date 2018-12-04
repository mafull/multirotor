#ifndef __IMU_H
#define __IMU_H


// --- Project includes ---
#include "macros.h"

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

/**
 *
 */
typedef float Imu_DataType_t;

/**
 *
 */
typedef struct Imu_Data_s
{
    struct
    {
        Imu_DataType_t roll;
    } angles;
    
    struct
    {
        Imu_DataType_t roll;
    } rates;

    OptionalTimestamp_t timestamp;
} Imu_Data_t;


/******************************************************************************
  Public Data
 ******************************************************************************/


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool Imu_GetNewData(Imu_Data_t *const data);

/**
 *
 */
void Imu_Run(void);


#endif // __IMU_H
