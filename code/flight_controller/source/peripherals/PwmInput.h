#ifndef __PWM_INPUT_H
#define __PWM_INPUT_H


// --- Project includes ---

// --- Library includes ---

// --- Standard includes ---
#include <stdbool.h>


/******************************************************************************
  Public Defines
 ******************************************************************************/


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 *
 */
typedef enum PwmInput_Instance_e
{
    // Timer 2
    In_Ch1 = 0u,
    In_Ch2,
    In_Ch3,
    In_Ch4,

    // Timer 3
    // In_Ch5,
    // In_Ch6,
    // In_Ch7,
    // In_Ch8,

    PwmInput_Instance_MAX
} PwmInput_Instance_t;


/******************************************************************************
  Public Data
 ******************************************************************************/


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool PwmInput_Initialise(void);

/**
 *
 */
bool PwmInput_IsInitialised(void);

/**
 *
 */
bool PwmInput_Start(PwmInput_Instance_t instance);

/**
 *
 */
bool PwmInput_Stop(PwmInput_Instance_t instance);


#endif // __PWM_INPUT_H
