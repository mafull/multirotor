#ifndef __FLIGHT_CONTROLLER_HPP
#define __FLIGHT_CONTROLLER_HPP

// Project includes
#include "imu/IMU.hpp"
#include "Logger.hpp"
#include "peripherals/PeripheralManager.hpp"
#include "threads/ControlThread.hpp"

// Library includes
// cpp_freertos
#include "thread.hpp"

// Standard includes
#include <string>


class FlightController : private Loggable
{
    class Init_Thread : private Loggable,
                        public cpp_freertos::Thread
    {
    public:
        Init_Thread(Logger& logger,
                    FlightController& parent);
        
        void Run();

    private:
        FlightController& _parent;
    };

public:
    FlightController(PeripheralManager& peripheralManager,
                     Accelerometer& accelerometer,
                     Gyroscope& gyroscope,
                     Magnetometer& magnetometer);
    ~FlightController();

    void run();

    void log(const std::string& msg);

private:
    void startThreads();

    static bool _isInstantiated;

    PeripheralManager _peripheralManager;

    ControlThread _controlThread;
    IMU _imu;
    Init_Thread _initThread;
    Logger _logger;
};

#endif  // __FLIGHT_CONTROLLER_HPP
