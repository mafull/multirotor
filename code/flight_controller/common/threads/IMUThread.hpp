#ifndef __IMU_THREAD_HPP
#define __IMU_THREAD_HPP

#include "imu/IMU.hpp"

#include "thread.hpp"

class IMUThread : public cpp_freertos::Thread
{
public:
    IMUThread() :
        Thread("IMU Thread", 1024, 1) {}
    ~IMUThread();

    void setIMU(IMU *imu)
    {
        ASSERT(imu);
        _imu = imu;
    }

    void Run();

protected:

private:
    IMU *_imu;
};

#endif  // __IMU_THREAD_HPP
