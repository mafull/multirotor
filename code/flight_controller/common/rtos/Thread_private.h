#ifndef __THREAD_PRIVATE_H
#define __THREAD_PRIVATE_H


#include "FreeRTOS/task.h"


/******************************************************************************
  Private Data Types
 ******************************************************************************/

/**
 *
 */
typedef struct Thread_s
{
    // Name
    Thread_FunctionPointer_t runFunction;
    TaskHandle_t *freeRTOSTaskHandle;
} Thread_t;


#endif // __THREAD_PRIVATE_H
