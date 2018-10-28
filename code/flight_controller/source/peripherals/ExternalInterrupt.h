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
    MPU6050_Int = 0u,
    UserButton,

    ExternalInterrupt_Instance_MAX
} ExternalInterrupt_Instance_t;


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool ExternalInterrupt_Initialise(void);

/**
 *
 */
bool ExternalInterrupt_IsInitialised(void);

/**
 *
 */
void ExternalInterrupt_SetCallback(ExternalInterrupt_Instance_t instance,
                                   ExternalInterrupt_CallbackFunction_t callback);


#endif // __EXTERNAL_INTERRUPT_H
