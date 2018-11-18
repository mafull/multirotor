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

QueueHandle_t Logger_hQueue = NULL;
TaskHandle_t Logger_hTask = NULL;

bool Logger_isInitialised = false;
bool Logger_isStarted = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

void Logger_Run(void)
{
    ENSURE(!Logger_isStarted);
    Logger_isStarted = true;

    // Create the log message queue
    Logger_hQueue = xQueueCreate(20u, LOGGER_MESSAGE_LENGTH);
    ENSURE(Logger_hQueue != NULL);

    // Create the Logger thread @todo: Define these values
    ENSURE(xTaskCreate(Logger_ThreadTop,
                       "Logger",
                       1024,
                       (void *)NULL,
                       THREAD_PRIORITY_LOGGER,
                       &Logger_hTask) == pdPASS);

    // UART DMA is unused thus far, so notify the task that it is ready
    xTaskNotifyGive(Logger_hTask);
}

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


void Logger_Log(const char *fileName, uint16_t lineNumber,
                Logger_Severity_t severity,
                const char *message, ...)
{
    // @todo: Make this thread safe (i.e. use a message queue)
    ENSURE(fileName);
    ENSURE(message);
    ENSURE(Logger_isInitialised);

    // @todo: Maybe strip LF/CR characters from message?
    // message[strcspn(message, "\n")] = '\0';
    Logger_StripLFCR(message);

    char msgBuf[LOGGER_MESSAGE_LENGTH] = "";
    va_list args;
    va_start(args, message);
    vsnprintf(msgBuf,
              LOGGER_MESSAGE_LENGTH,
              message,
              args);
    va_end(args);

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
             // LOGGER_LINENUMBER_LENGTH,  // Precision
             lineNumber,                // Data
             // Severity
             LOGGER_SEVERITY_LENGTH,    // Width
             LOGGER_SEVERITY_LENGTH,    // Precision
             (uint8_t)severity,         // Data
             // Message
             LOGGER_MESSAGE_LENGTH,     // Precision
             msgBuf);                   // Data

    (void)xQueueSend(Logger_hQueue, buffer, 0);

    // const bool success = Uart_Write(Uart1, buffer); // @todo: Move Uart1 to config
    // UNUSED(success);
    // @todo: Add stats (e.g. num logs sent, num failed)?
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

void Logger_StripLFCR(const char *string)
{
    ENSURE(string);

    char *pos;
    if ((pos = strchr(string, '\r')) != NULL) *pos = '\0';
    if ((pos = strchr(string, '\n')) != NULL) *pos = '\0';
}

void Logger_ThreadTop(void *params)
{
    // INITIALISE STUFF HERE
    Uart_SetTxCpltCb(Uart1, &Logger_UartTxCpltCb);

    LOG_INFO("Initialised");

    while (1)
    {
        static char buffer[LOGGER_MESSAGE_LENGTH] = "";

        (void)xQueueReceive(Logger_hQueue,
                      buffer,
                      portMAX_DELAY);

        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        (void)Uart_WriteDMA(Uart1, buffer);
    }
}

#include "peripherals/DigitalOutput.h"
void Logger_UartTxCpltCb(void)
{
    // https://www.freertos.org/RTOS_Task_Notification_As_Binary_Semaphore.html


    // static BaseType_t higherPrioTaskTaken = pdFALSE;
    // xSemaphoreGiveFromISR(Logger_uartReadySignal, &higherPrioTaskTaken);
    // portYIELD_FROM_ISR(higherPrioTaskTaken);
    
    DigitalOutput_ToggleState(AssertLed);

    static BaseType_t higherPrioTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(Logger_hTask, &higherPrioTaskWoken);

    portYIELD_FROM_ISR(higherPrioTaskWoken);
}