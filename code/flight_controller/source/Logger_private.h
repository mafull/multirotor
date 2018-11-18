// Incorrect usage guard
#ifndef LOGGER_PRIVATE
    #error Private interface should not be included here!
#endif // LOGGER_PRIVATE

#ifndef __LOGGER_PRIVATE_H
#define __LOGGER_PRIVATE_H


// --- Public header ---
#include "Logger.h"

// --- Project includes ---
#include "peripherals/Uart.h"

// --- Library includes ---
// FreeRTOS
#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/queue.h"
#include "FreeRTOS/task.h"


/******************************************************************************
  Private Defines
 ******************************************************************************/

/**
 *
 */
#define LOGGER_BUFFER_LENGTH        256u
#define LOGGER_FILENAME_LENGTH      20u
#define LOGGER_LINENUMBER_LENGTH    4u
#define LOGGER_SEVERITY_LENGTH      1u
#define LOGGER_MESSAGE_LENGTH       (  LOGGER_BUFFER_LENGTH \
                                     - LOGGER_FILENAME_LENGTH \
                                     - LOGGER_LINENUMBER_LENGTH \
                                     - LOGGER_SEVERITY_LENGTH \
                                     - 5u)


/******************************************************************************
  Private Data
 ******************************************************************************/

/**
 *
 */
extern TaskHandle_t Logger_hTask;

/**
 *
 */
extern bool Logger_isStarted;


/******************************************************************************
  Private Function Prototypes
 ******************************************************************************/

/**
 *
 */
void Logger_Initialise(void);

/**
 *
 */
void Logger_StripLFCR(const char *string);

/**
 *
 */
void Logger_ThreadTop(void *params);

/**
 *
 */
void Logger_UartTxCpltCb(void);


#endif // __LOGGER_PRIVATE_H
