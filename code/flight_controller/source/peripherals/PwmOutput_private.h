// Incorrect usage guard
#ifndef PWM_OUTPUT_PRIVATE
    #error Private interface should not be included here!
#endif // PWM_OUTPUT_PRIVATE

#ifndef __PWM_OUTPUT_PRIVATE_H
#define __PWM_OUTPUT_PRIVATE_H


// --- Public header ---
#include "peripherals/PwmOutput.h"

// --- Project includes ---
#include "peripherals/Timer.h"
#define TIMER_PRIVATE
    #include "peripherals/Timer_private.h"
#undef TIMER_PRIVATE

// --- Library includes ---
#include "stm32f4xx_hal.h"


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 *
 */
typedef struct PwmOutput_ConfigData_s
{
    Timer_Instance_t timerInstance;
    Timer_OCConfigData_t ocConfigData;
} PwmOutput_ConfigData_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern const PwmOutput_ConfigData_t PwmOutput_configData[PwmOutput_Instance_MAX];

/**
 *
 */
extern bool PwmOutput_isInitialised;


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */

#endif // __PWM_OUTPUT_PRIVATE_H
