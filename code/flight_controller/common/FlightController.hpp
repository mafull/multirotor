#ifndef __FLIGHT_CONTROLLER_HPP
#define __FLIGHT_CONTROLLER_HPP

#include "Peripherals.hpp"

class FlightController
{
    public:
        FlightController();
        ~FlightController();

        void run();

        const Peripherals& getPeripherals() const
        {
            return m_peripherals;
        }

    protected:
        
    private:
        static bool m_isInstantiated;

        const Peripherals m_peripherals;
};

#endif  // __FLIGHT_CONTROLLER_HPP
