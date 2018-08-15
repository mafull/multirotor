#ifndef __STM32F4_CONFIG_HPP
#define __STM32F4_CONFIG_HPP

// I2C
#define I2C1_CLOCK_SPEED    400000

// UART
#define UART1_BAUD_RATE     115200
#define UART2_BAUD_RATE     115200
#define UART1_RX_PIN        GPIO_PIN_10
#define UART1_RX_PORT       GPIOA
#define UART1_TX_PIN        GPIO_PIN_9
#define UART1_TX_PORT       GPIOA

#endif  // __STM32F4_CONFIG_HPP
