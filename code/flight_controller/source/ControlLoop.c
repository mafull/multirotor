// --- Public header ---
#include "ControlLoop.h"

// --- Private header ---
#define CONTROL_LOOP_PRIVATE
    #include "ControlLoop_private.h"
#undef CONTROL_LOOP_PRIVATE


// --- Project includes ---
#include "Logger.h"
#include "macros.h"
#include "threadPriorities.h"

// --- Library includes ---

// --- Standard includes ---


/******************************************************************************
  Private Data
 ******************************************************************************/

TaskHandle_t ControlLoop_hTask = NULL;

bool ControlLoop_isInitialised = false;

bool ControlLoop_isStarted = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

void ControlLoop_Run(void)
{
    ENSURE(!ControlLoop_isStarted);
    ControlLoop_isStarted = true;

    ENSURE(xTaskCreate(ControlLoop_ThreadTop,
                       "ControlLoop",
                       1024,
                       (void *)NULL,
                       THREAD_PRIORITY_CONTROL,
                       &ControlLoop_hTask) == pdPASS);
}

/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

void ControlLoop_ThreadTop(void *params)
{
    LOG_INFO("Started");

    while (1)
    {
        LOG_INFO("TICK");
        vTaskDelay(1000);
    }

    LOG_INFO("Finished");
}