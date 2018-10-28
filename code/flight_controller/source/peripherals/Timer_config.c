// --- Public header ---
#include "peripherals/Timer.h"

// --- Private header ---
#define TIMER_PRIVATE
    #include "peripherals/Timer_private.h"
#undef TIMER_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

const Timer_ConfigData_t Timer_configData[Timer_Instance_MAX] = 
    {
        /*
          | Instance
          |     | TIM Init Struct
          |     | | Prescaler
          |     | |    | Counter Mode      | Period    | Clock Division        | Repetition Counter
        */
        { TIM1, { 167, TIM_COUNTERMODE_UP,       2499, TIM_CLOCKDIVISION_DIV1, 0} }, // Timer1
        { TIM2, {  83, TIM_COUNTERMODE_UP, 0xFFFFFFFF, TIM_CLOCKDIVISION_DIV1, 0} }, // Timer2
        { TIM3, {  83, TIM_COUNTERMODE_UP, 0xFFFFFFFF, TIM_CLOCKDIVISION_DIV1, 0} }, // Timer3
        { TIM4, {  83, TIM_COUNTERMODE_UP,       2499, TIM_CLOCKDIVISION_DIV1, 0} }, // Timer4
    };
