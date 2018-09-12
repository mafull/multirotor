#ifndef __LOGGER_HPP
#define __LOGGER_HPP

#define QUEUE_SIZE      20u
#define QUEUE_ITEM_SIZE (sizeof(char) * 128u)
//#define QUEUE_ITEM_SIZE sizeof(uint32_t)

#include "peripherals/UART.hpp"

#include "queue.hpp"
#include "thread.hpp"



class Logger
{
    class Logger_Thread : public cpp_freertos::Thread
    {
    public:
        Logger_Thread(Logger& parent) :
            Thread("Logger Thread", 1024, 1),
            _parent(parent)
        {
        }
        //~Logger_Thread();

        void Run();

    private:
        void write(const std::string& message);
        
        Logger& _parent;
    };

public:
    Logger();
    ~Logger();

    void start();

    void log(const std::string& message);

    void setUART(UART *uart)
    {
        ASSERT(uart);
        _uart = uart;
    }

protected:

private:
    UART *_uart;
    Logger_Thread _thread;

    cpp_freertos::Queue _queue;
};

#endif  // __LOGGER_HPP
