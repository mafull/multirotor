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
        [Gpio_AssertLed]   = { GPIOD, {  GPIO_PIN_1, GPIO_MODE_OUTPUT_PP,   GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,               0 } },
        [Gpio_ControlLed]  = { GPIOD, { GPIO_PIN_12, GPIO_MODE_OUTPUT_PP,   GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,               0 } },
        [Gpio_ImuLed]      = { GPIOD, { GPIO_PIN_13, GPIO_MODE_OUTPUT_PP,   GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,               0 } },
        [Gpio_LoggerLed]   = { GPIOD, { GPIO_PIN_14, GPIO_MODE_OUTPUT_PP,   GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,               0 } },
        [Gpio_UnusedLed]   = { GPIOD, { GPIO_PIN_15, GPIO_MODE_OUTPUT_PP,   GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,               0 } },
        // External Interrupts
        [Gpio_MPU6050_Int] = { GPIOD, {  GPIO_PIN_4, GPIO_MODE_IT_RISING,   GPIO_PULLUP,  GPIO_SPEED_FREQ_LOW,               0 } },
        [Gpio_UserButton]  = { GPIOD, {  GPIO_PIN_0, GPIO_MODE_IT_RISING,   GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,               0 } },
        // I2C
        [Gpio_I2c1_Scl]    = { GPIOB, {  GPIO_PIN_6,     GPIO_MODE_AF_OD,   GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH,   GPIO_AF4_I2C1 } },
        [Gpio_I2c1_Sda]    = { GPIOB, {  GPIO_PIN_7,     GPIO_MODE_AF_OD,   GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH,   GPIO_AF4_I2C1 } },
        // UART
        [Gpio_Uart1_Rx]    = { GPIOA, { GPIO_PIN_10,     GPIO_MODE_AF_PP,   GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF7_USART1 } },
        [Gpio_Uart1_Tx]    = { GPIOA, {  GPIO_PIN_9,     GPIO_MODE_AF_PP,   GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF7_USART1 } },
        [Gpio_Uart2_Rx]    = { GPIOD, {  GPIO_PIN_6,     GPIO_MODE_AF_PP,   GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF7_USART2 } },
        [Gpio_Uart2_Tx]    = { GPIOD, {  GPIO_PIN_5,     GPIO_MODE_AF_PP,   GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH, GPIO_AF7_USART2 } },
        // Timer 1
        [Gpio_Tim1_Ch1]    = { GPIOE, {  GPIO_PIN_9,     GPIO_MODE_AF_PP,   GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,   GPIO_AF1_TIM1 } },
        [Gpio_Tim1_Ch2]    = { GPIOE, { GPIO_PIN_11,     GPIO_MODE_AF_PP,   GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,   GPIO_AF1_TIM1 } },
        [Gpio_Tim1_Ch3]    = { GPIOE, { GPIO_PIN_13,     GPIO_MODE_AF_PP,   GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,   GPIO_AF1_TIM1 } },
        [Gpio_Tim1_Ch4]    = { GPIOE, { GPIO_PIN_14,     GPIO_MODE_AF_PP,   GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,   GPIO_AF1_TIM1 } },
        // Timer 2
        [Gpio_Tim2_Ch1]    = { GPIOA, {  GPIO_PIN_0,     GPIO_MODE_AF_PP, GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW,   GPIO_AF1_TIM2 } },
        [Gpio_Tim2_Ch2]    = { GPIOA, {  GPIO_PIN_1,     GPIO_MODE_AF_PP, GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW,   GPIO_AF1_TIM2 } },
        [Gpio_Tim2_Ch3]    = { GPIOA, {  GPIO_PIN_2,     GPIO_MODE_AF_PP, GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW,   GPIO_AF1_TIM2 } },
        [Gpio_Tim2_Ch4]    = { GPIOA, {  GPIO_PIN_3,     GPIO_MODE_AF_PP, GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW,   GPIO_AF1_TIM2 } },
        // Timer 3
        [Gpio_Tim3_Ch1]    = { GPIOC, {  GPIO_PIN_6,     GPIO_MODE_AF_PP, GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW,   GPIO_AF2_TIM3 } },
        [Gpio_Tim3_Ch2]    = { GPIOC, {  GPIO_PIN_7,     GPIO_MODE_AF_PP, GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW,   GPIO_AF2_TIM3 } },
        [Gpio_Tim3_Ch3]    = { GPIOC, {  GPIO_PIN_8,     GPIO_MODE_AF_PP, GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW,   GPIO_AF2_TIM3 } },
        [Gpio_Tim3_Ch4]    = { GPIOC, {  GPIO_PIN_9,     GPIO_MODE_AF_PP, GPIO_PULLDOWN,  GPIO_SPEED_FREQ_LOW,   GPIO_AF2_TIM3 } },
        // Timer 4
        // [Gpio_Tim4_Ch1]    = { GPIOD, { GPIO_PIN_12,     GPIO_MODE_AF_PP, GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,   GPIO_AF2_TIM1 } },
        // [Gpio_Tim4_Ch2]    = { GPIOD, { GPIO_PIN_13,     GPIO_MODE_AF_PP, GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,   GPIO_AF2_TIM1 } },
        // [Gpio_Tim4_Ch3]    = { GPIOD, { GPIO_PIN_14,     GPIO_MODE_AF_PP, GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,   GPIO_AF2_TIM1 } },
        // [Gpio_Tim4_Ch4]    = { GPIOD, { GPIO_PIN_15,     GPIO_MODE_AF_PP, GPIO_NOPULL,  GPIO_SPEED_FREQ_LOW,   GPIO_AF2_TIM1 } },
    };
