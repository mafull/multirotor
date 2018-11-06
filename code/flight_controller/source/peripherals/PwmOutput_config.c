// --- Public header ---
#include "peripherals/PwmOutput.h"

// --- Private header ---
#define PWM_OUTPUT_PRIVATE
    #include "peripherals/PwmOutput_private.h"
#undef PWM_OUTPUT_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

const PwmOutput_ConfigData_t PwmOutput_configData[PwmOutput_Instance_MAX] = 
    {
        /*
                  | Timer Instance
                  |       | Channel      | Init Struct
                  |                      | | Mode           | Pulse
                  |                      | |                |  | Output Polarity    | Complimentary Output Polarity
                  |                      | |                |  |                    |  | Fast Mode         | Idle Pin State
                  |                      | |                |  |                    |  |                   |  | Complementary Idle Pin State
        */
        // Timer 1
        [Out_Ch1] = { Timer1, TIM_CHANNEL_1, { TIM_OCMODE_PWM1, 0, TIM_OCPOLARITY_HIGH, 0, TIM_OCFAST_DISABLE, 0, 0} },
        [Out_Ch2] = { Timer1, TIM_CHANNEL_2, { TIM_OCMODE_PWM1, 0, TIM_OCPOLARITY_HIGH, 0, TIM_OCFAST_DISABLE, 0, 0} },
        [Out_Ch3] = { Timer1, TIM_CHANNEL_3, { TIM_OCMODE_PWM1, 0, TIM_OCPOLARITY_HIGH, 0, TIM_OCFAST_DISABLE, 0, 0} },
        [Out_Ch4] = { Timer1, TIM_CHANNEL_4, { TIM_OCMODE_PWM1, 0, TIM_OCPOLARITY_HIGH, 0, TIM_OCFAST_DISABLE, 0, 0} },
        // Timer 4
        // [Out_Ch5] = { Timer4, TIM_CHANNEL_1, { TIM_OCMODE_PWM1, 0, TIM_OCPOLARITY_HIGH, 0, TIM_OCFAST_DISABLE, 0, 0} },
        // [Out_Ch6] = { Timer4, TIM_CHANNEL_2, { TIM_OCMODE_PWM1, 0, TIM_OCPOLARITY_HIGH, 0, TIM_OCFAST_DISABLE, 0, 0} },
        // [Out_Ch7] = { Timer4, TIM_CHANNEL_3, { TIM_OCMODE_PWM1, 0, TIM_OCPOLARITY_HIGH, 0, TIM_OCFAST_DISABLE, 0, 0} },
        // [Out_Ch8] = { Timer4, TIM_CHANNEL_4, { TIM_OCMODE_PWM1, 0, TIM_OCPOLARITY_HIGH, 0, TIM_OCFAST_DISABLE, 0, 0} },
    };
