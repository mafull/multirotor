#include "Logger.hpp"

Logger::Logger() :
    _thread(*this),
    _queue(QUEUE_SIZE, QUEUE_ITEM_SIZE)
{
}

Logger::~Logger()
{

}

void Logger::start()
{
    _thread.Start();
}

static uint32_t counter = 0;
void Logger::log(const std::string& message)
{
    _queue.Enqueue(&counter);
    counter++;
}





static uint32_t value = 0;
void Logger::Logger_Thread::Run()
{
    while (!_parent._uart) {}

    write("Logger_Thread running\n");

    for (uint32_t i = 0; i < 5; i++)
    {
        _parent._queue.Enqueue(&i);
    }

    for (;;)
    {
        const bool success = _parent._queue.Dequeue((void *)&value);

        if (success)
        {
            write("Logger: " + std::to_string(value) + "(" + std::to_string(_parent._queue.NumSpacesLeft()) + ")\n");
        }
    }
}

void Logger::Logger_Thread::write(const std::string& message)
{
    _parent._uart->write(message);
}
