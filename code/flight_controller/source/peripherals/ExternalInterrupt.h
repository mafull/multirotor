#ifndef __EXTERNAL_INTERRUPT_H
#define __EXTERNAL_INTERRUPT_H


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
typedef void (*ExternalInterrupt_CallbackFunction_t)(bool);

/**
 *
 */
typedef enum ExternalInterrupt_Instance_e
{
    MPU6050Int = 0u,
    UserButton,

    ExternalInterrupt_Instance_MAX
} ExternalInterrupt_Instance_t;


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool ExternalInterrupt_Initialise(ExternalInterrupt_Instance_t instance);

/**
 *
 */
bool ExternalInterrupt_IsInitialised(ExternalInterrupt_Instance_t instance);

/**
 *
 */
void ExternalInterrupt_SetCallback(ExternalInterrupt_Instance_t instance,
                                   ExternalInterrupt_CallbackFunction_t callback);


#endif // __EXTERNAL_INTERRUPT_H
