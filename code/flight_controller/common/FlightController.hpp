#ifndef __FLIGHT_CONTROLLER_HPP
#define __FLIGHT_CONTROLLER_HPP

#include "Logger.hpp"
#include "imu/IMU.hpp"
#include "threads/ControlThread.hpp"
#include "threads/IMUThread.hpp"
#include "peripherals/PeripheralManager.hpp"

#include "thread.hpp"

#include <string>

class FlightController
{
    class Init_Thread : public cpp_freertos::Thread
    {
    public:
        Init_Thread(FlightController& parent) :
            Thread("Init Thread", 1024, 1),
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

    ControlThread controlThread;
    //IMUThread imuThread;

    PeripheralManager peripherals;
    IMU imu;
    Logger logger;
    
private:
    void setUpThreads();
    void startThreads();

    static bool _isInstantiated;

    Init_Thread _thread;

};

#endif  // __FLIGHT_CONTROLLER_HPP
