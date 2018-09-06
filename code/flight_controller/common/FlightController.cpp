#include "FlightController.hpp"

#include "Assert.hpp"


bool FlightController::_isInstantiated = false;

FlightController::FlightController()
{
    // Ensure we only have a single instance of this class
    ASSERT(!_isInstantiated);
    _isInstantiated = true;
}

FlightController::~FlightController()
{
    _isInstantiated = false;
}

void FlightController::run()
{
    log("FlightController::run()");

    // SET UP THREADS

    log("> Threads initialised");

    /* START THREADS:
        LOGGING
        COMMS
        CONTROL */
    controlThread.setUART(&peripherals.uart(0));
    controlThread.Start();
    cpp_freertos::Thread::StartScheduler();

    for (;;) {}

    // THIS IS THE MAIN THREAD, CHECK STATUS OF OTHER THREADS (MSG QUEUE?)

    // RETURN ONCE E.G. OTHER THREADS ARE FINISHED
}

void FlightController::log(const std::string& msg)
{
    // SEND MESSAGE TO LOGGING THREAD

    // LOGGING THREAD WILL THEN LOG THE MESSAGE
    peripherals.uart(0).write(msg + "\n");
}

/* CONTROL LOOP:
    PROCESS INPUTS
        MESSAGE QUEUE
        CONTROL INPUTS
        SENSOR READINGS

    GENERATE OUTPUTS
        UPDATE PIDS
        MIX MOTOR OUTPUTS

    OUTPUT
        LOGGING
        INDICATION LEDS
        UPDATE PWM OUTPUTS
*/

/* COMMS LOOP:
    PROCESS INCOMING UART DATA
    SEND PENDING OUTGOING DATA FROM MSG QUEUE
*/

void FlightController::controlThreadTop()
{
    log("FlightController::controlThreadTop()");

    // Initialise the IMU
    imu.setConfiguration(&peripherals.i2c(0));
    imu.initialise();

    // SET PWM OUTPUTS TO TURN MOTORS OFF
    // LOAD DATA FROM EEPROM

    log("> Control loop ready to start");

    const IMU_Data_t& imuData = imu.getData();

    while (1)
    {
        /*
        PROCESS INPUTS
            MESSAGE QUEUE
            CONTROL INPUTS
            SENSOR READINGS
        */

        imu.update();

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

    log("> Control loop finished");


    log("> Control thread finished");
}