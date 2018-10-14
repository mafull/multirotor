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

        uint8_t whoAmI = 0x00;
        I2c_ReadMemory(I2c1, 0x68, 0x75, &whoAmI, 1u);

        static char msg[128] = "";
        snprintf(msg,
                 128,
                 "Tick: %3s | WHO_AM_I: 0x%02X\n",
                 on ? "ON" : "OFF",
                 whoAmI);
        Uart_Write(Uart1, msg);

        on = (DigitalOutput_GetState(AssertLed) == Off);
        HAL_Delay(500);
    }

    return -1;
}
