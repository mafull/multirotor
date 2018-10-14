// 
#ifndef RCC_PRIVATE
    #error Private interface should not be included here!
#endif // RCC_PRIVATE

#ifndef __RCC_PRIVATE_H
#define __RCC_PRIVATE_H


// --- Public header ---
#include "peripherals/RCC.h"

// --- Library includes ---
// HAL_Driver
#include "stm32f4xx_hal.h"


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern RCC_ClkInitTypeDef RCC_clkInitStruct;

/**
 *
 */
extern uint32_t RCC_flashLatency;

/**
 *
 */
extern RCC_OscInitTypeDef RCC_oscInitStruct;


#endif // __RCC_PRIVATE_H
