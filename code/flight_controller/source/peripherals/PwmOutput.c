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

TIM_HandleTypeDef *PwmOutput_timerHandles[PwmOutput_Instance_MAX] = { 0 };


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

uint32_t PwmOutput_GetPulseWidth(PwmOutput_Instance_t instance)
{
    ENSURE(instance < PwmOutput_Instance_MAX);
    ENSURE(PwmOutput_isInitialised);

    const TIM_HandleTypeDef *const handle = PwmOutput_timerHandles[instance];
    const PwmOutput_ConfigData_t *const conf = &PwmOutput_configData[instance];

    return __HAL_TIM_GET_COMPARE(handle, conf->channel);
}


bool PwmOutput_Initialise(void)
{
    ENSURE(!PwmOutput_isInitialised);
    ENSURE(Timer_IsInitialised()); // @todo: Maybe make this return false instead of asserting

    bool success = true;
    for (uint8_t i = 0u; success && (i < PwmOutput_Instance_MAX); i++)
    {
        const PwmOutput_ConfigData_t *const conf = &PwmOutput_configData[i];

        // Get the timer handle and store it for later use
        TIM_HandleTypeDef *handle = Timer_GetHandle(conf->timerInstance);
        ENSURE(handle);
        PwmOutput_timerHandles[i] = handle;

        success = (HAL_TIM_PWM_ConfigChannel(handle,
                                             (TIM_OC_InitTypeDef *)&conf->initStruct,
                                             conf->channel) == HAL_OK);
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

    const TIM_HandleTypeDef *const handle = PwmOutput_timerHandles[instance];
    const PwmOutput_ConfigData_t *const conf = &PwmOutput_configData[instance];

    __HAL_TIM_SET_COMPARE(handle, conf->channel, pulseWidth);

    // @todo: Maybe add safety check and change return type to bool?
}


bool PwmOutput_Start(PwmOutput_Instance_t instance)
{
    ENSURE(instance < PwmOutput_Instance_MAX);
    ENSURE(PwmOutput_isInitialised);

    TIM_HandleTypeDef *const handle = PwmOutput_timerHandles[instance];
    const PwmOutput_ConfigData_t *const conf = &PwmOutput_configData[instance];

    HAL_TIM_PWM_Start(handle, conf->channel);
    return true; // @todo: Maybe store state or check if it's already started?
}


bool PwmOutput_Stop(PwmOutput_Instance_t instance)
{
    ENSURE(instance < PwmOutput_Instance_MAX);
    ENSURE(PwmOutput_isInitialised);

    TIM_HandleTypeDef *const handle = PwmOutput_timerHandles[instance];
    const PwmOutput_ConfigData_t *const conf = &PwmOutput_configData[instance];

    HAL_TIM_PWM_Stop(handle, conf->channel);
    return true; // @todo: Maybe store state or check if it's already started?
}
