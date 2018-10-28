// Incorrect usage guard
#ifndef TIMER_PRIVATE
    #error Private interface should not be included here!
#endif // TIMER_PRIVATE

#ifndef __TIMER_PRIVATE_H
#define __TIMER_PRIVATE_H


// --- Public header ---
#include "peripherals/Timer.h"

// --- Library includes ---
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
typedef struct Timer_ConfigData_s
{
    TIM_TypeDef *halInstance;
    TIM_Base_InitTypeDef initStruct;
} Timer_ConfigData_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern const Timer_ConfigData_t Timer_configData[Timer_Instance_MAX];

/**
 *
 */
extern bool Timer_isInitialised;


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */
void Timer_EnableTimerClock(TIM_TypeDef *instance);


#endif // __TIMER_PRIVATE_H
