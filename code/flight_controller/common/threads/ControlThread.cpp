#include "ControlThread.hpp"

// ControlThread::ControlThread()
// {

// }

ControlThread::~ControlThread()
{

}

static int i = 0;
static Mode_t mode = Mode_None;

void ControlThread::Run()
{
    for (;;)
    {
        //_uart->write(std::to_string(i++) + '.');
        Delay(1000);
        //_logger.log(std::to_string(i++) + '#');


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
}