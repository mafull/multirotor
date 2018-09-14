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

#include "stm32f4_init.hpp"

#include "Assert.hpp"
#include "FlightController.hpp"

void assert_callback(const char *file, int line);

/**
 * The main entry point of the application
 */

int main()
{
    // Initialise the assert handler
    assert_init(&assert_callback);

    // PERIPHERALS
    PeripheralManager peripheralManager;
    stm32f4_initialisePeripheralManager(peripheralManager);
    
    // Create an instance of FlightController
    FlightController flightController(peripheralManager);

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
    // flightController.peripherals.uart(0).write("#");
    // flightController.peripherals.uart(0).write("ASSERT: " + std::string(file) + std::to_string(line));
}
