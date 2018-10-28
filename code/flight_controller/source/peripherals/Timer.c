// --- Public header ---
#include "peripherals/Timer.h"

// --- Private header ---
#define TIMER_PRIVATE
    #include "peripherals/Timer_private.h"
#undef TIMER_PRIVATE


// --- Project includes ---
#include "macros.h"


/******************************************************************************
  Private Data
 ******************************************************************************/

TIM_HandleTypeDef Timer_handles[Timer_Instance_MAX] = { 0 };

bool Timer_isInitialised = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool Timer_Initialise(void)
{
    ENSURE(!Timer_isInitialised);

    bool success = true;
    for (uint8_t i = 0u; success && (i < Timer_Instance_MAX); i++)
    {
        const Timer_ConfigData_t *const conf = &Timer_configData[i];
        TIM_HandleTypeDef *const handle = &Timer_handles[i];

        Timer_EnableTimerClock(conf->halInstance);

        handle->Instance = conf->halInstance;
        handle->Init = conf->initStruct;
        success = (HAL_TIM_Base_Init(handle) == HAL_OK);
    }

    Timer_isInitialised = success;
    return Timer_isInitialised;
}


bool Timer_IsInitialised(void)
{
    return Timer_isInitialised;
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

void Timer_EnableTimerClock(TIM_TypeDef *instance)
{
    ENSURE(instance);

    if      (instance == TIM1)  __HAL_RCC_TIM1_CLK_ENABLE();
    else if (instance == TIM2)  __HAL_RCC_TIM2_CLK_ENABLE();
    else if (instance == TIM3)  __HAL_RCC_TIM3_CLK_ENABLE();
    else if (instance == TIM4)  __HAL_RCC_TIM4_CLK_ENABLE();
    else if (instance == TIM5)  __HAL_RCC_TIM5_CLK_ENABLE();
    else if (instance == TIM6)  __HAL_RCC_TIM6_CLK_ENABLE();
    else if (instance == TIM7)  __HAL_RCC_TIM7_CLK_ENABLE();
    else if (instance == TIM8)  __HAL_RCC_TIM8_CLK_ENABLE();
    else if (instance == TIM9)  __HAL_RCC_TIM9_CLK_ENABLE();
    else                        UNREACHABLE();
}
