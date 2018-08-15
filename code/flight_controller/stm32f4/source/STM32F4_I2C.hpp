#ifndef __STM32F4_I2C_HPP
#define __STM32F4_I2C_HPP

class STM32F4_I2C
{
public:
    STM32F4_I2C();

    void setConfiguration(I2C_TypeDef *instance, I2C_InitTypeDef& init);
    
    void initialise();

protected:

private:
    bool m_configured;
    I2C_HandleTypeDef m_handle;
};

#endif  // __STM32F4_I2C_HPP
