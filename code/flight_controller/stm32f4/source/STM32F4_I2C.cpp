#include "STM32F4_I2C.hpp"

STM32F4_I2C::STM32F4_I2C() :
    m_configured(false)
{
    // Do nothing
}

void STM32F4_I2C::setConfiguration(I2C_TypeDef *instance, I2C_InitTypeDef& init)
{
    // Ensure it is not already initialised
    ASSERT(!m_initialised);

    // Store the configuration in the handle
    m_handle.Instance = instance;
    m_handle.Init = init;

    m_configured = true;
}

void STM32F4_I2C::initialise()
{
    // Ensure it is configured but not already initialised
    ASSERT(m_configured && !m_initialised);

    // Attempt to initialise the I2C peripheral
    m_initialised = (HAL_I2C_Init(&m_handle) == HAL_OK);

    // Ensure that the initialsation was successful
    ASSERT(m_initialised);
}
