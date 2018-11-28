// --- Public header ---
#include "Logger.h"

// --- Private header ---
#define LOGGER_PRIVATE
    #include "Logger_private.h"
#undef LOGGER_PRIVATE


// --- Project includes ---
#include "macros.h"
#include "threadPriorities.h"

// --- Library includes ---

// --- Standard includes ---
#include <stdarg.h>
#include <stdio.h>
#include <string.h>


/******************************************************************************
  Private Data
 ******************************************************************************/

// FreeRTOS handles
QueueHandle_t Logger_hQueue = NULL;
TaskHandle_t  Logger_hTask  = NULL;

bool Logger_isStarted = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

void Logger_Run(void)
{
    ENSURE(!Logger_isStarted);

    // Create the log message queue
    Logger_hQueue = xQueueCreate(20u, LOGGER_MESSAGE_LENGTH);
    ENSURE(Logger_hQueue != NULL);

    // Create the Logger thread   @todo: Define these values
    ENSURE(xTaskCreate(Logger_ThreadTop,
                       "Logger",
                       1024,
                       (void *)NULL,
                       THREAD_PRIORITY_LOGGER,
                       &Logger_hTask) == pdPASS);

    // Update the isStarted flag to allow log messages to be received
    Logger_isStarted = true;
}


void Logger_Log(const char *fileName, uint16_t lineNumber,
                Logger_Severity_t severity,
                const char *fmt, ...)
{
    ENSURE(fileName);
    ENSURE(fmt);

    // fmt[strcspn(fmt, "\n")] = '\0';
    Logger_StripLFCR(fmt);

    // Generate the variadic args string
    char msgBuf[LOGGER_MESSAGE_LENGTH] = "";
    va_list args;
    va_start(args, fmt);
    vsnprintf(msgBuf,
              LOGGER_MESSAGE_LENGTH,
              fmt,
              args);
    va_end(args);

    // Generate the overall fmt
    char buffer[LOGGER_BUFFER_LENGTH] = ""; // @todo maybe make static & use memset 0?
    snprintf(buffer,                    // Target string
             LOGGER_BUFFER_LENGTH,      // Max output string length
             "%*.*s:%*u|%*.*u|%.*s\n",  // Format string
             // File name
             LOGGER_FILENAME_LENGTH,    // Width (min length)
             LOGGER_FILENAME_LENGTH,    // Precision (max length)
             fileName,                  // Data
             // Line number
             LOGGER_LINENUMBER_LENGTH,  // Width
             lineNumber,                // Data
             // Severity
             LOGGER_SEVERITY_LENGTH,    // Width
             LOGGER_SEVERITY_LENGTH,    // Precision
             (uint8_t)severity,         // Data
             // Message
             LOGGER_MESSAGE_LENGTH,     // Precision
             msgBuf);                   // Data

    // Add the formatted message to the queue
    if (Logger_isStarted)
    {
        (void)xQueueSend(Logger_hQueue, buffer, 0);
    }
    else
    {
        // @todo: Handle this properly + stats
    }

    // @todo: Add stats (e.g. num logs sent, num failed)?

    // @todo: Add return value + update description
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

void Logger_Initialise(void)
{
    // Ensure that UART is initialised and configure the callback function
    ENSURE(Uart_IsInitialised()); // @todo: Ret val?
    Uart_SetTxCpltCb(Uart1, &Logger_UartTxCpltCb);

    // UART DMA is unused thus far, so notify the task that it is ready
    xTaskNotifyGive(Logger_hTask);

    LOG_INFO("Initialised");
}


void Logger_StripLFCR(const char *string)
{
    ENSURE(string);

    char *pos;
    if ((pos = strchr(string, '\r')) != NULL) *pos = '\0';
    if ((pos = strchr(string, '\n')) != NULL) *pos = '\0';
}


void Logger_ThreadTop(void *params)
{
    LOG_INFO("Started"); // @todo: Maybe send logs from this file to the front of the queue

    Logger_Initialise();

    while (1)
    {
        static char buffer[LOGGER_MESSAGE_LENGTH] = "";

        // Wait indefinitely for a message to arrive in the queue
        (void)xQueueReceive(Logger_hQueue,
                            buffer,
                            portMAX_DELAY); // @todo: Add a finite delay and process return value

        // Wait indefinitely for the UART peripheral to become available
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // @todo: Add a finite delay etc.

        // Send the received message over UART via DMA
        (void)Uart_WriteDMA(Uart1, buffer);
    }

    LOG_INFO("Finished");
}


void Logger_UartTxCpltCb(void) // @todo: Rename UartTransmitCompleteCallback
{
    static BaseType_t higherPrioTaskWoken;

    // Notify the logger thread that the UART is ready and yield if necessary
    higherPrioTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(Logger_hTask, &higherPrioTaskWoken);
    portYIELD_FROM_ISR(higherPrioTaskWoken);
}
