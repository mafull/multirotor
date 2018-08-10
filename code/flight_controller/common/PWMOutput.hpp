#ifndef __PWM_OUTPUT_HPP
#define __PWM_OUTPUT_HPP

typedef PWMOutput_PulseWidth_t uint16_t;

class PWMOutput
{
public:
    virtual void setPulseWidthUs(PWMOutput_PulseWidth_t pulseWidthUs) = 0;
    virtual PWMOutput_PulseWidth_t getPulseWidthUs() = 0;

private:
    m_initialised
};

#endif  // __PWM_OUTPUT_HPP
