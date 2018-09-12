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




class ControlThread : public cpp_freertos::Thread
{
public:
    ControlThread(Logger& logger) :
        Thread("Control Thread", 1024, 1),
        _logger(logger)
    {

    }

    ~ControlThread();

    void setUART(UART *uart)
    {
        _uart = uart;
    }

    void Run();

    UART *_uart;
protected:

private:
    Logger& _logger;
};

#endif  // __CONTROL_THREAD_HPP
