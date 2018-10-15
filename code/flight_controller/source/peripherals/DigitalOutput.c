// --- Public header ---
#include "peripherals/DigitalOutput.h"

// --- Private header ---
#define DIGITAL_OUTPUT_PRIVATE
    #include "peripherals/DigitalOutput_private.h"
#undef DIGITAL_OUTPUT_PRIVATE

// --- Project includes ---
#include "macros.h"


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

DigitalOutput_State_t DigitalOutput_GetState(DigitalOutput_Instance_t instance)
{
    ENSURE(instance < DigitalOutput_Instance_MAX);

    DigitalOutput_Handle_t *const handle =
            &DigitalOutput_handles[(uint8_t)instance]; // @todo: Make this a function...

    ENSURE(handle->initialised);

    return (HAL_GPIO_ReadPin(handle->port,
                             handle->initStruct.Pin)
                == GPIO_PIN_SET) ? On : Off;
}


bool DigitalOutput_Initialise(DigitalOutput_Instance_t instance)
{
    ENSURE(instance < DigitalOutput_Instance_MAX);

    DigitalOutput_Handle_t *const handle =
        &DigitalOutput_handles[(uint8_t)instance];

    ENSURE(instance == handle->instance);
    ENSURE(!handle->initialised);

    DigitalOutput_EnablePortClock(handle->port);
    HAL_GPIO_Init(handle->port, &handle->initStruct);

    handle->initialised = true;

    return handle->initialised;
}


bool DigitalOutput_SetState(DigitalOutput_Instance_t instance,
                            DigitalOutput_State_t newState)
{
    ENSURE(instance < DigitalOutput_Instance_MAX);

    DigitalOutput_Handle_t *const handle =
            &DigitalOutput_handles[(uint8_t)instance]; // @todo: Make this a function...

    ENSURE(handle->initialised);

    const DigitalOutput_State_t currentState = // @todo: Make func?
        (HAL_GPIO_ReadPin(handle->port,
                          handle->initStruct.Pin) == GPIO_PIN_SET) ? On : Off;

    bool success = false;
    if (newState != currentState)
    {
        HAL_GPIO_WritePin(handle->port,
                          handle->initStruct.Pin,
                          (newState == On) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        success = true;
    }
    
    return success;
}


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

void DigitalOutput_EnablePortClock(GPIO_TypeDef *port)
{
    ENSURE(port);

    if      (port == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    else if (port == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    else if (port == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    else if (port == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
    else if (port == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();
    else if (port == GPIOF) __HAL_RCC_GPIOF_CLK_ENABLE();
    else if (port == GPIOG) __HAL_RCC_GPIOG_CLK_ENABLE();
    else if (port == GPIOH) __HAL_RCC_GPIOH_CLK_ENABLE();
    else                    UNREACHABLE();
}
