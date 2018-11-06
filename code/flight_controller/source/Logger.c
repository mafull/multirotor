// --- Public header ---
#include "Logger.h"

// --- Private header ---
#define LOGGER_PRIVATE
    #include "Logger_private.h"
#undef LOGGER_PRIVATE


// --- Project includes ---
#include "macros.h"

// --- Library includes ---

// --- Standard includes ---
#include <stdio.h>


/******************************************************************************
  Private Data
 ******************************************************************************/

bool Logger_isInitialised = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool Logger_Initialise(void)
{
    ENSURE(!Logger_isInitialised);

    ENSURE(Uart_IsInitialised()); // @todo: Ret val?

    Logger_isInitialised = true;
    return Logger_isInitialised;
}


bool Logger_IsInitialised(void)
{
    return Logger_isInitialised;
}


void Logger_Log(char *fileName, uint16_t lineNumber,
                Logger_Severity_t severity,
                char *message)
{
    // @todo: Make this thread safe (i.e. use a message queue)
    ENSURE(fileName);
    ENSURE(message);
    ENSURE(Logger_isInitialised);

    ENSURE(Uart_IsInitialised());

    // @todo: Maybe strip LF/CR characters from message?

    char buffer[LOGGER_BUFFER_LENGTH] = ""; // @todo maybe make static & use memset 0?
    snprintf(buffer,                    // Target string
             LOGGER_BUFFER_LENGTH,      // Max output string length
             "%*.*s:%*u|%*.*u|%.*s",  // Format string
             // File name
             LOGGER_FILENAME_LENGTH,    // Width (min length)
             LOGGER_FILENAME_LENGTH,    // Precision (max length)
             fileName,                  // Data
             // Line number
             LOGGER_LINENUMBER_LENGTH,  // Width
             // LOGGER_LINENUMBER_LENGTH,  // Precision
             lineNumber,                // Data
             // Severity
             LOGGER_SEVERITY_LENGTH,    // Width
             LOGGER_SEVERITY_LENGTH,    // Precision
             (uint8_t)severity,         // Data
             // Message
             LOGGER_MESSAGE_LENGTH,     // Precision
             message);                  // Data

    const bool success = Uart_Write(Uart1, buffer); // @todo: Move Uart1 to config
    UNUSED(success);
    // @todo: Add stats (e.g. num logs sent, num failed)?
}
