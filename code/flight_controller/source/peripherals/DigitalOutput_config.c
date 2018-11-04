// --- Private header ---
#define DIGITAL_OUTPUT_PRIVATE
    #include "peripherals/DigitalOutput_private.h"
#undef DIGITAL_OUTPUT_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

const DigitalOutput_ConfigData_t DigitalOutput_configData[DigitalOutput_Instance_MAX] =
    {
        /*
                         | GPIO Instance
        */
        [AssertLed]  = { Gpio_AssertLed  },
        [ControlLed] = { Gpio_ControlLed },
        [ImuLed]     = { Gpio_ImuLed     },
        [LoggerLed]  = { Gpio_LoggerLed  },
        [UnusedLed]  = { Gpio_UnusedLed  },
    };
