#include "ControlThread.hpp"
#include "stm32f4xx_hal.h"
// ControlThread::ControlThread()
// {

// }

ControlThread::~ControlThread()
{

}

static Mode_t mode = Mode_None;

void ControlThread::Run()
{
    logInfo("Running");
    logError("ERROR TEST");

    for (;;)
    {
        logDebug("Tick");
        Delay(10e3);
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
        
        switch (mode)
        {
        case Mode_None:

            break;

        case Mode_Initialisation:

            break;

        case Mode_POST:

            break;

        case Mode_Idle:

            break;

        case Mode_Running:

            break;

        case Mode_Fault:

            break;

        default:

            break;
        }
    }

    logInfo("Finished");
}
