#ifndef __PWM_OUTPUT_H
#define __PWM_OUTPUT_H


// --- Project includes ---

// --- Library includes ---

// --- Standard includes ---
#include <stdbool.h>
#include <stdint.h>


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 *
 */
typedef enum PwmOutput_Instance_e
{
    // Timer 1
    Ch1 = 0u,
    Ch2,
    Ch3,
    Ch4,

    // Timer 4
    // Ch5,
    // Ch6,
    // Ch7,
    // Ch8,

    PwmOutput_Instance_MAX
} PwmOutput_Instance_t;


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool PwmOutput_Initialise(void);

/**
 *
 */
bool PwmOutput_IsInitialised(void);

/**
 *
 */
void PwmOutput_SetPulseWidth(PwmOutput_Instance_t instance, uint32_t pulseWidth);

/**
 *
 */
bool PwmOutput_Start(PwmOutput_Instance_t instance);

/**
 *
 */
bool PwmOutput_Stop(PwmOutput_Instance_t instance);


#endif // __PWM_OUTPUT_H
