// --- Public header ---
#include "FlightController.h"

// --- Private header ---
#define FLIGHT_CONTROLLER_PRIVATE
    #include "FlightController_private.h"
#undef FLIGHT_CONTROLLER_PRIVATE


// --- Project includes ---
#include "Imu.h"
#include "Logger.h"
#include "macros.h"
#include "peripherals/DigitalOutput.h"
#include "peripherals/Dma.h"
#include "peripherals/Gpio.h"
#include "peripherals/ExternalInterrupt.h"
#include "peripherals/I2c.h"
#include "peripherals/PwmInput.h"
#include "peripherals/PwmOutput.h"
#include "peripherals/Rcc.h"
#include "peripherals/Timer.h"
#include "peripherals/Uart.h"
#include "threadPriorities.h"

// --- Library includes ---

// --- Standard includes ---

/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

TaskHandle_t FlightController_hTask = NULL;

bool FlightController_isStarted = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

void FlightController_Run(void)
{
    // Check that the FlightController hasn't already been started
    ENSURE(!FlightController_isStarted);
    FlightController_isStarted = true;

    // Create the initialisation thread @todo: Define these values
    ENSURE(xTaskCreate(FlightController_ThreadTop,
                       "Init",
                       1024,
                       (void *)NULL,
                       THREAD_PRIORITY_INITIALISATION,
                       &FlightController_hTask) == pdPASS);

    // Start the scheduler
    vTaskStartScheduler();

    UNREACHABLE(); // Something has gone wrong
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

void FlightController_InitialisePeripherals(void)
{
    // Reset and clock control
    (void)Rcc_Initialise();

    // Base modules
    (void)Gpio_Initialise();
    (void)Dma_Initialise();
    // (void)Timer_Initialise();

    // Simple IO
    (void)DigitalOutput_Initialise();
    (void)ExternalInterrupt_Initialise();

    // Communication
    // (void)I2c_Initialise();
    (void)Uart_Initialise();

    // Timer-based IO
    // (void)PwmInput_Initialise();
    // (void)PwmOutput_Initialise();
}

#if 1
TaskHandle_t hFlashyTask = NULL;
void FlashyFunc(void *params)
{
    vTaskDelay(100);

    uint32_t count = 0u;
    while (1)
    {
        LOG_DEBUG("Flash %u", count);
        if (!(count % 1)) DigitalOutput_ToggleState(ControlLed);
        if (!(count % 2)) DigitalOutput_ToggleState(ImuLed);
        if (!(count % 4)) DigitalOutput_ToggleState(LoggerLed);
        if (!(count % 8)) DigitalOutput_ToggleState(UnusedLed);

        vTaskDelay(200);
        count++;
    }
}
#endif


void FlightController_ThreadTop(void *params)
{
    // Initialise microcontroller peripherals
    FlightController_InitialisePeripherals();

#if 1
    xTaskCreate(FlashyFunc,
                "Flashy",
                1024,
                (void *)NULL,
                (tskIDLE_PRIORITY + 2u),
                &hFlashyTask);
#endif

    // Start the threads
    Logger_Run();
    Imu_Run();

    LOG_INFO("Finished");
}


/******************************************************************************
  Callback Functions
 ******************************************************************************/

// @todo: Move these
void vApplicationTickHook(void)
{

}

void vApplicationMallocFailedHook(void)
{

}

void vApplicationStackOverflowHook(void)
{

}