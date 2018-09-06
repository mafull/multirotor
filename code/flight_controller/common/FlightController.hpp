#ifndef __FLIGHT_CONTROLLER_HPP
#define __FLIGHT_CONTROLLER_HPP

#include "ControlThread.hpp"
#include "imu/IMU.hpp"
#include "peripherals/PeripheralManager.hpp"

#include <string>


#include "ControlThread.hpp"

class FlightController
{
public:
    FlightController();
    ~FlightController();

    void run();

    void log(const std::string& msg);

    ControlThread controlThread;

    PeripheralManager peripherals;
    IMU imu;

protected:
    void controlThreadTop();
    
private:
    static bool _isInstantiated;

};

#endif  // __FLIGHT_CONTROLLER_HPP
