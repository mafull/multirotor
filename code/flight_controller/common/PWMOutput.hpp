#ifndef __PWM_OUTPUT_HPP
#define __PWM_OUTPUT_HPP

#include "Peripheral.hpp"

#include <cstdint>

typedef uint16_t PWMOutput_PulseWidth_t;

class PWMOutput : public Peripheral
{
public:
    virtual void setPulseWidthUs(PWMOutput_PulseWidth_t pulseWidthUs) = 0;
    virtual PWMOutput_PulseWidth_t getPulseWidthUs() = 0;

private:

};

#endif  // __PWM_OUTPUT_HPP
