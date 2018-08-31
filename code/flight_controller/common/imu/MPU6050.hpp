#ifndef __MPU6050_HPP
#define __MPU6050_HPP

#include "imu/Accelerometer.hpp"
#include "imu/Gyroscope.hpp"

class MPU6050
{




    class MPU6050_Accelerometer : public Accelerometer
    {
    public:
        MPU6050_Accelerometer(MPU6050& parent) :
            _parent(parent)
        {

        }

        void initialise()
        {

        }

        void something()
        {
            _parent.doSomething();
        }

    protected:

    private:
        MPU6050& _parent;
    };






public:
    MPU6050() :
        accelerometer(*this)
    {

    }

    ~MPU6050();

    void doSomething();

    MPU6050_Accelerometer accelerometer;
    
protected:

private:

};

#endif  // __MPU6050_HPP
