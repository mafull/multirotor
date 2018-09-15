#ifndef __GYROSCOPE_HPP
#define __GYROSCOPE_HPP

using Gyroscope_Data_Element_t = float;

using Gyroscope_Data_t =
    struct Gyroscope_Data_t
    {
        Gyroscope_Data_Element_t x;
        Gyroscope_Data_Element_t y;
        Gyroscope_Data_Element_t z;
    };


class Gyroscope
{
public:
    Gyroscope();
    ~Gyroscope();
    
    virtual void initialise() = 0;
    virtual void update() = 0;

    const Gyroscope_Data_t& getData() const
    {
        return _data;
    }

protected:
    Gyroscope_Data_t _data;
};

#endif  // __GYROSCOPE_HPP
