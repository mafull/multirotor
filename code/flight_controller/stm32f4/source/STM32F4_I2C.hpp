#ifndef __STM32F4_I2C_HPP
#define __STM32F4_I2C_HPP

#include "I2C.hpp"

#include "stm32f4xx.h"

class STM32F4_I2C : public I2C
{
public:
    STM32F4_I2C();

    void setConfiguration(I2C_TypeDef *instance, I2C_InitTypeDef& init);
    
    void initialise();

    void writeMemory(
        I2C_Address_t deviceAddress,
        I2C_Address_t memoryAddress,
        uint8_t *data,
        uint8_t amount);
    void readMemory(
        I2C_Address_t deviceAddress,
        I2C_Address_t memoryAddress,
        uint8_t *data,
        uint8_t amount);

protected:

private:
    bool _configured;
    I2C_HandleTypeDef _handle;
};

#endif  // __STM32F4_I2C_HPP
