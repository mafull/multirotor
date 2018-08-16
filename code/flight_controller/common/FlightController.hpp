#ifndef __FLIGHT_CONTROLLER_HPP
#define __FLIGHT_CONTROLLER_HPP

//#include "Peripherals.hpp"

class FlightController
{
public:
    FlightController();
    ~FlightController();

    void run();

    void addPeripheral(); 

//    const Peripherals& getPeripherals() const
//    {
//        return _peripherals;
//    }

protected:
    
private:
    static bool _isInstantiated;

//    const Peripherals _peripherals;
};

#endif  // __FLIGHT_CONTROLLER_HPP
