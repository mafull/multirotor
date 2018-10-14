// --- Private header ---
#define DIGITAL_OUTPUT_PRIVATE
    #include "peripherals/DigitalOutput_private.h"
#undef DIGITAL_OUTPUT_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

DigitalOutput_Handle_t DigitalOutput_handles[DigitalOutput_Instance_MAX] = 
    {
        {
            .instance   = AssertLed,

            .initStruct = 
            {
                .Mode   = GPIO_MODE_OUTPUT_PP,
                .Pin    = GPIO_PIN_1,
                .Pull   = GPIO_NOPULL,
                .Speed  = GPIO_SPEED_LOW,
            },
            .port       = GPIOD
        },
        {
            .instance   = ControlLed,

            .initStruct = 
            {
                .Mode   = GPIO_MODE_OUTPUT_PP,
                .Pin    = GPIO_PIN_12,
                .Pull   = GPIO_NOPULL,
                .Speed  = GPIO_SPEED_LOW,
            },
            .port       = GPIOD
        },
        {
            .instance   = IMULed,

            .initStruct = 
            {
                .Mode   = GPIO_MODE_OUTPUT_PP,
                .Pin    = GPIO_PIN_13,
                .Pull   = GPIO_NOPULL,
                .Speed  = GPIO_SPEED_LOW,
            },
            .port       = GPIOD
        },
        {
            .instance   = LoggerLed,

            .initStruct = 
            {
                .Mode   = GPIO_MODE_OUTPUT_PP,
                .Pin    = GPIO_PIN_14,
                .Pull   = GPIO_NOPULL,
                .Speed  = GPIO_SPEED_LOW,
            },
            .port       = GPIOD
        },
        {
            .instance   = UnusedLed,

            .initStruct = 
            {
                .Mode   = GPIO_MODE_OUTPUT_PP,
                .Pin    = GPIO_PIN_15,
                .Pull   = GPIO_NOPULL,
                .Speed  = GPIO_SPEED_LOW,
            },
            .port       = GPIOD
        }
    };
