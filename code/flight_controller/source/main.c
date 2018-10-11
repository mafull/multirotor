// Project includes
// #include "FlightController.h"

#include "peripherals/UART.h"

int main(void)
{
    //FlightController_Run();

    UART_Initialise(UART_Instance_UART1);
    UART_Write(UART_Instance_UART1, "Hello world!");

    return 0; // -1;
}
