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
#define LOG(severity, msg)  Logger_Log(__FILENAME__, __LINE__, (severity), (msg))
#define LOG_DEBUG(msg)      Logger_Log(__FILENAME__, __LINE__, Debug,      (msg))
#define LOG_INFO(msg)       Logger_Log(__FILENAME__, __LINE__, Info,       (msg))
#define LOG_WARNING(msg)    Logger_Log(__FILENAME__, __LINE__, Warning,    (msg))
#define LOG_ERROR(msg)      Logger_Log(__FILENAME__, __LINE__, Error,      (msg))


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
 *
 */
bool Logger_Initialise(void);

/**
 *
 */
bool Logger_IsInitialised(void);

/**
 *
 */
void Logger_Log(const char *fileName, uint16_t lineNumber,
                Logger_Severity_t severity,
                const char *message);


#endif // __LOGGER_H
