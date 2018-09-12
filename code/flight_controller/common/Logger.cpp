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

void Logger::log(const std::string& message)
{
    if (message.length() <= 128u) // @todo: Change to constant
    {
        _queue.Enqueue(const_cast<void *>(static_cast<const void *>(message.c_str()))); // @todo: Sort this out
    }
    else // Message is too long
    {
        // @todo: Add in message splitting
        _queue.Enqueue(const_cast<void *>(static_cast<const void *>("TOO LONG"))); // @todo: This too
    }
}



void Logger::Logger_Thread::Run()
{
    while (!_parent._uart) {}

    write("Logger_Thread running\n");

    // Character buffer in which to store the received message
    // @todo: replace char[x] with a structure inc. message source
    char receivedMessage[128] = ""; // @todo: Change size to constant

    for (;;)
    {
        // Attempt to remove an item from the queue
        const bool success = _parent._queue.Dequeue((void *)&receivedMessage);

        if (success) // Successfully removed an item from the queue
        {
            // Print the received message
            // @todo: Add formatting
            write(std::string(receivedMessage) + '\n');
        }
    }
}

void Logger::Logger_Thread::write(const std::string& message)
{
    _parent._uart->write(message);
}
