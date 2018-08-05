#include "FlightController.hpp"

#include "Assert.hpp"


bool FlightController::m_isInstantiated = false;

FlightController::FlightController()
{
    ASSERT(!m_isInstantiated);
}

FlightController::~FlightController()
{

}
