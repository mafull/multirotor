// --- Public header ---
#include "peripherals/DigitalOutput.h"

// --- Private header ---
#define DIGITAL_OUTPUT_PRIVATE
    #include "peripherals/DigitalOutput_private.h"
#undef DIGITAL_OUTPUT_PRIVATE

// --- Project includes ---
#include "macros.h"


/******************************************************************************
  Private Data
 ******************************************************************************/

bool DigitalOutput_isInitialised = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

DigitalOutput_State_t DigitalOutput_GetState(DigitalOutput_Instance_t instance)
{
    ENSURE(instance < DigitalOutput_Instance_MAX);
    ENSURE(DigitalOutput_isInitialised);

    const Gpio_Instance_t gpioInstance = DigitalOutput_configData[instance].gpioInstance;

    return (Gpio_GetState(gpioInstance) == High) ? On : Off;
}


bool DigitalOutput_Initialise(void)
{
    ENSURE(!DigitalOutput_isInitialised);

    // All we need to do is check that the GPIOs are initialised
    ENSURE(Gpio_IsInitialised()); // @todo: Maybe make this the ret value, don't assert?

    DigitalOutput_isInitialised = true;
    return DigitalOutput_isInitialised;
}


bool DigitalOutput_IsInitialised(void)
{
    return DigitalOutput_isInitialised;
}


bool DigitalOutput_SetState(DigitalOutput_Instance_t instance,
                            DigitalOutput_State_t newState)
{
    ENSURE(instance < DigitalOutput_Instance_MAX);
    ENSURE(DigitalOutput_isInitialised);

    const Gpio_Instance_t gpioInstance = DigitalOutput_configData[instance].gpioInstance;

    return Gpio_SetState(gpioInstance,
                         (newState == On) ? High : Low);
}

void DigitalOutput_ToggleState(DigitalOutput_Instance_t instance)
{
    ENSURE(instance < DigitalOutput_Instance_MAX);
    ENSURE(DigitalOutput_isInitialised);

    const DigitalOutput_State_t currentState = DigitalOutput_GetState(instance);
    DigitalOutput_SetState(instance,
                           (currentState == On) ? Off : On);
}