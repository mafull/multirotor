#include "IMU.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

const double pi = 3.14159265358979323846;
const IMU_Data_Element_t rad2degMultiplier = 180.0 / pi;
#define RAD2DEG(x)      (x) * rad2degMultiplier

IMU::IMU() :
    _configured(false),
    _initialised(false),
    // Peripherals
    _accelerometer(nullptr),
    _gyroscope(nullptr),
    _magnetometer(nullptr)
{

}

IMU::~IMU()
{

}

void IMU::setConfiguration(I2C *i2c)
{
    ASSERT(i2c);

    // Ensure it is not already initialised
    ASSERT(!_initialised);

    // Ensure the required peripherals have been added
    ASSERT(_accelerometer && _gyroscope && _magnetometer);

    // Pass the I2C handle to the peripherals
    _accelerometer->setI2C(i2c);
    _gyroscope->setI2C(i2c);
    _magnetometer->setI2C(i2c);

    _configured = true;
}

void IMU::initialise()
{
    // Ensure it is configured but not already initialised
    ASSERT(_configured && !_initialised);

    // Initialise the peripherals
    _accelerometer->initialise();
    _gyroscope->initialise();
    //_magnetometer->initialise();

    _initialised = true;
}

void IMU::update()
{
    _accelerometer->update();
    _gyroscope->update();
    //_magnetometer->update();




    // GET SENSOR DATA
    const Accelerometer_Data_t& aData = _accelerometer->getData();
    const Gyroscope_Data_t& gData = _gyroscope->getData();
    // const Magnetometer_Data_t& mData = _magnetometer->getData();
    

    // CALCULATE DT
    IMU_Data_Element_t dt = 0.1f;

    // GYRO-BASED ATTITUDE
    _data.gyroscope.roll +=  gData.x * dt;
    _data.gyroscope.pitch += gData.y * dt;
    _data.gyroscope.yaw +=   gData.z * dt;


    // ACCELEROMETER-BASED ATTITUDE
    IMU_Data_Element_t ax2 = pow(aData.x, 2);
    IMU_Data_Element_t ay2 = pow(aData.y, 2);
    IMU_Data_Element_t az2 = pow(aData.z, 2);
    _data.accelerometer.roll = -RAD2DEG(atan2(aData.y, sqrt(ax2 + az2)));
    _data.accelerometer.pitch = RAD2DEG(atan2(aData.x, sqrt(ay2 + az2)));
    _data.accelerometer.yaw =  -RAD2DEG(atan2(aData.x, sqrt(ax2 + az2)));

    // TILT-COMPENSATED MAGNETOMETER-BASED HEADING
    // _data.magnetometer.heading


    // COMBINE EVERYTING (COMPLIMENTARY FILTER FOR NOW)
    // _data.roll = 
    // _data.pitch = 
    // _data.yaw = 



    // COMPENSATE FOR GYRO DRIFT
    _data.gyroscope.roll = _data.roll;
    _data.gyroscope.pitch = _data.pitch;
    _data.gyroscope.yaw = _data.yaw;

    // _data.timestamp = TIME
}
