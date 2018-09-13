#ifndef __CONTROL_THREAD_HPP
#define __CONTROL_THREAD_HPP

#include "thread.hpp"
#include "peripherals/UART.hpp"
#include "Logger.hpp"


using Mode_t = 
    enum : uint32_t
    {
        Mode_None,
        Mode_Initialisation,
        Mode_POST,
        Mode_Idle,
        Mode_Running,
        Mode_Fault,

        Mode_MAX
    };




class ControlThread : public cpp_freertos::Thread, private Loggable
{
public:
    ControlThread(Logger& logger) :
        // Base constructors
        Loggable(logger, "Control"),
        Thread("Control Thread", 1024, 1)
    {

    }

    ~ControlThread();

    void Run();
};

#endif  // __CONTROL_THREAD_HPP
