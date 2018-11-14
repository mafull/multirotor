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
#define LOG(severity, msg, ...)  Logger_Log(__FILENAME__, __LINE__, (severity), (msg), ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...)      Logger_Log(__FILENAME__, __LINE__, Debug,      (msg), ##__VA_ARGS__)
#define LOG_INFO(msg, ...)       Logger_Log(__FILENAME__, __LINE__, Info,       (msg), ##__VA_ARGS__)
#define LOG_WARNING(msg, ...)    Logger_Log(__FILENAME__, __LINE__, Warning,    (msg), ##__VA_ARGS__)
#define LOG_ERROR(msg, ...)      Logger_Log(__FILENAME__, __LINE__, Error,      (msg), ##__VA_ARGS__)


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
void Logger_Run(void *params);





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
                const char *message, ...);


#endif // __LOGGER_H
