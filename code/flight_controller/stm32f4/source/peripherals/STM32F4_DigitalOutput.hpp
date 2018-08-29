#ifndef __STM32F4_DIGITAL_OUTPUT_HPP
#define __STM32F4_DIGITAL_OUTPUT_HPP

#include "peripherals/DigitalOutput.hpp"

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
    bool _configured;
    GPIO_TypeDef *_port;
    GPIO_InitTypeDef _initStruct;
};

#endif  // __STM32F4_DIGITAL_OUTPUT_HPP
