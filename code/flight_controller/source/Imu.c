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

// --- Library includes ---

// --- Standard includes ---


/******************************************************************************
  Private Data
 ******************************************************************************/

Imu_Data_t Imu_data = { 0 };

bool Imu_isInitialised = false;

bool Imu_isDataNew = false;


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


bool Imu_IsInitialised(void)
{
    return Imu_isInitialised;
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
