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


void Imu_Update(void)
{
    ENSURE(Imu_isInitialised);

    static Imu_Data_t data = { 0 }; // Static so it isn't repeatedly allocated

    // MPU6050_GetData();



    // @todo: Lock mutex
    Imu_data = data;
    Imu_isDataNew = true;
    // @todo: Unlock mutex
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


        // DO OTHER STUFF

        Imu_isInitialised = true;
    }
    else
    {
        LOG_ERROR("MPU6050 failed to initialise");
    }

    return Imu_isInitialised;
}


void Imu_ThreadTop(void *params)
{
    LOG_INFO("Started");
    (void)Imu_Initialise();

    while (1)
    {
        LOG_DEBUG("TICK");
        vTaskDelay(1000);
    }

    LOG_INFO("Finished");
}