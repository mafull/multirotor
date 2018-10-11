// Public header
#include "Thread.h"

// Private header
#define __THREAD_C
#include "Thread_private.h"
#undef // __THREAD_C


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

/**
 *
 */
void Thread_StartScheduler(void)
{
    vTaskStartScheduler();
}