#include "FlightController.hpp"

#include "Assert.hpp"


bool FlightController::_isInstantiated = false;

FlightController::FlightController() :
    logger(),
    controlThread(logger)
{
    // Ensure we only have a single instance of this class
    ASSERT(!_isInstantiated);
    _isInstantiated = true;
}

FlightController::~FlightController()
{
    _isInstantiated = false;
}

#include "stm32f4xx.h"

void FlightController::run()
{
    peripherals.uart(0).write("Running\n");
    logger.log("FlightController::run()");

    setUpThreads();

    //log("> Threads initialised");

    // ASSERT(false);
    startThreads();

    peripherals.uart(0).write("threads started\n");
    for (;;)
    {
        //peripherals.uart(0).write("log: ");
        logger.log("log");

        // Do nothing
        //HAL_Delay(1000);
    }
}

void FlightController::setUpThreads()
{
    logger.setUART(&peripherals.uart(0));
    controlThread.setUART(&peripherals.uart(0));

    // imu.setConfiguration(&peripherals.i2c(0));
    // imu.initialise();
    // imuThread.setIMU(&imu);
}

void FlightController::startThreads()
{
    controlThread.Start();
    //imuThread.Start();

    logger.start();
    cpp_freertos::Thread::StartScheduler();
}
