#include "Logger.hpp"

Logger::Logger() :
    _thread(*this),
    _queue(QUEUE_SIZE, sizeof(Log_Packet_t))
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
    // if (message.length() <= 128u) // @todo: Change to constant
    // {
    //     _queue.Enqueue(const_cast<void *>(static_cast<const void *>(message.c_str()))); // @todo: Sort this out
    // }
    // else // Message is too long
    // {
    //     // @todo: Add in message splitting
    //     _queue.Enqueue(const_cast<void *>(static_cast<const void *>("TOO LONG"))); // @todo: This too
    // }

    // Create a
    Log_Packet_t packet =
        {
            .sender = "UNKNOWN",
            .severity = Log_Severity_Debug,
            .message = const_cast<char *>(message.c_str()) // @todo: Is this the best way to do this?
        };
    log(packet);
}

void Logger::log(const Log_Packet_t& packet)
{
    _queue.Enqueue(&packet);
}



void Logger::Logger_Thread::Run()
{
    while (!_parent._uart) {}

    write("Logger_Thread running\n");

    // Struct in which to store the received packet
    Log_Packet_t receivedPacket = { 0 }; 

    for (;;)
    {
        // Attempt to remove an item from the queue
        const bool success = _parent._queue.Dequeue((void *)&receivedPacket);

        if (success) // Successfully removed an item from the queue
        {
            // Created a formatted string from the packet
            auto formattedString = createFormattedStringFromPacket(receivedPacket);

            // Send the string over UART
            write(formattedString);
        }
    }
}

const std::string Logger::Logger_Thread::createFormattedStringFromPacket(const Log_Packet_t& packet)
{
    return std::string(
        packet.sender + ' ' + // @todo: Add width
        std::to_string(packet.severity) + ' ' + // @todo: Add width
        packet.message + '\n');
}

void Logger::Logger_Thread::write(const std::string& message)
{
    _parent._uart->write(message);
}
