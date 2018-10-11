#if 0
// Public header
#include "FlightController.h"

// Private header
#define FLGHT_CONTROLLER_PRIVATE
    #include "FlightController_private.h"
#undef FLGHT_CONTROLLER_PRIVATE


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

void FlightController_Run(void)
{
    Thread_CreateThread("FlightController",
                        1024,
                        1,
                        &FlightController_ThreadTop);
    Thread_StartScheduler();
}


void FlightController_ThreadTop(void)
{
    // LOG STARTED
    
    FlightController_InitialisePeripherals();

    FlightController_CreateThreads();

    // LOG FINISHED
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

void FlightController_CreateThreads(void)
{
    // CREATE OTHER THREADS
    // @todo maybe make this a single function with structure containing all thread init info
    // Thread_CreateThread("ControlLoop",
    //                     1024,
    //                     1,
    //                     &ControlLoop_ThreadTop);

    // Thread_CreateThread("IMU",
    //                     1024,
    //                     1,
    //                     &IMU_ThreadTop);

    Thread_CreateThread("Logger",
                        1024,
                        1,
                        &Logger_ThreadTop);
}


void FlightController_InitialisePeripherals(void)
{
    // UART 1,2
    // I2C 1
    // Digital Inputs
    // Digital Outputs
    // EXTI
}
#endif