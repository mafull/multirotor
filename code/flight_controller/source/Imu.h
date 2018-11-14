#ifndef __IMU_H
#define __IMU_H


// --- Project includes ---

// --- Library includes ---

// --- Standard includes ---
#include <stdbool.h>


/******************************************************************************
  Public Defines
 ******************************************************************************/


/******************************************************************************
  Public Data Types
 ******************************************************************************/

typedef float Imu_DataType_t;

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
bool Imu_Initialise(void);

/**
 *
 */
bool Imu_IsInitialised(void);

/**
 *
 */
void Imu_Run(void);

/**
 *
 */
void Imu_Update(void);


#endif // __IMU_H
