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

void Imu_CombineSensorData(const MPU6050_Data_t *const mpu6050Data,
                           /*const HMC5883L_Data_t *const hmc5883lData,*/
                           Imu_Data_t *const imuData)
{
    ENSURE(mpu6050Data);
    // ENSURE(hmc5883lData);
    ENSURE(imuData);

    ENSURE(mpu6050Data->timestamp.hasValue);
    // ENSURE(hmc5883lData->timestamp.hasValue);

    const bool firstPacket =    (!imuData->timestamp.hasValue)
                             && (imuData->timestamp.value == 0);

    if (!firstPacket)
    {
        // Calculate the time since the previous packet in seconds
        const Timestamp_t dt_timestamp =
            (mpu6050Data->timestamp.value - imuData->timestamp.value);
        const float dt_s = (float)dt_timestamp; // @todo: Timestamp implmentation, plus maybe replace float with Imu_DataType_t?

        // Copy angular rates

        // Calculate accelerometer-based attitude


        // Calculate gyroscope-based attitude
        // gAngX += mpu6050Data.gyro.x * dt_s;
        // gAngY += mpu6050Data.gyro.y * dt_s;
        // gAngZ += mpu6050Data.gyro.z * dt_s;

        imuData->timestamp.hasValue = true;
    }
    else // First data packet
    {
        
    }



    LOG_ERROR("UNIMPLEMENTED"); // @todo: Implement
}


bool Imu_Initialise(void)
{
    ENSURE(!Imu_isInitialised);

#if 0
    MPU6050_SetDataReadyCallback(&Imu_MPU6050DataReadyCallback);
    bool success = MPU6050_Initialise();

    if (success)
    {
        LOG_INFO("MPU6050 initialised successfully");
    }
    else
    {
        LOG_ERROR("MPU6050 failed to initialise");
    }
#else
    LOG_ERROR("NOT ACTUALLY INITIALISING");
    const bool success = true;
#endif
    Imu_isInitialised = success;
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
        LOG_DEBUG("Waiting for new data to become available"); // @todo: Probably remove

        // Wait indefinitely for new data to become available
        (void)ulTaskNotifyTake(pdTRUE, portMAX_DELAY); // @todo: Add finite delay/use ret val

        static Imu_Data_t imuData = { 0 };

        static MPU6050_Data_t mpu6050Data = { 0 };
        // static HMC5883L_Data_t hmc5883lData = { 0 };

        // Generate useable data from the raw data read from sensors
        // @todo: Prevent raw data from being updated via DMA
        MPU6050_ProcessRawData(&mpu6050Data);
        // HMC5883L_ProcessRawData(&hmc5883lData);
        // @todo: Allow raw data to be updated again

        // Combine the accelerometer/gyroscope/magnetometer data
        Imu_CombineSensorData(&mpu6050Data, /*&hmc5883lData,*/ &imuData);

        // USE THE DATA - SEND TO CONTROL THREAD?

        LOG_DEBUG("TICK"); // @todo: Remove
        vTaskDelay(1000);  // @todo: Remove
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
