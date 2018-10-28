// --- Public header ---
#include "peripherals/ExternalInterrupt.h"

// --- Private header ---
#define EXTERNAL_INTERRUPT_PRIVATE
    #include "peripherals/ExternalInterrupt_private.h"
#undef EXTERNAL_INTERRUPT_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

const ExternalInterrupt_ConfigData_t ExternalInterrupt_configData[ExternalInterrupt_Instance_MAX] = 
    {
        /*
          | GPIO Instance
        */
        { Gpio_MPU6050_Int }, // MPU6050_Int
        { Gpio_UserButton  }, // UserButton
    };
