// --- Public header ---
#include "peripherals/Gpio.h"

// --- Private header ---
#define GPIO_PRIVATE
    #include "peripherals/Gpio_private.h"
#undef GPIO_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

const Gpio_ConfigData_t Gpio_configData[Gpio_Instance_MAX] = 
    {
        /*
          | Port | Init Struct
          |      | | Pin        | Mode               | Pull        | Speed         | Alt. Function
        */
        // Digital Outputs
        { GPIOD, {  GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,  GPIO_SPEED_LOW,               0 } }, // Gpio_AssertLed
        { GPIOD, { GPIO_PIN_12, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,  GPIO_SPEED_LOW,               0 } }, // Gpio_ControlLed
        { GPIOD, { GPIO_PIN_13, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,  GPIO_SPEED_LOW,               0 } }, // Gpio_ImuLed
        { GPIOD, { GPIO_PIN_14, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,  GPIO_SPEED_LOW,               0 } }, // Gpio_LoggerLed
        { GPIOD, { GPIO_PIN_15, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL,  GPIO_SPEED_LOW,               0 } }, // Gpio_UnusedLed
        // External Interrupts
        { GPIOD, {  GPIO_PIN_4, GPIO_MODE_IT_RISING, GPIO_NOPULL,  GPIO_SPEED_LOW,               0 } }, // Gpio_MPU6050_Int
        { GPIOD, {  GPIO_PIN_0, GPIO_MODE_IT_RISING, GPIO_NOPULL,  GPIO_SPEED_LOW,               0 } }, // Gpio_UserButton
        // Peripheral pins
        { GPIOB, {  GPIO_PIN_6,     GPIO_MODE_AF_OD, GPIO_PULLUP, GPIO_SPEED_HIGH,   GPIO_AF4_I2C1 } }, // Gpio_I2c1_Scl
        { GPIOB, {  GPIO_PIN_7,     GPIO_MODE_AF_OD, GPIO_PULLUP, GPIO_SPEED_HIGH,   GPIO_AF4_I2C1 } }, // Gpio_I2c1_Scl
        { GPIOA, { GPIO_PIN_10,     GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_HIGH, GPIO_AF7_USART1 } }, // Gpio_Uart1_Rx
        { GPIOA, {  GPIO_PIN_9,     GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_HIGH, GPIO_AF7_USART1 } }, // Gpio_Uart1_Tx
        { GPIOD, {  GPIO_PIN_6,     GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_HIGH, GPIO_AF7_USART2 } }, // Gpio_Uart2_Rx
        { GPIOD, {  GPIO_PIN_5,     GPIO_MODE_AF_PP, GPIO_NOPULL, GPIO_SPEED_HIGH, GPIO_AF7_USART2 } }, // Gpio_Uart2_Tx
    };
