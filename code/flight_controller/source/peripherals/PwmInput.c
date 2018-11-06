// --- Public header ---
#include "peripherals/PwmInput.h"

// --- Private header ---
#define PWM_INPUT_PRIVATE
    #include "peripherals/PwmInput_private.h"
#undef PWM_INPUT_PRIVATE


// --- Project includes ---
#include "macros.h"


/******************************************************************************
  Private Data
 ******************************************************************************/

bool PwmInput_isInitialised = false;

TIM_HandleTypeDef *PwmInput_timerHandles[PwmInput_Instance_MAX] = { 0 };


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool PwmInput_Initialise(void)
{
    ENSURE(!PwmInput_isInitialised);
    ENSURE(Timer_IsInitialised()); // @todo: Maybe make this return false instead of asserting

    bool success = true;
    for (uint8_t i = 0u; success && (i < PwmInput_Instance_MAX); i++)
    {
        const PwmInput_ConfigData_t *const conf = &PwmInput_configData[i];

        // Get the timer handle and store it for later use
        TIM_HandleTypeDef *handle = Timer_GetHandle(conf->timerInstance);
        ENSURE(handle);
        PwmInput_timerHandles[i] = handle;

        success = (HAL_TIM_IC_ConfigChannel(handle,
                                            (TIM_IC_InitTypeDef *)&conf->initStruct,
                                            conf->channel) == HAL_OK);
    }

    PwmInput_isInitialised = success;
    return PwmInput_isInitialised;
}


bool PwmInput_IsInitialised(void)
{
    return PwmInput_isInitialised;
}


bool PwmInput_Start(PwmInput_Instance_t instance)
{
    ENSURE(instance < PwmInput_Instance_MAX);

    TIM_HandleTypeDef *const handle = PwmInput_timerHandles[instance];
    const PwmInput_ConfigData_t *const conf = &PwmInput_configData[instance];

    HAL_TIM_IC_Start_IT(handle, conf->channel);
    return true; // @todo: Maybe store state or check if it's already started?
}


bool PwmInput_Stop(PwmInput_Instance_t instance)
{
    ENSURE(instance < PwmInput_Instance_MAX);

    TIM_HandleTypeDef *const handle = PwmInput_timerHandles[instance];
    const PwmInput_ConfigData_t *const conf = &PwmInput_configData[instance];

    HAL_TIM_IC_Stop_IT(handle, conf->channel);
    return true; // @todo: Maybe store state or check if it's already stopped?
}
