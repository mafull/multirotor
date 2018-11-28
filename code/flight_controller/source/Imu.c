// --- Public header ---
#include "Imu.h"

// --- Private header ---
#define IMU_PRIVATE
    #include "Imu_private.h"
#undef IMU_PRIVATE


// --- Project includes ---
#include "devices/MPU6050.h"
#include "Logger.h"
#include "macros.h"
#include "threadPriorities.h"

// --- Library includes ---

// --- Standard includes ---


/******************************************************************************
  Private Data
 ******************************************************************************/

Imu_Data_t Imu_data = { 0 };

TaskHandle_t Imu_hTask = NULL;

bool Imu_isDataNew = false;
bool Imu_isInitialised = false;
bool Imu_isStarted = false;


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool Imu_GetNewData(Imu_Data_t *const data)
{
    ENSURE(data);
    ENSURE(Imu_isInitialised);

    // @todo: Lock mutex
    *data = Imu_data;
    const bool isDataNew = Imu_isDataNew;
    // @todo: Unlock mutex

    return isDataNew;
}


void Imu_Run(void)
{
    ENSURE(!Imu_isStarted);

    // Create the IMU thread
    ENSURE(xTaskCreate(Imu_ThreadTop,
                       "IMU",
                       1024,
                       (void *)NULL,
                       THREAD_PRIORITY_IMU,
                       &Imu_hTask) == pdPASS);

    Imu_isStarted = true;
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

bool Imu_Initialise(void)
{
    ENSURE(!Imu_isInitialised);

    if (MPU6050_Initialise())
    {
        LOG_INFO("MPU6050 initialised successfully");

        MPU6050_SetDataReadyCallback(&Imu_MPU6050DataReadyCallback);


        // DO OTHER STUFF

        Imu_isInitialised = true;
    }
    else
    {
        LOG_ERROR("MPU6050 failed to initialise");
    }

    return Imu_isInitialised;
}


void Imu_MPU6050DataReadyCallback(void)
{
    static BaseType_t higherPrioTaskWoken;

    /* Notify the IMU thread that new MPU6050 data is available and yield if
    necessary */
    higherPrioTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(Imu_hTask, &higherPrioTaskWoken);
    portYIELD_FROM_ISR(higherPrioTaskWoken);
}


void Imu_ThreadTop(void *params)
{
    LOG_INFO("Started");
    (void)Imu_Initialise();

    while (1)
    {
        LOG_DEBUG("Waiting for new data to become available");


        // Wait indefinitely for new data to become available
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // @todo: Add finite delay/use ret val

        static Imu_Data_t imuData = { 0 };

        static MPU6050_Data_t mpu6050Data = { 0 };

        // Generate useable MPU6050 data from the raw data read from its sensors
        // @todo: Prevent raw data from being updated via DMA
        MPU6050_ProcessRawData(&mpu6050Data);
        // @todo: Allow raw data to be updated again


        LOG_DEBUG("TICK");
        vTaskDelay(1000);
    }

    LOG_INFO("Finished");
}






/*
    Getting data from MPU6050:
        IMU Thread:
            Block, waiting on data ready signal (WHAT IS IT?)
            ###


            Process raw data:
                Generate raw sensor data from raw byte data
                Signal that the raw data has been used (+ SOMETHING DMA SIGNAL RELATED HERE)
                Scale raw sensor data and apply callibration offsets

            Deal with processed data
                

        MPU6050 interrupt:
            Trigger DMA read
                8-bit data (or 16, but would need changing if I stop using HAL in the future)
                14 reads (or 7 reads if 16-bit data)

        DMA complete interrupt:
            Signal that data is ready (WHAT TYPE OF SIGNAL?)

        DMA error interrupt:
            Increment failure counter


        ControlLoop Thread:
            ???
*/
