#ifndef __STM32F4_DIGITAL_OUTPUT_HPP
#define __STM32F4_DIGITAL_OUTPUT_HPP

#include "DigitalOutput.hpp"

#include "stm32f4xx.h"

class STM32F4_DigitalOutput : public DigitalOutput
{
public:
    STM32F4_DigitalOutput();

    void setConfiguration(GPIO_TypeDef *port, GPIO_InitTypeDef& init);

    void initialise();
    const DigitalOutput_State_t getState() const;
    void setState(const DigitalOutput_State_t state) const;
    
protected:

private:
    bool m_configured;
    GPIO_TypeDef *m_port;
    GPIO_InitTypeDef m_initStruct;
};

#endif  // __STM32F4_DIGITAL_OUTPUT_HPP
