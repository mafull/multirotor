#include "stm32f4_init.hpp"


bool stm32f4_initialiseFlightController(FlightController& flightController)
{
    bool ok = true;

    const Peripherals& peripherals = flightController.getPeripherals();
    stm32f4_initialisePeripherals(peripherals);

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
    STM32F4_UART uart1 = STM32F4_UART(USART1);
    STM32F4_UART uart2 = STM32F4_UART(USART2);

    // Create a common initialisation structure
    UART_InitTypeDef init;
    init.WordLength = UART_WORDLENGTH_8B;
    init.StopBits= UAR_STOPBITS_1;
    init.Parity = UART_PARITY_NONE;
    init.Mode = UART_MODE_TX_RX;
    init.HwFlowControl = UART_HWCONTROL_NONE;
    init.Oversampling = UART_OVERSAMPLING_16;

    // Set the baud rate for UART1 and initialise it
    init.BaudRate = UART1_BAUD_RATE;
    uart1.init(init);

    // Set the baud rate for UART2 and initialise it
    init.BaudRate = UART_BAUD_RATE;
    uart2.init(init);

    // Add the two modules to the Peripherals module
    peripherals.addUART(uart1);
    peripherals.addUART(uart2);
}