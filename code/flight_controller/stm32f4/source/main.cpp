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

/**
 * The callback function that is called when an assert fails
 * @param[in] file The filename where the assert failed
 * @param[in] line The line number where the assert failed
 */
void assert_callback(const char *file, int line)
{
    // Do something here
}


int main()
{
    // Initialise the assert handler
    assert_init(&assert_callback);

    // Create an instance of FlightController
    FlightController flightController;
    
    for (;;)
    {
        
    }
}
