// Project includes
// #include "FlightController.h"

#include "peripherals/DigitalOutput.h"
#include "peripherals/RCC.h"
#include "peripherals/UART.h"
#include "stm32f4xx_hal.h"



int main(void)
{
    //FlightController_Run();

    RCC_Initialise();

    DigitalOutput_Initialise(AssertLED);
    DigitalOutput_Initialise(ControlLED);
    DigitalOutput_Initialise(IMULED);
    DigitalOutput_Initialise(LoggerLED);
    DigitalOutput_Initialise(UnusedLED);

    UART_Initialise(UART1);

    bool on = false;
    uint32_t count = 0u;
    while (++count)
    {
        DigitalOutput_SetState(AssertLED, on ? On : Off);

        if (!(count % 1))
        {
            DigitalOutput_SetState(
                ControlLED, 
                (DigitalOutput_GetState(ControlLED) == Off) ? On : Off);
        }

        if (!(count % 2))
        {
            DigitalOutput_SetState(
                IMULED, 
                (DigitalOutput_GetState(IMULED) == Off) ? On : Off);
        }

        if (!(count % 4))
        {
            DigitalOutput_SetState(
                LoggerLED, 
                (DigitalOutput_GetState(LoggerLED) == Off) ? On : Off);
        }

        if (!(count % 8))
        {
            DigitalOutput_SetState(
                UnusedLED, 
                (DigitalOutput_GetState(UnusedLED) == Off) ? On : Off);
        }


        UART_Write(UART1, "Tick ");
        UART_Write(UART1, (on ? "ON" : "OFF"));
        UART_Write(UART1, "\n");

        on = (DigitalOutput_GetState(AssertLED) == Off);
        HAL_Delay(500);
    }

    return -1;
}
