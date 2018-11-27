// Incorrect usage guard
#ifndef CONTROL_LOOP_PRIVATE
    #error Private interface should not be included here!
#endif // CONTROL_LOOP_PRIVATE

#ifndef __CONTROL_LOOP_PRIVATE_H
#define __CONTROL_LOOP_PRIVATE_H


// --- Public header ---
#include "ControlLoop.h"

// --- Project includes ---

// --- Library includes ---
// FreeRTOS
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/task.h"

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
extern TaskHandle_t ControlLoop_hTask;

/**
 *
 */
extern bool ControlLoop_isInitialised;

/**
 *
 */
extern bool ControlLoop_isStarted;


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */
void ControlLoop_ThreadTop(void *params);


#endif // __CONTROL_LOOP_PRIVATE_H
