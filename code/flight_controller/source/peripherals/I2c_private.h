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

/**
 *
 */
#define I2C_TRANSMIT_TIMEOUT   HAL_MAX_DELAY // @todo: Change this


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 *
 */
typedef struct I2c_ConfigData_s
{
    I2C_TypeDef *halInstance;
    I2C_InitTypeDef initStruct;
} I2c_ConfigData_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern const I2c_ConfigData_t I2c_configData[I2c_Instance_MAX];

/**
 *
 */
extern I2C_HandleTypeDef I2c_handles[I2c_Instance_MAX];

/**
 *
 */
extern bool I2c_isInitialised;


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */
void I2c_EnableI2cClock(I2C_TypeDef *instance);


#endif // __I2C_PRIVATE_H
