#ifndef __IMU_HPP
#define __IMU_HPP

class IMU
{
public:
    IMU();
    ~IMU();
    
    void initialise();
    void getAccelerometerData();
    void getGyroscopeData();
    void getMagnetometerData();

protected:

private:
};

#endif  // __IMU_HPP
