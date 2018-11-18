#ifndef __LOGGER_H
#define __LOGGER_H


// Standard includes
#include <stdbool.h>
#include <stdint.h>


/******************************************************************************
  Public Defines
 ******************************************************************************/

/**
 *
 */
#define LOG(severity, fmt, ...)  Logger_Log(__FILENAME__, __LINE__, (severity), (fmt), ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)      Logger_Log(__FILENAME__, __LINE__, Debug,      (fmt), ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)       Logger_Log(__FILENAME__, __LINE__, Info,       (fmt), ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)    Logger_Log(__FILENAME__, __LINE__, Warning,    (fmt), ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)      Logger_Log(__FILENAME__, __LINE__, Error,      (fmt), ##__VA_ARGS__)


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 *
 */
typedef enum Logger_Severity_e
{
    Debug,
    Info,
    Warning,
    Error
} Logger_Severity_t;


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 * Start the Logger
 */
void Logger_Run(void);

/**
 * Log a message with variadic parameters
 *
 * @note  Typically called via a macro to provide the file name and line number
 *        arguments.
 *
 * @param fileName      File name from where the log request was made
 * @param lineNumber    Line number from where the log request was made
 * @param severity      Severity of the log message - @see #Logger_Severity_t
 * @param format        Format of the generated message
 * @param ...           Variadic arguments used to create the log message
 */
void Logger_Log(const char *fileName, uint16_t lineNumber,
                Logger_Severity_t severity,
                const char *format, ...);


#endif // __LOGGER_H
