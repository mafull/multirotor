#ifndef __DIGITAL_OUTPUT_HPP
#define __DIGITAL_OUTPUT_HPP

#include "Peripheral.hpp"

typedef enum DigitalOutput_State_t
{
    DigitalOutput_State_NotConfigured = 0,

    DigitalOutput_State_High,
    DigitalOutput_State_Low
} DigitalOutput_State_t;

class DigitalOutput : public Peripheral
{
public:
    virtual const DigitalOutput_State_t getState() const = 0;
    virtual void setState(const DigitalOutput_State_t state) = 0;

    const bool isHigh() const
    {
        return (getState() == DigitalOutput_State_High);
    }

    void setHigh() const
    {
        setState(DigitalOutput_State_High);
    }

    void setLow() const
    {
        setState(DigitalOutput_State_Low);
    }
    
protected:
    DigitalOutput() :
        m_type(Peripheral_Type_DigitalOutput) {}
};

#endif  // __DIGITAL_OUTPUT_HPP
