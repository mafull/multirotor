#ifndef __PWM_OUTPUT_H
#define __PWM_OUTPUT_H


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
    Out_Ch1 = 0u,
    Out_Ch2,
    Out_Ch3,
    Out_Ch4,

    // Timer 4
    // Out_Ch5,
    // Out_Ch6,
    // Out_Ch7,
    // Out_Ch8,

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
