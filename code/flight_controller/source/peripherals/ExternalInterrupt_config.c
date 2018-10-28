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
          | GPIO Instance   | line
          |                 |  | IRQ Number
        */
        { Gpio_MPU6050_Int, 4, EXTI4_IRQn }, // MPU6050_Int
        { Gpio_UserButton , 0, EXTI0_IRQn }, // UserButton
    };
