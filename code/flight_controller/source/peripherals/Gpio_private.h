// Incorrect usage guard
#ifndef GPIO_PRIVATE
    #error Private interface should not be included here!
#endif // GPIO_PRIVATE

#ifndef __GPIO_PRIVATE_H
#define __GPIO_PRIVATE_H


// --- Public header ---
#include "peripherals/Gpio.h"

// --- Library includes ---
#include "stm32f4xx_hal.h"


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 *
 */
typedef struct Gpio_ConfigData_s
{
    GPIO_TypeDef *port;
    GPIO_InitTypeDef initStruct;
} Gpio_ConfigData_t;


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern const Gpio_ConfigData_t Gpio_configData[Gpio_Instance_MAX];

/**
 *
 */
extern bool Gpio_isInitialised;


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 * Enable a GPIO port clock
 *
 * @param port The GPIO port whose clock is to be enabled
 */
void Gpio_EnablePortClock(GPIO_TypeDef *port);


#endif // __GPIO_PRIVATE_H
