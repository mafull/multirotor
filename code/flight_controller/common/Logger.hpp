#ifndef __LOGGER_HPP
#define __LOGGER_HPP

#define QUEUE_MESSAGE_LENGTH 128u
#define QUEUE_SENDER_LENGTH 16u
#define QUEUE_SIZE      20u
//#define QUEUE_ITEM_SIZE (sizeof(char) * QUEUE_MESSAGE_LENGTH)
#define PACKET_CSTRING_LENGTH (sizeof(Log_Packet_t) + 3u)

#include "peripherals/UART.hpp"

#include "queue.hpp"
#include "thread.hpp"

using Log_Severity_t = 
    enum Log_Severity_t : uint8_t
    {
        Log_Severity_Error = 0,
        Log_Severity_Warning,
        Log_Severity_Info,
        Log_Severity_Debug
    };

using Log_Packet_t = 
    struct Log_Packet_t
    {
        char sender[QUEUE_SENDER_LENGTH]; // +1 for the null terminator
        Log_Severity_t severity;
        char message[QUEUE_MESSAGE_LENGTH]; // +1 for the null terminator
    };



class Logger : public cpp_freertos::Thread
{
public:
    Logger();
    ~Logger();

    void Run();

    void log(const Log_Packet_t& packet);

    // @todo: Ideally remove this and set the uart in the constructor - UART will then needs to not assert when used without beign initialised
    void setUART(UART *uart)
    {
        ASSERT(uart);
        _uart = uart;
    }

protected:
    const std::string createFormattedStringFromPacket(const Log_Packet_t& packet);
    void write(const std::string& message);

private:
    UART *_uart;

    cpp_freertos::Queue _queue;
};

class Loggable
{
public:
    Loggable(Logger& logger, const std::string& sender) :
        _logger(logger),
        _sender(sender)
    {

    }

protected:
    void log(const Log_Severity_t severity, const std::string& message);
    void logDebug(const std::string& message);
    void logError(const std::string& message);
    void logInfo(const std::string& message);
    void logWarning(const std::string& message);

private:
    Logger& _logger;
    const std::string _sender;
};

#endif  // __LOGGER_HPP
