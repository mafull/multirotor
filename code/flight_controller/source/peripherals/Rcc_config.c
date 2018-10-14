// --- Private header ---
#define RCC_PRIVATE
    #include "peripherals/Rcc_private.h"
#undef RCC_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

RCC_ClkInitTypeDef Rcc_clkInitStruct =
    {
        .AHBCLKDivider  = RCC_SYSCLK_DIV1,
        .APB1CLKDivider = RCC_HCLK_DIV4,
        .APB2CLKDivider = RCC_HCLK_DIV2,
        .ClockType      = (RCC_CLOCKTYPE_SYSCLK |
                           RCC_CLOCKTYPE_PCLK1 |
                           RCC_CLOCKTYPE_PCLK2),
        .SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK
    };

uint32_t Rcc_flashLatency = FLASH_LATENCY_5;

RCC_OscInitTypeDef Rcc_oscInitStruct =
    {
        .HSEState = RCC_HSE_ON,
        .OscillatorType = RCC_OSCILLATORTYPE_HSE,
        .PLL =
            {
                .PLLM       = 4u,
                .PLLN       = 168u,
                .PLLP       = RCC_PLLP_DIV2,
                .PLLQ       = 4u,
                .PLLSource  = RCC_PLLSOURCE_HSE,
                .PLLState   = RCC_PLL_ON
            }
    };
