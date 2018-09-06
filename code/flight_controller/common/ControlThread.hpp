#ifndef __CONTROL_THREAD_HPP
#define __CONTROL_THREAD_HPP

#include "thread.hpp"
#include "peripherals/UART.hpp"
class ControlThread : public cpp_freertos::Thread
{
public:
    ControlThread() :
        Thread("Control Thread", 128, 1), ch('a') {}
    ~ControlThread();

    void setUART(UART *uart)
    {
        _uart = uart;
    }

    char ch;

    void Run()
    {
        if (!_uart) return;

        for (;;)
        {
            _uart->write(std::string("." + ch));
            ch++;
            Delay(1000);

        }
    }

    UART *_uart;
protected:

private:

};

#endif  // __CONTROL_THREAD_HPP
