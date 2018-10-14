// Project includes
// #include "FlightController.h"

#include "peripherals/DigitalOutput.h"
#include "peripherals/I2c.h"
#include "peripherals/Rcc.h"
#include "peripherals/Uart.h"
#include "stm32f4xx_hal.h"



int main(void)
{
    //FlightController_Run();

    Rcc_Initialise();

    DigitalOutput_Initialise(AssertLed);
    DigitalOutput_Initialise(ControlLed);
    DigitalOutput_Initialise(IMULed);
    DigitalOutput_Initialise(LoggerLed);
    DigitalOutput_Initialise(UnusedLed);

    I2c_Initialise(I2c1);

    Uart_Initialise(Uart1);

    bool on = false;
    uint32_t count = 0u;
    while (++count)
    {
        DigitalOutput_SetState(AssertLed, on ? On : Off);

        if (!(count % 1))
        {
            DigitalOutput_SetState(
                ControlLed, 
                (DigitalOutput_GetState(ControlLed) == Off) ? On : Off);
        }

        if (!(count % 2))
        {
            DigitalOutput_SetState(
                IMULed, 
                (DigitalOutput_GetState(IMULed) == Off) ? On : Off);
        }

        if (!(count % 4))
        {
            DigitalOutput_SetState(
                LoggerLed, 
                (DigitalOutput_GetState(LoggerLed) == Off) ? On : Off);
        }

        if (!(count % 8))
        {
            DigitalOutput_SetState(
                UnusedLed, 
                (DigitalOutput_GetState(UnusedLed) == Off) ? On : Off);
        }


        Uart_Write(Uart1, "Tick ");
        Uart_Write(Uart1, (on ? "ON" : "OFF"));
        Uart_Write(Uart1, "\n");

        on = (DigitalOutput_GetState(AssertLed) == Off);
        HAL_Delay(500);
    }

    return -1;
}
