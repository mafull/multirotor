// --- Public header ---
#include "peripherals/Gpio.h"

// --- Private header ---
#define GPIO_PRIVATE
    #include "peripherals/Gpio_private.h"
#undef GPIO_PRIVATE


// --- Project includes ---
#include "macros.h"


/******************************************************************************
  Private Data
 ******************************************************************************/

bool Gpio_isInitialised = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

Gpio_State_t Gpio_GetState(Gpio_Instance_t instance)
{
    ENSURE(instance < Gpio_Instance_MAX);
    ENSURE(Gpio_isInitialised);

    const Gpio_ConfigData_t *const conf = &Gpio_configData[instance];
    const GPIO_PinState state = HAL_GPIO_ReadPin(conf->port, conf->initStruct.Pin);

    return (state == GPIO_PIN_SET) ? High : Low;
}


bool Gpio_Initialise(void)
{
    ENSURE(!Gpio_isInitialised);

    for (uint8_t i = 0u; i < Gpio_Instance_MAX; i++)
    {
        const Gpio_ConfigData_t *const conf = &Gpio_configData[i];

        // Initialise the GPIO after starting the relevant port clock
        Gpio_EnablePortClock(conf->port);
        HAL_GPIO_Init(conf->port, (GPIO_InitTypeDef *)&conf->initStruct);
    }

    Gpio_isInitialised = true;
    return Gpio_isInitialised;
}


bool Gpio_IsInitialised(void)
{
    return Gpio_isInitialised;
}


bool Gpio_SetState(Gpio_Instance_t instance, Gpio_State_t newState)
{
    ENSURE(instance < Gpio_Instance_MAX);
    ENSURE(Gpio_isInitialised);

    bool success = false;
    if (Gpio_GetState(instance) != newState)
    {
        const Gpio_ConfigData_t *const conf = &Gpio_configData[instance];

        HAL_GPIO_WritePin(conf->port,
                          conf->initStruct.Pin,
                          newState == High ? GPIO_PIN_SET : GPIO_PIN_RESET);
        success = true;
    }

    return success;
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

void Gpio_EnablePortClock(GPIO_TypeDef *port)
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
