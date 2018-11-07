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

PwmInput_Instance_t PwmInput_timerInstanceMap[TIMER_COUNT][TIMER_CHANNEL_COUNT] = { 0 };

PwmInput_PulseData_t PwmInput_pulseData[PwmInput_Instance_MAX] = { 0 };


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool PwmInput_GetPulseData(PwmInput_Instance_t instance,
                           PwmInput_PulseData_t *const dataOut)
{
    ENSURE(instance < PwmInput_Instance_MAX);
    ENSURE(dataOut);
    ENSURE(PwmInput_isInitialised);

    *dataOut = PwmInput_pulseData[instance];

    return (PwmInput_pulseData[instance].duration != 0u);
}


bool PwmInput_GetPulseWidth(PwmInput_Instance_t instance,
                            uint32_t *const pulseWidthOut)
{
    ENSURE(instance < PwmInput_Instance_MAX);
    ENSURE(PwmInput_isInitialised);

    *pulseWidthOut = PwmInput_pulseData[instance].duration;

    return (PwmInput_pulseData[instance].duration != 0u);
}


bool PwmInput_Initialise(void)
{
    ENSURE(!PwmInput_isInitialised);
    ENSURE(Timer_IsInitialised()); // @todo: Maybe make this return false instead of asserting
    ENSURE(Gpio_IsInitialised());

    // Clear the timer instance map before use in interrupt handlers
    for (uint8_t tim = 0u; tim < TIMER_COUNT; tim++)
    {
        for (uint8_t ch = 0u; ch < TIMER_CHANNEL_COUNT; ch++)
        {
            PwmInput_timerInstanceMap[tim][ch] = PwmInput_Instance_MAX;
        }
    }

    bool success = true;
    for (uint8_t i = 0u; success && (i < PwmInput_Instance_MAX); i++)
    {
        const PwmInput_ConfigData_t *const conf = &PwmInput_configData[i];

        // Update the timer instance map
        PwmInput_timerInstanceMap[conf->timerIndex][conf->channelIndex] = (PwmInput_Instance_t)i;

        // Get the timer handle and store it for later use
        TIM_HandleTypeDef *handle = Timer_GetHandle(conf->timerInstance);
        ENSURE(handle);
        PwmInput_timerHandles[i] = handle;

        success = (HAL_TIM_IC_ConfigChannel(handle,
                                            (TIM_IC_InitTypeDef *)&conf->initStruct,
                                            conf->channel) == HAL_OK);

        HAL_NVIC_SetPriority(TIM2_IRQn, 1, 1);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

        // @todo: Consider DMA - CCR reg value copied straight into datastruct?
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

    char str[50];
    memset(str, 0, 50);
    uint32_t *p = TIM2;
    for (uint8_t i = 0; i < 21u; i++)
    {
        snprintf(str, 50, "%2u: addr: 0x%08lX  value: 0x%08lX", i, p, *p);
        LOG_DEBUG(str);
        p++;
    }
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


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/
#include "Logger.h"
void PwmInput_GenericHandler(uint32_t timerIndex)
{
    ENSURE(timerIndex < TIMER_COUNT);

    // Check all of this timer's channels
    for (uint8_t ch = 0; ch < TIMER_CHANNEL_COUNT; ch++)
    {
        // Get a PwmInstance (if there is one) from the map
        const PwmInput_Instance_t instance = PwmInput_timerInstanceMap[timerIndex][ch];
        if (instance == PwmInput_Instance_MAX)
        {
            // No instance has been configured to use this channel
            continue;
        }

        TIM_HandleTypeDef *const handle = PwmInput_timerHandles[instance];

        // static char str[16];
        // memset(str, 0, 16);
        // snprintf(str, 16, "0x%lX", (uint32_t)handle->Instance->SR);
        // LOG_DEBUG(str);

        // Check if an interrupt has occurred on this channel
        const uint32_t interruptFlag = (1u << ch);
        if (__HAL_TIM_GET_FLAG(handle, interruptFlag))
        {
            const PwmInput_ConfigData_t *const conf = &PwmInput_configData[instance];

            // Read the captured value - this clears the interrupt flag
            const uint32_t capturedValue = HAL_TIM_ReadCapturedValue(handle, conf->channel);

            // Update the pulse data for this channel
            PwmInput_PulseData_t *const pulse = &PwmInput_pulseData[instance];
            if (Gpio_GetState(conf->gpioInstance) == High) // Rising edge
            {
                pulse->startTime = capturedValue;
                // if (ch == 0) LOG_DEBUG("rising 0");
                // else if (ch == 1) LOG_DEBUG("rising 1");
                // else if (ch == 2) LOG_DEBUG("rising 2");
                // else if (ch == 3) LOG_DEBUG("rising 3");
            }
            else // Falling edge - pulse complete
            {
                pulse->endTime = capturedValue;
                pulse->duration = (pulse->endTime - pulse->startTime);
                // if (ch == 0) LOG_DEBUG("falling 0");
                // else if (ch == 1) LOG_DEBUG("falling 1");
                // else if (ch == 2) LOG_DEBUG("falling 2");
                // else if (ch == 3) LOG_DEBUG("falling 3");
            }

            __HAL_TIM_CLEAR_FLAG(handle, interruptFlag); // REMOVE
            break; // Don't waste time checking for other channels' flags
        }
    }
}


#define TIMn_HANDLER(n) \
    void TIM##n##_IRQHandler(void) \
    { \
        PwmInput_GenericHandler(n-1); \
    }

TIMn_HANDLER(2);
TIMn_HANDLER(3);