#ifndef __TEMPERATURE_SENSOR_HPP
#define __TEMPERATURE_SENSOR_HPP

using TemperatureSensor_Data_t =
    struct TemperatureSensor_Data_t
    {
        // @todo: Timestamp
        float temperature;
    };


class TemperatureSensor
{
public:
    virtual void initialise() = 0;
    virtual void update() = 0;

    const TemperatureSensor_Data_t& getData() const
    {
        return _data;
    }

protected:
    TemperatureSensor_Data_t _data;
};

#endif  // __TEMPERATURE_SENSOR_HPP
