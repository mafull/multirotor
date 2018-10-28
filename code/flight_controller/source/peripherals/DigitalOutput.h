#ifndef __DIGITAL_OUTPUT_H
#define __DIGITAL_OUTPUT_H


// --- Standard includes ---
#include <stdbool.h>


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 * Enum defining the available Digital Outputs
 */
typedef enum DigitalOutput_Instance_e
{
    AssertLed = 0u,
    ControlLed,
    ImuLed,
    LoggerLed,
    UnusedLed,
    
    DigitalOutput_Instance_MAX
} DigitalOutput_Instance_t;

/**
 * Enum defining the possible states of a Digital Output
 */
typedef enum DigitalOutput_State_e
{
    On,
    Off
} DigitalOutput_State_t;


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 * Get the state of a Digital Output
 *
 * @param instance The Digital Output to query
 * 
 * @return The current state of the Digital Output
 */
DigitalOutput_State_t DigitalOutput_GetState(DigitalOutput_Instance_t instance);

/**
 * Initialise all Digital Outputs
 *
 * @retval true If initialisation is successful
 */
bool DigitalOutput_Initialise(void);

/**
 * Check if the available Digital Outputs are initialised
 *
 * @retval true If initialised
 */
bool DigitalOutput_IsInitialised(void);

/**
 * Set the state of a Digital Output
 *
 * @param instance The Digital Output to update
 * @param newState The state to update the Digital Output with
 */
bool DigitalOutput_SetState(DigitalOutput_Instance_t instance,
                            DigitalOutput_State_t newState);

/**
 * Toggle the state of a Digital Output
 *
 * @param instance The Digital Output to update
 */
void DigitalOutput_ToggleState(DigitalOutput_Instance_t instance);


#endif // __DIGITAL_OUTPUT_H
