#ifndef __EXTERNAL_INTERRUPT_H
#define __EXTERNAL_INTERRUPT_H


// --- Library includes ---

// --- Standard includes ---
#include <stdbool.h>


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 * Enum defining the possible states of an External Interrupt
 */
typedef enum ExternalInterrupt_State_e
{
    Risen,
    Fallen
} ExternalInterrupt_State_t;

/**
 *
 */
typedef void (*ExternalInterrupt_Callback_t)(ExternalInterrupt_State_t);

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
void ExternalInterrupt_Enable(ExternalInterrupt_Instance_t instance,
                              bool enable);

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
                                   ExternalInterrupt_Callback_t callback);


#endif // __EXTERNAL_INTERRUPT_H
