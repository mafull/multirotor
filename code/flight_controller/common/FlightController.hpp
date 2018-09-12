#ifndef __FLIGHT_CONTROLLER_HPP
#define __FLIGHT_CONTROLLER_HPP

#include "Logger.hpp"
#include "imu/IMU.hpp"
#include "threads/ControlThread.hpp"
#include "threads/IMUThread.hpp"
#include "peripherals/PeripheralManager.hpp"

#include <string>

class FlightController
{
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

};

#endif  // __FLIGHT_CONTROLLER_HPP
