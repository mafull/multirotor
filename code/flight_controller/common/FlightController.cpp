#include "FlightController.hpp"

#include "Assert.hpp"


bool FlightController::_isInstantiated = false;

FlightController::FlightController() :
    // Base constructors
    Loggable(_logger, "FlightController"),
    // Private members
    _controlThread(_logger),
    _logger(),
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
    logInfo("Setting up threads...");

    logger.setUART(&peripherals.uart(0)); // @todo: Move this?
    // imu.setConfiguration(&peripherals.i2c(0));
    // imu.initialise();
    // imuThread.setIMU(&imu);

    logInfo("All threads are ready");
}

void FlightController::startThreads()
{
    logInfo("Starting threads...");

    logger.start(); // @todo: Work out why this has to go before other threads

    _controlThread.Start();
    //imuThread.Start();
    
    logInfo("All threads have been started");
    logInfo("Starting scheduler...");

    //cpp_freertos::Thread::StartScheduler();
}

void FlightController::Init_Thread::Run()
{
    logInfo("Running");

    _parent.setUpThreads();
    _parent.startThreads();

    logInfo("Finished");
}