#ifndef __TIMER_H
#define __TIMER_H


// --- Project includes ---

// --- Library includes ---

// --- Standard includes ---
#include <stdbool.h>


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 *
 */
typedef enum Timer_Instance_e
{
    Timer1 = 0u,
    Timer2,
    Timer3,
    Timer4,

    Timer_Instance_MAX
} Timer_Instance_t;


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool Timer_Initialise(void);

/**
 *
 */
bool Timer_IsInitialised(void);


#endif // __TIMER_H
