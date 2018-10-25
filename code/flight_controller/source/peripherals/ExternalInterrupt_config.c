// --- Public header ---
#include "peripherals/ExternalInterrupt.h"

// --- Private header ---
#define EXTERNAL_INTERRUPT_PRIVATE
    #include "peripherals/ExternalInterrupt_private.h"
#undef EXTERNAL_INTERRUPT_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

ExternalInterrupt_Handle_t ExternalInterrupt_handles[ExternalInterrupt_Instance_Max] = 
    {
        {
            .instance = MPU6050Int,

            .initStruct = 
            {
                .Mode   = GPIO_MODE_IT_RISING,
                .Pin    = GPIO_PIN_4,
                .Pull   = GPIO_NOPULL,
                .Speed  = GPIO_SPEED_LOW
            },
            .port       = GPIOD
        }
    };