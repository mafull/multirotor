#ifndef __FLIGHT_CONTROLLER_HPP
#define __FLIGHT_CONTROLLER_HPP

#include "Logger.hpp"
#include "imu/IMU.hpp"
#include "threads/ControlThread.hpp"
#include "peripherals/PeripheralManager.hpp"

#include "thread.hpp"

#include <string>

class FlightController : private Loggable
{
    class Init_Thread : private Loggable, public cpp_freertos::Thread
    {
    public:
        Init_Thread(Logger& logger, FlightController& parent) :
            // Base constructors
            Loggable(logger, "Init Thread"),
            Thread("Init Thread", 1024, 1),
            // Private members
            _parent(parent)
        {
            // Do nothing
        }
        //~Init_Thread();

        void Run();

    private:
        FlightController& _parent;
    };

public:
    FlightController();
    ~FlightController();

    void run();

    void log(const std::string& msg);


    PeripheralManager peripherals;
    IMU imu;
    
private:
    void setUpThreads();
    void startThreads();

    static bool _isInstantiated;

    
    ControlThread _controlThread;
    Init_Thread _thread;
    
    Logger _logger;
};

#endif  // __FLIGHT_CONTROLLER_HPP
