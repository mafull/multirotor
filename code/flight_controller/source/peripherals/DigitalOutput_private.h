//
#ifndef DIGITAL_OUTPUT_PRIVATE
    #error Private interface should not be included here!
#endif // DIGITAL_OUTPUT_PRIVATE

#ifndef __DIGITAL_OUTPUT_PRIVATE_H
#define __DIGITAL_OUTPUT_PRIVATE_H


// --- Public header ---
#include "peripherals/DigitalOutput.h"

// --- Project includes ---
#include "peripherals/Gpio.h"


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 *
 */
typedef struct DigitalOutput_ConfigData_s
{
    Gpio_Instance_t gpioInstance;
} DigitalOutput_ConfigData_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
const extern DigitalOutput_ConfigData_t DigitalOutput_configData[DigitalOutput_Instance_MAX];

/**
 *
 */
extern bool DigitalOutput_isInitialised;


#endif // __DIGITAL_OUTPUT_PRIVATE_H
