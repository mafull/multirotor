// Project includes
// #include "FlightController.h"

#include "Imu.h"
#include "Logger.h"
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
#include "stm32f4xx_hal.h"

#include "macros.h"



#include "FreeRTOS/FreeRTOS.h"
#include "FreeRTOS/semphr.h"
#include "FreeRTOS/task.h"


TaskHandle_t initTask, ledFlasherTask, loggerTask;
SemaphoreHandle_t initComplete = NULL;
SemaphoreHandle_t initComplete2 = NULL;


void buttonCb(ExternalInterrupt_State_t state)
{
    DigitalOutput_ToggleState(AssertLed);
}


void mpu6050IntCb(ExternalInterrupt_State_t state)
{
    if (Uart_IsInitialised()) Uart_Write(Uart1, "cb");
}


void cb(char c)
{
    // char buffer[16];
    // snprintf(buffer, 16, "Received: %c", c);
    // Uart_Write(Uart1, buffer);
    // DigitalOutput_ToggleState(AssertLed);
}



void InitialisationTask(void *params)
{
    //FlightController_Run();

    (void)Rcc_Initialise();

    (void)Gpio_Initialise();
    (void)Dma_Initialise();


    (void)Uart_Initialise();
    // Uart_Write(Uart1, "Normal transmission test\n");
    // Uart_WriteDMA(Uart1, "DMA transmission test\n");

    // return;
    // Uart_SetCallback(Uart1, cb);
    (void)Logger_Initialise();
    LOG_INFO("UART initialised");
    LOG_INFO("Logger initialised");
    LOG_WARNING("Newline test \n(should be stripped)\n");

    // return;
    char buildString[128] = "";
    snprintf(buildString,
             128,
             "Build time: %s %s",
             __DATE__,
             __TIME__);
    LOG_INFO(buildString);





    (void)DigitalOutput_Initialise();

    (void)ExternalInterrupt_Initialise();
    ExternalInterrupt_SetCallback(UserButton, &buttonCb);
    ExternalInterrupt_SetCallback(MPU6050_Int, &mpu6050IntCb);
    ExternalInterrupt_EnableIT(UserButton, true);
    // ExternalInterrupt_EnableIT(MPU6050_Int, true);



    // const bool i2cOk = I2c_Initialise();
    // LOG_INFO(i2cOk ? "I2C initialised successfully" : "I2C failed to initialise");

    // const bool imuOk = Imu_Initialise();
    // LOG_INFO(imuOk ? "IMU initialised successfully" : "IMU failed to initialise");


    // (void)Timer_Initialise();

    // if (PwmOutput_Initialise())
    // {
    //     PwmOutput_SetPulseWidth(Out_Ch1, 1000);
    //     PwmOutput_SetPulseWidth(Out_Ch2, 1000);
    //     PwmOutput_SetPulseWidth(Out_Ch3, 1000);
    //     PwmOutput_SetPulseWidth(Out_Ch4, 1000);
    //     PwmOutput_Start(Out_Ch1);
    //     PwmOutput_Start(Out_Ch2);
    //     PwmOutput_Start(Out_Ch3);
    //     PwmOutput_Start(Out_Ch4);
    // }

    // if (PwmInput_Initialise())
    // {
    //     LOG_INFO("PwmInput initialised successfully");
    //     PwmInput_Start(In_Ch1);
    //     PwmInput_Start(In_Ch2);
    //     PwmInput_Start(In_Ch3);
    //     PwmInput_Start(In_Ch4);
    // }
    // else
    // {
    //     LOG_ERROR("PwmInput failed to initialised");
    // }

    xSemaphoreGive(initComplete);
    xSemaphoreGive(initComplete2);
}


