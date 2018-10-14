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
 *
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
 *
 */
extern DigitalOutput_Handle_t DigitalOutput_handles[DigitalOutput_Instance_MAX];


#endif // __DIGITAL_OUTPUT_PRIVATE_H
