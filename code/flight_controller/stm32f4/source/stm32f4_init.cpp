#include "stm32f4_init.hpp"

#include "stm32f4_config.hpp"

// Peripherals
#include "STM32F4_DigitalOutput.hpp"
#include "STM32F4_I2C.hpp"
#include "STM32F4_UART.hpp"

bool stm32f4_initialiseFlightController(FlightController& flightController)
{
    bool ok = true;

    //const Peripherals& peripherals = flightController.getPeripherals();
    //stm32f4_initialisePeripherals(peripherals);

    return ok;
}

void stm32f4_initialisePeripherals(const Peripherals& peripherals)
{
    stm32f4_initialiseDigitalInput(peripherals);
    stm32f4_initialiseDigitalOutput(peripherals);
    stm32f4_initialiseI2C(peripherals);
    stm32f4_initialisePWMInput(peripherals);
    stm32f4_initialisePWMOutput(peripherals);
    stm32f4_initialiseUART(peripherals);
}

void stm32f4_initialiseDigitalInput(const Peripherals& peripherals)
{

}

void stm32f4_initialiseDigitalOutput(const Peripherals& peripherals)
{

}

void stm32f4_initialiseI2C(const Peripherals& peripherals)
{
    // Create an instance of the STM32F4_I2C module
    STM32F4_I2C i2c1;

    // Create a common initialisation structure
    I2C_InitTypeDef init;
    init.DutyCycle = I2C_DUTYCYCLE_2;
    init.OwnAddress1 = 0;
    init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
    init.OwnAddress2 = 0;
    init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    init.NoStretchMode = I2C_NOSTRETCH_DISABLED;

    // Set the clock speed for I2C1 and update the configuration
    init.ClockSpeed = I2C1_CLOCK_SPEED;
    i2c1.setConfiguration(I2C1, init);

    // Initialise the instance
    i2c1.initialise();

    // Add to the FlightController instance
    // DO SOMETHING
}

void stm32f4_initialisePWMInput(const Peripherals& peripherals)
{

}

void stm32f4_initialisePWMOutput(const Peripherals& peripherals)
{

}

void stm32f4_initialiseUART(const Peripherals& peripherals)
{
    // Create instances of the STM32F4_UART module
    STM32F4_UART uart1;
    STM32F4_UART uart2;

    // Create a common initialisation structure
    UART_InitTypeDef init;
    init.WordLength = UART_WORDLENGTH_8B;
    init.StopBits= UART_STOPBITS_1;
    init.Parity = UART_PARITY_NONE;
    init.Mode = UART_MODE_TX_RX;
    init.HwFlowCtl = UART_HWCONTROL_NONE;
    init.OverSampling = UART_OVERSAMPLING_16;

    // Set the baud rate for UART1 and update the configuration
    init.BaudRate = UART1_BAUD_RATE;
    uart1.setConfiguration(USART1, init);

    // Set the baud rate for UART2 and update the configuration
    init.BaudRate = UART2_BAUD_RATE;
    uart2.setConfiguration(USART2, init);

    // Initialise both instances
    uart1.initialise();
    uart2.initialise();

    // Add to the FlightController instance
    // peripherals.addUART(uart1);
    // peripherals.addUART(uart2);
}
