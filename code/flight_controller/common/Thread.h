#ifndef __THREAD_H
#define __THREAD_H


#include "Thread_private.h"

// Library includes
#include "FreeRTOS/task.h"


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 *
 */
typedef void (*Thread_FunctionPointer_t)(void);


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
Thread_t Thread_CreateThread(// Name string,
                             // Stack depth,
                             // Priority,
                             // Run function
                             void);

/**
 *
 */
void Thread_StartScheduler(void);


#endif // __THREAD_H
