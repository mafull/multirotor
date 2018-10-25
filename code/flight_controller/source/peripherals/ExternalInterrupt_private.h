// Incorrect usage guard
#ifndef EXTERNAL_INTERRUPT_PRIVATE
    #error Private interface should not be included here!
#endif // EXTERNAL_INTERRUPT_PRIVATE

#ifndef __EXTERNAL_INTERRUPT_PRIVATE_H
#define __EXTERNAL_INTERRUPT_PRIVATE_H


// --- Public header ---
#include "peripherals/ExternalInterrupt.h"

// --- Project includes ---

// --- Library includes ---

// --- Standard includes ---


/******************************************************************************
  Private Defines
 ******************************************************************************/

/**
 *
 */
#define EXTERNAL_INTERRUPT_LINE_COUNT_GPIO  16u
#define EXTERNAL_INTERRUPT_LINE_COUNT       (EXTERNAL_INTERRUPT_LINE_COUNT_GPIO)


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 *
 */
typedef struct Uart_Handle_s
{
    ExternalInterrupt_Instance_t instance;

    bool initialised;
    ExternalInterrupt_CallbackFunction_t callback;

    GPIO_InitTypeDef initStruct;
    GPIO_TypeDef *port;
} ExternalInterrupt_Handle_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern ExternalInterrupt_Handle_t ExternalInterrupt_handles[ExternalInterrupt_Instance_MAX];

/**
 *
 */
extern ExternalInterrupt_CallbackFunction_t ExternalInterrupt_callbackFunctions[EXTERNAL_INTERRUPT_LINE_COUNT];


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */

#endif // __EXTERNAL_INTERRUPT_PRIVATE_H
