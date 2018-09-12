#include "FlightController.hpp"

#include "Assert.hpp"


bool FlightController::_isInstantiated = false;

FlightController::FlightController() :
    logger(),
    controlThread(logger),
    _thread(*this)
{
    // Ensure we only have a single instance of this class
    ASSERT(!_isInstantiated);
    _isInstantiated = true;
}

FlightController::~FlightController()
{
    _isInstantiated = false;
}

void FlightController::run()
{
    // Start the initialisation thread and scheduler
    _thread.Start();
    cpp_freertos::Thread::StartScheduler();

    ASSERT(true); // Should never get here
    peripherals.uart(0).write("WHY AM I HERE"); // @todo: Remove this once ASSERT is working
}

void FlightController::setUpThreads()
{
    logger.log("Setting up threads...");

    logger.setUART(&peripherals.uart(0)); // @todo: Move this?
    // imu.setConfiguration(&peripherals.i2c(0));
    // imu.initialise();
    // imuThread.setIMU(&imu);

    logger.log("All threads are ready");
}

void FlightController::startThreads()
{
    logger.log("Starting threads...");

    logger.start(); // @todo: Work out why this has to go before other threads

    controlThread.Start();
    //imuThread.Start();
    
    logger.log("All threads have been started");
    logger.log("Starting scheduler...");

    //cpp_freertos::Thread::StartScheduler();
}

void FlightController::Init_Thread::Run()
{
    _parent.logger.log(GetName() + " started");

    _parent.setUpThreads();
    _parent.startThreads();

    _parent.logger.log("END OF RUN");
}