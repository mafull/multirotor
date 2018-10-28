// Incorrect usage guard
#ifndef EXTERNAL_INTERRUPT_PRIVATE
    #error Private interface should not be included here!
#endif // EXTERNAL_INTERRUPT_PRIVATE

#ifndef __EXTERNAL_INTERRUPT_PRIVATE_H
#define __EXTERNAL_INTERRUPT_PRIVATE_H


// --- Public header ---
#include "peripherals/ExternalInterrupt.h"

// --- Project Includes ---
#include "peripherals/Gpio.h"

// --- Library Includes
// HAL Driver
#include "stm32f4xx_hal.h"


/******************************************************************************
  Private Defines
 ******************************************************************************/

/**
 *
 */
#define EXTERNAL_INTERRUPT_LINE_COUNT_GPIO  16u
#define EXTERNAL_INTERRUPT_LINE_COUNT       (EXTERNAL_INTERRUPT_LINE_COUNT_GPIO)


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 *
 */
typedef struct ExternalInterrupt_ConfigData_s
{
    Gpio_Instance_t gpioInstance;
    uint8_t line;
    IRQn_Type irqN;
} ExternalInterrupt_ConfigData_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern const ExternalInterrupt_ConfigData_t ExternalInterrupt_configData[ExternalInterrupt_Instance_MAX];

/**
 *
 */
extern ExternalInterrupt_CallbackFunction_t ExternalInterrupt_callbackFunctions[EXTERNAL_INTERRUPT_LINE_COUNT];

/**
 *
 */
extern bool ExternalInterrupt_isInitialised;


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */
void ExternalInterrupt_GenericHandler(uint8_t line);


#endif // __EXTERNAL_INTERRUPT_PRIVATE_H
