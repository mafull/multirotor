#include "FlightController.hpp"

#include "Assert.hpp"


bool FlightController::_isInstantiated = false;

FlightController::FlightController(PeripheralManager& peripheralManager) :
    // Base constructors
    Loggable(_logger, "FlightController"),
    // Public members
    //imu(_logger),
    // Private members
    _peripheralManager(peripheralManager), // This MUST be first
    _controlThread(_logger),
    _initThread(_logger, *this),
    _logger(peripheralManager.uart(0))
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
    _initThread.Start();
    cpp_freertos::Thread::StartScheduler();

    ASSERT(true); // Should never get here
    _peripheralManager.uart(0).write("WHY AM I HERE"); // @todo: Remove this once ASSERT is working
}

void FlightController::setUpThreads()
{
    logInfo("Setting up threads...");

    // imu.setConfiguration(&_peripheralManager.i2c(0));
    // imu.initialise();

    logInfo("All threads are ready");
}

void FlightController::startThreads()
{
    logInfo("Starting threads...");

    _logger.Start(); // @todo: Work out why this has to go before other threads

    _controlThread.Start();
    //imu.Start();

    logInfo("All threads have been started");
}

void FlightController::Init_Thread::Run()
{
    logInfo("Running");

    _parent.setUpThreads();
    _parent.startThreads();

    logInfo("Finished");
}
