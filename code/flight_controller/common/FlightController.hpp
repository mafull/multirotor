#ifndef __FLIGHT_CONTROLLER_HPP
#define __FLIGHT_CONTROLLER_HPP

#include "imu/IMU.hpp"
#include "Logger.hpp"
#include "peripherals/PeripheralManager.hpp"
#include "threads/ControlThread.hpp"

// cpp_freertos
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
    FlightController(PeripheralManager& peripheralManager);
    ~FlightController();

    void run();

    void log(const std::string& msg);


    //IMU imu;
    
private:
    void setUpThreads();
    void startThreads();

    static bool _isInstantiated;

    
    ControlThread _controlThread;
    Init_Thread _initThread;
    Logger _logger;
    
    PeripheralManager _peripheralManager;
};

#endif  // __FLIGHT_CONTROLLER_HPP
