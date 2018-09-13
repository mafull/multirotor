#ifndef __LOGGER_HPP
#define __LOGGER_HPP

#define QUEUE_MESSAGE_LENGTH 128u
#define QUEUE_SENDER_LENGTH 16u
#define QUEUE_SIZE      20u
//#define QUEUE_ITEM_SIZE (sizeof(char) * QUEUE_MESSAGE_LENGTH)

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
        char sender[QUEUE_SENDER_LENGTH];
        Log_Severity_t severity;
        char message[QUEUE_MESSAGE_LENGTH];
    };



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
        const std::string createFormattedStringFromPacket(const Log_Packet_t& packet);
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

class Loggable
{
public:
    Loggable(const Logger& logger, const std::string& sender) :
        _logger(logger),
        _sender(sender)
    {

    }

private:
    void log(Log_Severity_t severity, const std::string& message)
    {
        Log_Packet_t packet = 
            {
                .sender = _sender,
                .severity = severity,
                .message = const_cast<char *>(message.c_str())
            };
        _logger.log(packet);
    }

    void logError(const std::string& message)
    {
        log(Log_Severity_Error, message);
    }

    void logWarning(const std::string& message)
    {
        log(Log_Severity_Warning, message);
    }

    void logInfo(const std::string& message)
    {
        log(Log_Severity_Info, message);
    }

    void logDebug(const std::string& message)
    {
        log(Log_Severity_Debug, message);
    }

    Logger& logger;
    const std::string _sender;
};

#endif  // __LOGGER_HPP
