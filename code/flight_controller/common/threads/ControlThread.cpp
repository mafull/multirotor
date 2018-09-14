#include "ControlThread.hpp"

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
