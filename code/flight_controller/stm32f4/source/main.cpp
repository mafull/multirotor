/**
 ******************************************************************************
 * @file    main.cpp
 * @author  Max Fuller
 * @version V1.0
 * @date    04/08/2018
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f4xx.h"

#include "Assert.hpp"

#include "FlightController.hpp"

#include "STM32F4_UART.hpp"

void assert_callback(const char *file, int line);

bool stm32f4_initialiseFlightController(FlightController& flightController);
void stm32f4_initialisePeripherals();

void stm32f4_initialiseDigitalInput();
void stm32f4_initialiseDigitalOutput();
void stm32f4_initialiseI2C();
void stm32f4_initialisePWMInput();
void stm32f4_initialisePWMOutput();
void stm32f4_initialiseUART();

//STM32F4_UART stm32f4_uart;

/**
 * The main entry point of the application
 */
int main()
{
    // Initialise the assert handler
    assert_init(&assert_callback);

    // Create an instance of FlightController
    FlightController flightController;

    // Attempt to initialise the instance
    ASSERT(stm32f4_initialiseFlightController(flightController));

    // Run the flight controller
    flightController.run();

    return 0;
}

/**
 * The callback function that is called when an assert fails
 * @param[in] file The filename where the assert failed
 * @param[in] line The line number where the assert failed
 */
void assert_callback(const char *file, int line)
{
    // Do something here
}


bool stm32f4_initialiseFlightController(FlightController& flightController)
{
    bool ok = true;

    stm32f4_initialisePeripherals();
    const Peripherals& peripherals = flightController.getPeripherals();
    
    //peripherals.addUART(stm32f4_uart);

    return ok;
}

void stm32f4_initialisePeripherals()
{
    stm32f4_initialiseDigitalInput();
    stm32f4_initialiseDigitalOutput();
    stm32f4_initialiseI2C();
    stm32f4_initialisePWMInput();
    stm32f4_initialisePWMOutput();
    stm32f4_initialiseUART();
}

void stm32f4_initialiseDigitalInput()
{

}

void stm32f4_initialiseDigitalOutput()
{

}

void stm32f4_initialiseI2C()
{

}

void stm32f4_initialisePWMInput()
{

}

void stm32f4_initialisePWMOutput()
{

}

void stm32f4_initialiseUART()
{

}
