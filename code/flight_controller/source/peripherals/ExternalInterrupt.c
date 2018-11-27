// --- Public header ---
#include "peripherals/ExternalInterrupt.h"

// --- Private header ---
#define EXTERNAL_INTERRUPT_PRIVATE
    #include "peripherals/ExternalInterrupt_private.h"
#undef EXTERNAL_INTERRUPT_PRIVATE


// --- Project includes ---
#include "macros.h"


/******************************************************************************
  Private Data
 ******************************************************************************/

ExternalInterrupt_CallbackFunction_t ExternalInterrupt_callbackFunctions[EXTERNAL_INTERRUPT_LINE_COUNT] = { 0 };
Gpio_Instance_t ExternalInterrupt_gpioPins[EXTERNAL_INTERRUPT_LINE_COUNT] = { 0 };

bool ExternalInterrupt_isInitialised = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

void ExternalInterrupt_EnableIT(ExternalInterrupt_Instance_t instance, bool enable)
{
    ENSURE(instance < ExternalInterrupt_Instance_MAX);
    ENSURE(ExternalInterrupt_isInitialised);

    const ExternalInterrupt_ConfigData_t *const conf = &ExternalInterrupt_configData[instance]; // @todo: Make a macro...

    enable ? HAL_NVIC_EnableIRQ(conf->irqN) : HAL_NVIC_DisableIRQ(conf->irqN);
}


bool ExternalInterrupt_Initialise(void)
{
    ENSURE(!ExternalInterrupt_isInitialised);

    ENSURE(Gpio_IsInitialised()); // @todo: Maybe make this the ret value, don't assert?

    for (uint8_t i = 0u; i < ExternalInterrupt_Instance_MAX; i++)
    {
        const ExternalInterrupt_ConfigData_t *const conf = &ExternalInterrupt_configData[i]; // @todo: Make a macro...

        ExternalInterrupt_gpioPins[conf->line] = conf->gpioInstance;

        HAL_NVIC_SetPriority(conf->irqN, 6u, 0); // @todo: Change priorities/add to config data
    }

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
    ENSURE(instance < ExternalInterrupt_Instance_MAX);
    ENSURE(ExternalInterrupt_isInitialised);
    ENSURE(callback);

    const ExternalInterrupt_ConfigData_t *const conf = &ExternalInterrupt_configData[instance]; // @todo: Make a macro...
    ExternalInterrupt_callbackFunctions[conf->line] = callback;
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

void ExternalInterrupt_GenericHandler(uint8_t line)
{
    ENSURE(line < EXTERNAL_INTERRUPT_LINE_COUNT);

    const uint16_t lineDef = (uint16_t)(1 << line);
    if (__HAL_GPIO_EXTI_GET_IT(lineDef))
    {
        const ExternalInterrupt_CallbackFunction_t callback = ExternalInterrupt_callbackFunctions[line];
        
        if (callback)
        {
            const Gpio_Instance_t gpioInstance = ExternalInterrupt_gpioPins[line];
            const Gpio_State_t gpioState = (Gpio_GetState(gpioInstance));
            callback((gpioState == High) ? Risen : Fallen);
        }

        __HAL_GPIO_EXTI_CLEAR_IT(lineDef);
    }
}


#define EXTIn_HANDLER(n) \
    void EXTI##n##_IRQHandler(void) \
    { \
        ExternalInterrupt_GenericHandler(n); \
    }


#define EXTIn1_n2_HANDLER(n1, n2) \
    void EXTI##n1##_##n2##_IRQHandler(void) \
    { \
        for (uint8_t i = n1; i <= n2; i++) \
        { \
            ExternalInterrupt_GenericHandler(i); \
        } \
    }


EXTIn_HANDLER(0);
EXTIn_HANDLER(1);
EXTIn_HANDLER(2);
EXTIn_HANDLER(3);
EXTIn_HANDLER(4);
EXTIn1_n2_HANDLER(9, 5);
EXTIn1_n2_HANDLER(15, 10);
