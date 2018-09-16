#include "STM32F4_I2C.hpp"

STM32F4_I2C::STM32F4_I2C() :
    _configured(false)
{
    // Do nothing
}

void STM32F4_I2C::setConfiguration(I2C_TypeDef *instance, I2C_InitTypeDef& init)
{
    ASSERT(instance);
    
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

void STM32F4_I2C::writeMemory(
    I2C_Address_t deviceAddress,
    I2C_Address_t memoryAddress,
    uint8_t *data,
    uint8_t amount)
{
    HAL_StatusTypeDef result = HAL_I2C_Mem_Write(&_handle,
                                                 (deviceAddress << 1),
                                                 memoryAddress,
                                                 1,
                                                 data,
                                                 amount,
                                                 100);
    // ASSERT(result == HAL_OK); // @todo: Handle a failed write
}

void STM32F4_I2C::readMemory(
    I2C_Address_t deviceAddress,
    I2C_Address_t memoryAddress,
    uint8_t *data,
    uint8_t amount)
{
    HAL_StatusTypeDef result = HAL_I2C_Mem_Read(&_handle,
                                                (deviceAddress << 1),
                                                memoryAddress,
                                                1,
                                                data,
                                                amount,
                                                100);
    // ASSERT(result == HAL_OK); // @todo: Handle a failed read
}
