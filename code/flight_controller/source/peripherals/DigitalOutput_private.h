//
#ifndef DIGITAL_OUTPUT_PRIVATE
    #error Private interface should not be included here!
#endif // DIGITAL_OUTPUT_PRIVATE

#ifndef __DIGITAL_OUTPUT_PRIVATE_H
#define __DIGITAL_OUTPUT_PRIVATE_H


// --- Public header ---
#include "peripherals/DigitalOutput.h"

// --- Library includes ---
// HAL_Driver
#include "stm32f4xx_hal.h"


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 * Structure defining a handle that contains configuration data for a Digital
 * Output
 */
typedef struct DigitalOutput_Handle_s
{
    DigitalOutput_Instance_t instance;
    bool initialised;

    GPIO_InitTypeDef initStruct;
    GPIO_TypeDef *port;
} DigitalOutput_Handle_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 * Handles containing the configuration data for each Digital Output present in
 * DigitalOutput_Instance_t
 */
extern DigitalOutput_Handle_t DigitalOutput_handles[DigitalOutput_Instance_MAX];


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 * Enable a GPIO port clock
 *
 * @param port The GPIO port whose clock is to be enabled
 */
void DigitalOutput_EnablePortClock(GPIO_TypeDef *port);


#endif // __DIGITAL_OUTPUT_PRIVATE_H
