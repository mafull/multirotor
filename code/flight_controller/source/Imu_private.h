// Incorrect usage guard
#ifndef IMU_PRIVATE
    #error Private interface should not be included here!
#endif // IMU_PRIVATE

#ifndef __IMU_PRIVATE_H
#define __IMU_PRIVATE_H


// --- Public header ---
#include "Imu.h"

// --- Project includes ---

// --- Library includes ---
// FreeRTOS
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"

// --- Standard includes ---


/******************************************************************************
  Private Defines
 ******************************************************************************/


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 *
 */
typedef struct Imu_RawData_s
{
    uint16_t 
} Imu_RawData_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern Imu_Data_t Imu_data;

/**
 *
 */
extern TaskHandle_t Imu_hTask;

/**
 *
 */
extern bool Imu_isInitialised;

/**
 *
 */
extern bool Imu_isDataNew;

/**
 *
 */
extern bool Imu_isStarted;


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */
void Imu_ThreadTop(void *params);


#endif // __IMU_PRIVATE_H
