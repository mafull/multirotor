// Incorrect usage guard
#ifndef PWM_INPUT_PRIVATE
    #error Private interface should not be included here!
#endif // PWM_INPUT_PRIVATE

#ifndef __PWM_INPUT_PRIVATE_H
#define __PWM_INPUT_PRIVATE_H


// --- Public header ---
#include "peripherals/PwmInput.h"

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
typedef struct PwmInput_ConfigData_s
{
    Timer_Instance_t timerInstance;
    uint32_t channel;
    TIM_IC_InitTypeDef initStruct;
} PwmInput_ConfigData_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern const PwmInput_ConfigData_t PwmInput_configData[PwmInput_Instance_MAX];

/**
 *
 */
extern TIM_HandleTypeDef *PwmInput_timerHandles[PwmInput_Instance_MAX];

/**
 *
 */
extern bool PwmInput_isInitialised;


#endif // __PWM_INPUT_PRIVATE_H
