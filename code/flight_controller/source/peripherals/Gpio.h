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
    Gpio_IMULed,
    Gpio_LoggerLed,
    Gpio_UnusedLed,

    // External Interrupts
    Gpio_MPU6050_Int,
    Gpio_MPU6050_UserButton,

    // Peripheral pins
    Gpio_I2c1_Scl,
    Gpio_I2c1_Sda,
    // Gpio_Uart1_Rx,
    // Gpio_Uart1_Tx,
    // Gpio_Uart2_Rx,
    // Gpio_Uart2_Tx,

    Gpio_Instance_MAX
} Gpio_Instance_t;


/******************************************************************************
  Public Data
 ******************************************************************************/

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


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */

#endif // __GPIO_H
