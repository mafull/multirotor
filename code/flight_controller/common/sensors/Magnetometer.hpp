#ifndef __MAGNETOMETER_HPP
#define __MAGNETOMETER_HPP

using Magnetometer_Data_Element_t = float;

using Magnetometer_Data_t =
    struct Magnetometer_Data_t
    {
        // @todo: Timestamp
        Magnetometer_Data_Element_t x;
        Magnetometer_Data_Element_t y;
        Magnetometer_Data_Element_t z;
    };


class Magnetometer
{
public:
    virtual void initialise() = 0;
    virtual void update() = 0;

    const Magnetometer_Data_t& getData() const
    {
        return _data;
    }

protected:
    Magnetometer_Data_t _data;
};

#endif  // __MAGNETOMETER_HPP
