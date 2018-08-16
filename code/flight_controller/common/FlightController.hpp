#ifndef __FLIGHT_CONTROLLER_HPP
#define __FLIGHT_CONTROLLER_HPP

#include "PeripheralManager.hpp"

class FlightController
{
public:
    FlightController();
    ~FlightController();

    void run();

    void addPeripheral(); 

    PeripheralManager _peripherals;

protected:
    
private:
    static bool _isInstantiated;

};

#endif  // __FLIGHT_CONTROLLER_HPP
