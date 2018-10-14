// Incorrect usage guard
#ifndef I2C_PRIVATE
    #error Private interface should not be included here!
#endif // I2C_PRIVATE

#ifndef __I2C_PRIVATE_H
#define __I2C_PRIVATE_H


// --- Public header ---
#include "peripherals/I2c.h"

// --- Library includes ---
// HAL_Driver
#include "stm32f4xx_hal.h"


/******************************************************************************
  Private Defines
 ******************************************************************************/


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 *
 */
typedef struct I2c_Handle_s
{
    I2c_Instance_t instance;
    bool initialised;

    I2C_HandleTypeDef halHandle;
} I2c_Handle_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern I2c_Handle_t I2c_handles[I2c_Instance_MAX];


#endif // __I2C_PRIVATE_H
