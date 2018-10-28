// --- Public header ---
#include "peripherals/ExternalInterrupt.h"

// --- Private header ---
#define EXTERNAL_INTERRUPT_PRIVATE
    #include "peripherals/ExternalInterrupt_private.h"
#undef EXTERNAL_INTERRUPT_PRIVATE


// --- Project includes ---
#include "macros.h"

// --- Library includes ---

// --- Standard includes ---


/******************************************************************************
  Private Data
 ******************************************************************************/

ExternalInterrupt_CallbackFunction_t ExternalInterrupt_callbackFunctions[EXTERNAL_INTERRUPT_LINE_COUNT] = { 0 };

bool ExternalInterrupt_isInitialised = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool ExternalInterrupt_Initialise(void)
{
    ENSURE(!ExternalInterrupt_isInitialised);

    // All we need to do is check that the GPIOs are initialised
    ENSURE(Gpio_IsInitialised()); // @todo: Maybe make this the ret value, don't assert?

    ExternalInterrupt_isInitialised = true;
    return ExternalInterrupt_isInitialised;
}


bool ExternalInterrupt_IsInitialised(void)
{
    return ExternalInterrupt_isInitialised;
}


void ExternalInterrupt_SetCallback(ExternalInterrupt_Instance_t instance,
                                   ExternalInterrupt_CallbackFunction_t callback)
{
    // @todo: Somehow add to extern ExternalInterrupt_callbackFunctions
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/




// #define EXTIn_HANDLER(n) \
//     void EXTI##n##_IRQHandler(void) \
//     { \
//         const ExternalInterrupt_CallbackFunction_t callback = ExternalInterrupt_callbackFunctions[n]; \
//         if (callback) \
//         { \
//             callback(true); \
//         } \
//         EXTI->PR = (1 << n); \
//     }

// EXTIn_HANDLER(0)
// EXTIn_HANDLER(1)
// EXTIn_HANDLER(2)
// EXTIn_HANDLER(3)
// EXTIn_HANDLER(4)

// void EXTI0_IRQHandler(void)
// {
//     const ExternalInterrupt_CallbackFunction_t callback = ExternalInterrupt_callbackFunctions[0];
    
//     if (callback)
//     {
//         const bool isHigh = (HAL_GPIO_ReadPin(handle->port,
//                           handle->initStruct.Pin) == GPIO_PIN_SET)
//         callback();
//     }

//     EXTI->PR = (1 << 0); // @todo: Maybe use __HAL_GPIO_EXTI_CLEAR_IT()
// }

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