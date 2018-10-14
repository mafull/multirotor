#ifndef __DIGITAL_OUTPUT_H
#define __DIGITAL_OUTPUT_H


// Standard includes
#include <stdbool.h>


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 *
 */
typedef enum DigitalOutput_Instance_e
{
    AssertLED = 0u,
    ControlLED,
    IMULED,
    LoggerLED,
    UnusedLED,
    
    DigitalOutput_Instance_MAX
} DigitalOutput_Instance_t;

/**
 *
 */
typedef enum DigitalOutput_State_e
{
    On,
    Off
} DigitalOutput_State_t;


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
DigitalOutput_State_t DigitalOutput_GetState(DigitalOutput_Instance_t instance);

/**
 *
 */
bool DigitalOutput_Initialise(DigitalOutput_Instance_t instance);

/**
 *
 */
bool DigitalOutput_SetState(DigitalOutput_Instance_t instance,
                            DigitalOutput_State_t newState);

#endif // __DIGITAL_OUTPUT_H
