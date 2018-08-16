#include "STM32F4_I2C.hpp"

STM32F4_I2C::STM32F4_I2C() :
    _configured(false)
{
    // Do nothing
}

void STM32F4_I2C::setConfiguration(I2C_TypeDef *instance, I2C_InitTypeDef& init)
{
    // Ensure it is not already initialised
    ASSERT(!_initialised);

    // Store the configuration in the handle
    _handle.Instance = instance;
    _handle.Init = init;

    _configured = true;
}

void STM32F4_I2C::initialise()
{
    // Ensure it is configured but not already initialised
    ASSERT(_configured && !_initialised);

    // Attempt to initialise the I2C peripheral
    _initialised = (HAL_I2C_Init(&_handle) == HAL_OK);

    // Ensure that the initialsation was successful
    ASSERT(_initialised);
}
