#include "FlightController.hpp"

#include "Assert.hpp"


bool FlightController::m_isInstantiated = false;

FlightController::FlightController()
{
    // Ensure we only have a single instance of this class
    ASSERT(!m_isInstantiated);
    m_isInstantiated = true;
}

FlightController::~FlightController()
{
    m_isInstantiated = false;
}

void FlightController::run()
{

}