void LEDFlasherTask(void *params)
{
    xSemaphoreTake(initComplete, portMAX_DELAY);

    uint32_t count = 0u;
    while (1)
    {
        if (!(count % 1)) DigitalOutput_ToggleState(ControlLed);
        if (!(count % 2)) DigitalOutput_ToggleState(ImuLed);
        if (!(count % 4)) DigitalOutput_ToggleState(LoggerLed);
        if (!(count % 8)) DigitalOutput_ToggleState(UnusedLed);

        vTaskDelay(200);
        count++;
    }
}


void LoggerTask(void *params)
{
    xSemaphoreTake(initComplete2, portMAX_DELAY);

    while (1)
    {
        LOG_DEBUG("Tick");
        vTaskDelay(1000);
    }
}



int main(void)
{

    // InitialisationTask(NULL);

    xTaskCreate(InitialisationTask,
                "InitTask",
                2048,
                (void *)NULL,
                tskIDLE_PRIORITY + 2UL,
                &initTask);

    xTaskCreate(LEDFlasherTask,
                "LEDTask",
                1024, //configMINIMAL_STACK_SIZE,
                (void *)NULL,
                tskIDLE_PRIORITY + 2UL,
                &ledFlasherTask);

    xTaskCreate(LoggerTask,
                "LoggerTask",
                1024,//configMINIMAL_STACK_SIZE,
                (void *)NULL,
                tskIDLE_PRIORITY + 2UL,
                &loggerTask);

    initComplete = xSemaphoreCreateBinary();
    initComplete2 = xSemaphoreCreateBinary();

    vTaskStartScheduler();

    // UNREACHABLE();

    return 0;




    uint32_t pw = 20u;
    uint32_t pwIn = 0u;
    bool up = false;
    while (true)
    {
        pw = up ? pw + 10 : pw - 10;

        if (pw >= 2000) up = false;
        if (pw <= 20) up = true;

        PwmInput_GetPulseWidth(In_Ch1, &pwIn);

    #if 0
        PwmOutput_SetPulseWidth(Out_Ch1, pw);
    #else
        PwmOutput_SetPulseWidth(Out_Ch1, pwIn > 900 ? (pwIn - 900)*2 : 0);
    #endif
        
        static char pulseMsg[50] = "";
        // snprintf(pulseMsg,
        //          50,
        //          "Pulse in: %5u Out: %5u",
        //          pwIn,
        //          PwmOutput_GetPulseWidth(Out_Ch1));

        static uint32_t in[4];
        PwmInput_GetPulseWidth(In_Ch1, &in[0]);
        PwmInput_GetPulseWidth(In_Ch2, &in[1]);
        PwmInput_GetPulseWidth(In_Ch3, &in[2]);
        PwmInput_GetPulseWidth(In_Ch4, &in[3]);
        snprintf(pulseMsg,
                 50,
                 "%4lu %4lu %4lu %4lu",
                 in[0], in[1], in[2], in[3]);
        LOG_INFO(pulseMsg);

        HAL_Delay(10);
    }


    uint32_t count = 0u;
    while (++count)
    {
        if (!(count % 1)) DigitalOutput_ToggleState(ControlLed);
        if (!(count % 2)) DigitalOutput_ToggleState(ImuLed);
        if (!(count % 4)) DigitalOutput_ToggleState(LoggerLed);
        if (!(count % 8)) DigitalOutput_ToggleState(UnusedLed);

        uint8_t whoAmI = 0x00;
        const bool readOkay = I2c_ReadMemory(I2c1, 0x68, 0x75, &whoAmI, 1u);

        static char msg[128] = "";
        snprintf(msg,
                 128,
                 "Tick: %3s | WHO_AM_I(%s): 0x%02X",
                 (DigitalOutput_GetState(AssertLed) == On) ? "ON" : "OFF",
                 readOkay ? "good" : "bad",
                 whoAmI);
        LOG_DEBUG(msg);

        HAL_Delay(500);
    }

    return -1;
}


void vApplicationTickHook(void)
{

}

void vApplicationMallocFailedHook(void)
{

}

void vApplicationStackOverflowHook(void)
{

}