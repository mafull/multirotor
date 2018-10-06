#ifndef __STM32F4_CONFIG_HPP
#define __STM32F4_CONFIG_HPP

// I2C
#define I2C1_ADDRESS_BMP280     0x76
#define I2C1_ADDRESS_EEPROM     0x50
#define I2C1_ADDRESS_HMC5883L   0x1E
#define I2C1_ADDRESS_MPU6050    0x68
#define I2C1_CLOCK_SPEED        400000
#define I2C1_SCL_PIN            GPIO_PIN_6
#define I2C1_SCL_PORT           GPIOB
#define I2C1_SDA_PIN            GPIO_PIN_7
#define I2C1_SDA_PORT           GPIOB

// UART
#define UART1_BAUD_RATE         115200
#define UART2_BAUD_RATE         115200
#define UART1_RX_PIN            GPIO_PIN_10
#define UART1_RX_PORT           GPIOA
#define UART1_TX_PIN            GPIO_PIN_9
#define UART1_TX_PORT           GPIOA

#endif  // __STM32F4_CONFIG_HPP
