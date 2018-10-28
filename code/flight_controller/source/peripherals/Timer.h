#ifndef __TIMER_H
#define __TIMER_H


// --- Project includes ---

// --- Library includes ---

// --- Standard includes ---
#include <stdbool.h>


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 *
 */
typedef enum Timer_Instance_e
{
    Timer1 = 0u,
    Timer2,
    Timer3,
    Timer4,

    Timer_Instance_MAX
} Timer_Instance_t;

/**
 *
 */
typedef struct Timer_OCConfigData_s
{
    uint32_t channel;
    TIM_OC_InitTypeDef initStruct;
} Timer_OCConfigData_t;


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool Timer_ConfigureOC(Timer_Instance_t instance, Timer_OCConfigData_t *ocConf);

/**
 *
 */
uint32_t Timer_GetPWMPulseWidth(Timer_Instance_t instance, uint32_t channel);

/**
 *
 */
bool Timer_Initialise(void);

/**
 *
 */
bool Timer_IsInitialised(void);

/**
 *
 */
void Timer_SetPWMPulseWidth(Timer_Instance_t instance,
                            uint32_t channel,
                            uint32_t pulseWidth);

/**
 *
 */
bool Timer_StartPWM(Timer_Instance_t instance, uint32_t channel);

/**
 *
 */
bool Timer_StopPWM(Timer_Instance_t instance, uint32_t channel);


#endif // __TIMER_H
