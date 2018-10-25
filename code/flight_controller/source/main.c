// Project includes
// #include "FlightController.h"

#include "Imu.h"
#include "peripherals/DigitalOutput.h"
#include "peripherals/ExternalInterrupt.h"
#include "peripherals/I2c.h"
#include "peripherals/Rcc.h"
#include "peripherals/Uart.h"
#include "stm32f4xx_hal.h"

void cb(char c)
{
    // char buffer[16];
    // snprintf(buffer, 16, "\nReceived: %c\n", c);
    // Uart_Write(Uart1, buffer);
    DigitalOutput_SetState(
        AssertLed,
        DigitalOutput_GetState(AssertLed) == Off ? On : Off);
}

int main(void)
{
    //FlightController_Run();

    Rcc_Initialise();

    DigitalOutput_Initialise(AssertLed);
    DigitalOutput_Initialise(ControlLed);
    DigitalOutput_Initialise(IMULed);
    DigitalOutput_Initialise(LoggerLed);
    DigitalOutput_Initialise(UnusedLed);

    ExternalInterrupt_Initialise(MPU6050Int);
    ExternalInterrupt_Initialise(UserButton);

    Uart_Initialise(Uart1);
    // Uart_SetCallback(Uart1, cb);
    Uart_Write(Uart1, "UART1 initialised\n");

    char buildString[128] = "";
    snprintf(buildString,
             128,
             "%s %s\n",
             __DATE__,
             __TIME__);
    Uart_Write(Uart1, buildString);
    Uart_Write(Uart1, "UART1 initialised\n");

    I2c_Initialise(I2c1);
    const bool success = Imu_Initialise();
    Uart_Write(
        Uart1,
        success ? "IMU initialised successfully\n" : "IMU failed to initialise\n");
    

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
        const bool readOkay = I2c_ReadMemory(I2c1, 0x68, 0x75, &whoAmI, 1u);

        static char msg[128] = "";
        snprintf(msg,
                 128,
                 "Tick: %3s | WHO_AM_I(%s): 0x%02X\n",
                 on ? "ON" : "OFF",
                 readOkay ? "good" : "bad",
                 whoAmI);
        Uart_Write(Uart1, msg);

        on = (DigitalOutput_GetState(AssertLed) == Off);
        HAL_Delay(500);
    }

    return -1;
}
