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

// --- Standard includes ---


/******************************************************************************
  Private Defines
 ******************************************************************************/


/******************************************************************************
  Private Data Types
 ******************************************************************************/


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
extern bool Imu_isInitialised;

/**
 *
 */
extern bool Imu_isDataNew;


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */

#endif // __IMU_PRIVATE_H
