#include "IMUThread.hpp"

// IMUThread::IMUThread()
// {

//}

IMUThread::~IMUThread()
{

}

void IMUThread::Run()
{
    ASSERT(_imu);

    // SET PWM OUTPUTS TO TURN MOTORS OFF
    // LOAD DATA FROM EEPROM


    const IMU_Data_t& imuData = _imu->getData();

    while (1)
    {
        /*
        PROCESS INPUTS
            MESSAGE QUEUE
            CONTROL INPUTS
            SENSOR READINGS
        */

        _imu->update();

        /*
        GENERATE OUTPUTS
            UPDATE PIDS
            MIX MOTOR OUTPUTS
        */

        /*
        OUTPUT
            LOGGING
            INDICATION LEDS
            UPDATE PWM OUTPUTS
        */

        // MAINTAIN CONSTANT LOOP RATE
    }
}