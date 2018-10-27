// --- Public header ---
#include "peripherals/Gpio.h"

// --- Private header ---
#define GPIO_PRIVATE
    #include "peripherals/Gpio_private.h"
#undef GPIO_PRIVATE


// --- Project includes ---
#include "macros.h"

// --- Library includes ---

// --- Standard includes ---


/******************************************************************************
  Private Data
 ******************************************************************************/

bool Gpio_isInitialised = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool Gpio_Initialise(void)
{
    ENSURE(!Gpio_isInitialised);

    for (uint8_t i = 0u; i < Gpio_Instance_MAX; i++)
    {
        const Gpio_ConfigData_t *const conf = &Gpio_configData[i];

        // Initialise the GPIO and start the relevant port clock
        HAL_GPIO_Init(conf->port, (GPIO_InitTypeDef *)&conf->initStruct);
        Gpio_EnablePortClock(conf->port);
    }

    Gpio_isInitialised = true;
    return Gpio_isInitialised;
}


bool Gpio_IsInitialised(void)
{
    return Gpio_isInitialised;
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
