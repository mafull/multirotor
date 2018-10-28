#ifndef __GPIO_H
#define __GPIO_H


// --- Project includes ---

// --- Library includes ---

// --- Standard includes ---
#include <stdbool.h>


/******************************************************************************
  Public Defines
 ******************************************************************************/



/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 * Enum defining the available GPIO instances
 */
typedef enum Gpio_Instance_e
{
    // Digital Outputs
    Gpio_AssertLed = 0u,
    Gpio_ControlLed,
    Gpio_ImuLed,
    Gpio_LoggerLed,
    Gpio_UnusedLed,

    // External Interrupts
    Gpio_MPU6050_Int,
    Gpio_UserButton,

    // Peripheral pins
    Gpio_I2c1_Scl,
    Gpio_I2c1_Sda,
    Gpio_Uart1_Rx,
    Gpio_Uart1_Tx,
    Gpio_Uart2_Rx,
    Gpio_Uart2_Tx,

    Gpio_Instance_MAX
} Gpio_Instance_t;

/**
 * Enum defining the possible states of a GPIO pin
 */
typedef enum Gpio_State_e
{
    High,
    Low
} Gpio_State_t;


/******************************************************************************
  Public Data
 ******************************************************************************/

/**
 *
 */
Gpio_State_t Gpio_GetState(Gpio_Instance_t instance);

/**
 * Initialise all available GPIO instances
 *
 * @retval true If initialisation is successful
 */
bool Gpio_Initialise(void);

/**
 * Check if the available GPIOs are initialised
 *
 * @retval true If initialised
 */
bool Gpio_IsInitialised(void);

/**
 *
 */
bool Gpio_SetState(Gpio_Instance_t instance, Gpio_State_t newState);



/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */

#endif // __GPIO_H
