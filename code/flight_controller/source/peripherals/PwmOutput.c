// --- Public header ---
#include "peripherals/PwmOutput.h"

// --- Private header ---
#define PWM_OUTPUT_PRIVATE
    #include "peripherals/PwmOutput_private.h"
#undef PWM_OUTPUT_PRIVATE


// --- Project includes ---
#include "macros.h"

// --- Library includes ---

// --- Standard includes ---


/******************************************************************************
  Private Data
 ******************************************************************************/

bool PwmOutput_isInitialised = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool PwmOutput_Initialise(void)
{
    ENSURE(!PwmOutput_isInitialised);



    bool success = true;
    for (uint8_t i = 0u; success && (i < PwmOutput_Instance_MAX); i++)
    {
        const PwmOutput_ConfigData_t *const conf = &PwmOutput_configData[i];

        success = Timer_ConfigureOC(conf->timerInstance, &conf->ocConfigData);
    }

    PwmOutput_isInitialised = success;
    return PwmOutput_isInitialised;
}


bool PwmOutput_IsInitialised(void)
{
    return PwmOutput_isInitialised;
}


void PwmOutput_SetPulseWidth(PwmOutput_Instance_t instance, uint32_t pulseWidth)
{
    ENSURE(instance < PwmOutput_Instance_MAX);
    ENSURE(PwmOutput_isInitialised);

    const PwmOutput_ConfigData_t *const conf = &PwmOutput_configData[instance];

    Timer_SetPWMPulseWidth(conf->timerInstance, conf->channel, pulseWidth);
}


bool PwmOutput_Start(PwmOutput_Instance_t instance)
{
    ENSURE(instance < PwmOutput_Instance_MAX);
    ENSURE(PwmOutput_isInitialised);

    const PwmOutput_ConfigData_t *const conf = &PwmOutput_configData[instance];

    return Timer_StartPWM(conf->timerInstance, conf->channel);
}


bool PwmOutput_Stop(PwmOutput_Instance_t instance)
{
    ENSURE(instance < PwmOutput_Instance_MAX);
    ENSURE(PwmOutput_isInitialised);

    const PwmOutput_ConfigData_t *const conf = &PwmOutput_configData[instance];

    return Timer_StopPWM(conf->timerInstance, conf->channel);
}




/******************************************************************************
  Private Function Implementations
 ******************************************************************************/
