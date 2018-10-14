// --- Public header ---
#include "peripherals/DigitalOutput.h"

// --- Private header ---
#define DIGITAL_OUTPUT_PRIVATE
    #include "peripherals/DigitalOutput_private.h"
#undef DIGITAL_OUTPUT_PRIVATE


#define ENSURE(x) // @todo: Implement externally


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

DigitalOutput_State_t DigitalOutput_GetState(DigitalOutput_Instance_t instance)
{
    ENSURE(instance < DigitalOutput_Instance_MAX);

    DigitalOutput_Handle_t *const handle =
            &DigitalOutput_handles[(uint8_t)instance]; // @todo: Make this a function...

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

    // @todo: Enable port clock properly
    __HAL_RCC_GPIOD_CLK_ENABLE();
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

    const DigitalOutput_State_t currentState = 
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
