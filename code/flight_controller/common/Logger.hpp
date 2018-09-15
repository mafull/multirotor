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
        Log_Severity_Debug,

        Log_Severity_MAX
    };

using Log_Packet_t = 
    struct Log_Packet_t
    {
        char sender[QUEUE_SENDER_LENGTH];
        Log_Severity_t severity;
        char message[QUEUE_MESSAGE_LENGTH];
    };


class Logger : public cpp_freertos::Thread
{
public:
    Logger(UART& uart);
    ~Logger();

    void Run();

    void log(const Log_Packet_t& packet);

protected:
    const std::string createFormattedStringFromPacket(const Log_Packet_t& packet);
    void write(const std::string& message);

private:
    cpp_freertos::Queue _queue;
    UART& _uart;
};


class Loggable
{
public:
    Loggable(Logger& logger, const std::string& sender);
    ~Loggable();

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
