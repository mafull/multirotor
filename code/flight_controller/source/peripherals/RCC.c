// --- Public header ---
#include "peripherals/RCC.h"

// --- Private header ---
#define RCC_PRIVATE
    #include "peripherals/RCC_private.h"
#undef RCC_PRIVATE


#define ENSURE(x) // @todo: Implement externally


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool RCC_Initialise(void)
{
    ENSURE(true); // @todo: Add check for not already initialised

    HAL_Init();

    // @todo: Add commenting
    __PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    // @todo: Use return values == HAL_OK
    HAL_RCC_OscConfig(&RCC_oscInitStruct);
    HAL_RCC_ClockConfig(&RCC_clkInitStruct, RCC_flashLatency);

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000u); // @todo: Make setting
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    HAL_NVIC_SetPriority(SysTick_IRQn, 15u, 0u);

    return true;
}