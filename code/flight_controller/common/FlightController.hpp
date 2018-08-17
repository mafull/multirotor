#ifndef __FLIGHT_CONTROLLER_HPP
#define __FLIGHT_CONTROLLER_HPP

#include "IMU.hpp"
#include "PeripheralManager.hpp"

#include <string>

class FlightController
{
public:
    FlightController();
    ~FlightController();

    void run();

    void log(const std::string& msg);



    PeripheralManager peripherals;
    IMU imu;

protected:
    
private:
    static bool _isInstantiated;

};

#endif  // __FLIGHT_CONTROLLER_HPP
