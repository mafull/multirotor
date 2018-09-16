#include "FlightController.hpp"

#include "Assert.hpp"


bool FlightController::_isInstantiated = false;

FlightController::FlightController(PeripheralManager& peripheralManager,
                                   Accelerometer& accelerometer,
                                   Gyroscope& gyroscope,
                                   Magnetometer& magnetometer) :
    // Base constructors
    Loggable(_logger, "FlightController"),
    // Private members
    _peripheralManager(peripheralManager), // This MUST be first
    _controlThread(_logger),
    _imu(_logger,
         accelerometer,
         gyroscope,
         magnetometer),
    _initThread(_logger,
                *this),
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

    // ASSERT(true); // Should never get here
    _peripheralManager.uart(0).write("WHY AM I HERE"); // @todo: Remove this once ASSERT is working
}

void FlightController::startThreads()
{
    logInfo("Starting threads...");

    _controlThread.Start();
    _imu.Start();
    _logger.Start();

    logInfo("All threads have been started");
}


FlightController::Init_Thread::Init_Thread(Logger& logger,
                                           FlightController& parent) :
    // Base constructors
    Loggable(logger, "Init Thread"),
    Thread("Init Thread", 1024, 1),
    // Private members
    _parent(parent)
{

}

void FlightController::Init_Thread::Run()
{
    logInfo("Running");

    _parent.startThreads();

    logInfo("Finished");
}
