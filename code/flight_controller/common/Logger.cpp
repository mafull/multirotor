#include "Logger.hpp"
#include "stm32f4xx_hal.h"
#include <cstring>

Logger::Logger(UART& uart) :
    Thread("Logger Thread", 1024, 1),
    _queue(QUEUE_SIZE, sizeof(Log_Packet_t)),
    _uart(uart)
{
}

Logger::~Logger()
{

}

void Logger::Run()
{
    //while (!_uart) {} // @todo: Check initialised somehow

    // @todo: This is nasty, either make it a function or make this thread extend Loggable (in which case, maybe make a Loggable_Private and make Loggable subclass that; _Private can have the ability to put something on the front of the queue)
    Log_Packet_t tmpPacket = {
        "Logger",
        Log_Severity_Info,
        "Running"
    };
    write(createFormattedStringFromPacket(tmpPacket));

    // Struct in which to store the received packet
    Log_Packet_t receivedPacket = { 0 }; 

    for (;;)
    {
        // Attempt to remove an item from the queue
        const bool success = _queue.Dequeue((void *)&receivedPacket);

        if (success) // Successfully removed an item from the queue
        {
            HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_14);

            // Created a formatted string from the packet
            auto formattedString = createFormattedStringFromPacket(receivedPacket);

            // Send the string over UART
            write(formattedString);
        }
    }
}

void Logger::log(const Log_Packet_t& packet)
{
    _queue.Enqueue(const_cast<void *>(static_cast<const void *>(&packet)));
}

const std::string Logger::createFormattedStringFromPacket(const Log_Packet_t& packet)
{
    // Create a char array of the maximum size possible
    char cStr[PACKET_CSTRING_LENGTH] = "";

    // Safely format the string with the packet data
    snprintf(
        cStr,                  // Target string
        PACKET_CSTRING_LENGTH, // Max output string length
        "%*.*s %.1u %.*s\n",   // Format string
        // Sender
        QUEUE_SENDER_LENGTH,   // Width (min length)
        QUEUE_SENDER_LENGTH,   // Precision (max length)
        packet.sender,         // Data
        // Severity
        packet.severity,       // Data
        // Messgage
        QUEUE_MESSAGE_LENGTH,  // Precision (max length)
        packet.message);       // Data

    // Create a c++ string from the char array
    return std::string(cStr);
}

void Logger::write(const std::string& message)
{
    _uart.write(message);
}


Loggable::Loggable(Logger& logger, const std::string& sender) :
    _logger(logger),
    _sender(sender)
{
    //logDebug("Created"); // @todo: Get this working somehow. Need to make sure logger is initialised before anything else in FlightController ctr
}

Loggable::~Loggable()
{
    logDebug("Deleted");
}

void Loggable::log(const Log_Severity_t severity, const std::string& message)
{
    // @todo: Maybe optimise so the packet is a member variable that simply gets updated instead of created from scratch each time
    Log_Packet_t packet = { 0 };

    // Fill the packet with data
    strncpy(packet.sender, _sender.c_str(), QUEUE_SENDER_LENGTH-1);
    packet.severity = severity;
    // @todo: Handle message splitting
    strncpy(packet.message, message.c_str(), QUEUE_MESSAGE_LENGTH-1);

    // Send the packet to the logger
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
