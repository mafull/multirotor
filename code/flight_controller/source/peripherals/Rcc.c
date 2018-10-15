// --- Public header ---
#include "peripherals/Rcc.h"

// --- Private header ---
#define RCC_PRIVATE
    #include "peripherals/Rcc_private.h"
#undef RCC_PRIVATE

// --- Project includes ---
#include "macros.h"


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool Rcc_Initialise(void)
{
    ENSURE(true); // @todo: Add check for not already initialised

    HAL_Init();

    // @todo: Add commenting
    __PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    // @todo: Use return values == HAL_OK
    HAL_RCC_OscConfig(&Rcc_oscInitStruct);
    HAL_RCC_ClockConfig(&Rcc_clkInitStruct, Rcc_flashLatency);

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000u); // @todo: Make setting
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    HAL_NVIC_SetPriority(SysTick_IRQn, 15u, 0u);

    return true;
}
