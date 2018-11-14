// Incorrect usage guard
#ifndef FLIGHT_CONTROLLER_PRIVATE
    #error Private interface should not be included here!
#endif // FLIGHT_CONTROLLER_PRIVATE

#ifndef __FLIGHT_CONTROLLER_PRIVATE_H
#define __FLIGHT_CONTROLLER_PRIVATE_H


// --- Public header ---
#include "FlightController.h"

// --- Project includes ---

// --- Library includes ---
// FreeRTOS
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/semphr.h"
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
extern bool FlightController_isStarted;


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */
void FlightController_InitialisePeripherals(void);

/**
 *
 */
void FlightController_ThreadTop(void *params);


#endif // __FLIGHT_CONTROLLER_PRIVATE_H
