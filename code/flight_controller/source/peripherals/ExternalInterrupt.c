// --- Public header ---
#include "peripherals/ExternalInterrupt.h"

// --- Private header ---
#define EXTERNAL_INTERRUPT_PRIVATE
    #include "peripherals/ExternalInterrupt_private.h"
#undef EXTERNAL_INTERRUPT_PRIVATE


// --- Project includes ---

// --- Library includes ---

// --- Standard includes ---


/******************************************************************************
  Private Data
 ******************************************************************************/

extern ExternalInterrupt_CallbackFunction_t ExternalInterrupt_callbackFunctions[EXTERNAL_INTERRUPT_LINE_COUNT] = { 0 };


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool ExternalInterrupt_Initialise(ExternalInterrupt_Instance_t instance)
{
    ENSURE(instance < ExternalInterrupt_Instance_MAX);

    // Get the relevant handle
    ExternalInterrupt_Handle_t *const handle =
        &ExternalInterrupt_handles[(uint8_t)instance];

    // Ensure its instance is configured correctly and it's not initialised
    ENSURE(instance == handle->instance);
    ENSURE(!handle->initialised);

    // Enable the relevant port clock and initialise the pin
    ExternalInterrupt_EnablePortClock(handle->port);
    HAL_GPIO_Init(handle->port, &handle->initStruct);
    handle->initialised = true;

    // Enable the EXTI
    ExternalInterrupt_EnableEXTI();

    return handle->initialised;
}


bool ExternalInterrupt_IsInitialised(ExternalInterrupt_Instance_t instance)
{
    ENSURE(instance < ExternalInterrupt_Instance_MAX);
    return ExternalInterrupt_handles[(uint8_t)instance].initialised; // @todo: rename to isInitialise + same for other modules
}


void ExternalInterrupt_SetCallback(ExternalInterrupt_Instance_t instance,
                                   ExternalInterrupt_CallbackFunction_t callback)
{
    // @todo: Somehow add to extern ExternalInterrupt_callbackFunctions
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

void EXTI0_IRQHandler(void)
{
    const ExternalInterrupt_CallbackFunction_t callback = ExternalInterrupt_callbackFunctions[0];
    
    if (callback)
    {
        const bool isHigh = HAL_GPIO_ReadPin(handle->port,
                          handle->initStruct.Pin) == GPIO_PIN_SET)
        callback();
    }

    EXTI->PR = (1 << 0); // @todo: Maybe use __HAL_GPIO_EXTI_CLEAR_IT()
}

/*
void EXTI0_IRQHandler(void)
{
    // Checks whether the interrupt from EXTI0 or not
    if (EXTI_GetITStatus(EXTI_Line0))
    {
        // Toggle orange LED (GPIO13)
        GPIO_ToggleBits(GPIOD, GPIO_Pin_13);

        // Clears the EXTI line pending bit
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
*/

// HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
// {

// }

// void EXTI1_IRQHandler(void)
// void EXTI2_IRQHandler(void)
// void EXTI3_IRQHandler(void)
// void EXTI4_IRQHandler(void)
// void EXTI9_5_IRQHandler(void)
// void EXTI15_10_IRQHandler(void)