// --- Public header ---
#include "peripherals/PwmInput.h"

// --- Private header ---
#define PWM_INPUT_PRIVATE
    #include "peripherals/PwmInput_private.h"
#undef PWM_INPUT_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

const PwmInput_ConfigData_t PwmInput_configData[PwmInput_Instance_MAX] = 
    {
        /*
                     | Timer Instance
                     |       | Timer index
                     |       |  | Channel      | Channel index
                     |       |  |              |  | GPIO Instance
                     |       |  |              |  |              | Init Struct
                     |       |  |              |                 | | Polarity                         | Input Selection         | Prescaler     | Filter
        */
        // Timer 2
        [In_Ch1] = { Timer2, 1, TIM_CHANNEL_1, 0, Gpio_Tim2_Ch1, { TIM_INPUTCHANNELPOLARITY_BOTHEDGE, TIM_ICSELECTION_DIRECTTI, TIM_ICPSC_DIV1, 0 } },
        [In_Ch2] = { Timer2, 1, TIM_CHANNEL_2, 1, Gpio_Tim2_Ch2, { TIM_INPUTCHANNELPOLARITY_BOTHEDGE, TIM_ICSELECTION_DIRECTTI, TIM_ICPSC_DIV1, 0 } },
        [In_Ch3] = { Timer2, 1, TIM_CHANNEL_3, 2, Gpio_Tim2_Ch3, { TIM_INPUTCHANNELPOLARITY_BOTHEDGE, TIM_ICSELECTION_DIRECTTI, TIM_ICPSC_DIV1, 0 } },
        [In_Ch4] = { Timer2, 1, TIM_CHANNEL_4, 3, Gpio_Tim2_Ch4, { TIM_INPUTCHANNELPOLARITY_BOTHEDGE, TIM_ICSELECTION_DIRECTTI, TIM_ICPSC_DIV1, 0 } },
        // Timer 3
        // [In_Ch5] = { Timer3, 2, TIM_CHANNEL_1, 0, Gpio_Tim3_Ch1, { TIM_INPUTCHANNELPOLARITY_BOTHEDGE, TIM_ICSELECTION_DIRECTTI, TIM_ICPSC_DIV1, 0 } },
        // [In_Ch6] = { Timer3, 2, TIM_CHANNEL_2, 1, Gpio_Tim3_Ch2, { TIM_INPUTCHANNELPOLARITY_BOTHEDGE, TIM_ICSELECTION_DIRECTTI, TIM_ICPSC_DIV1, 0 } },
        // [In_Ch7] = { Timer3, 2, TIM_CHANNEL_3, 2, Gpio_Tim3_Ch3, { TIM_INPUTCHANNELPOLARITY_BOTHEDGE, TIM_ICSELECTION_DIRECTTI, TIM_ICPSC_DIV1, 0 } },
        // [In_Ch8] = { Timer3, 2, TIM_CHANNEL_4, 3, Gpio_Tim3_Ch4, { TIM_INPUTCHANNELPOLARITY_BOTHEDGE, TIM_ICSELECTION_DIRECTTI, TIM_ICPSC_DIV1, 0 } },
    };
