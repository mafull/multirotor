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
        { Gpio_AssertLed  }, // AssertLed
        { Gpio_ControlLed }, // ControlLed
        { Gpio_ImuLed     }, // ImuLed
        { Gpio_LoggerLed  }, // LoggerLed
        { Gpio_UnusedLed  }, // UnusedLed
    };
