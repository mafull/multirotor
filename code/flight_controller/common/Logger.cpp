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






void Loggable::log(Log_Severity_t severity, const std::string& message)
{
    Log_Packet_t packet = 
        {
            .sender = _sender,
            .severity = severity,
            .message = const_cast<char *>(message.c_str())
        };
    _logger.log(packet);
}

void Loggable::logError(const std::string& message)
{
    log(Log_Severity_Error, message);
}

void Loggable::logWarning(const std::string& message)
{
    log(Log_Severity_Warning, message);
}

void Loggable::logInfo(const std::string& message)
{
    log(Log_Severity_Info, message);
}

void Loggable::logDebug(const std::string& message)
{
    log(Log_Severity_Debug, message);
}