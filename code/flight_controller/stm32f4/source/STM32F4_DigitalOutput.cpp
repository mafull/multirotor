#include "STM32F4_DigitalOutput.hpp"

#define ENABLE_PORT_CLOCK(port)  __HAL_RCC_##port_CLK_ENABLE()

static uint8_t getSetBitsCount(uint16_t input);

STM32F4_DigitalOutput::STM32F4_DigitalOutput() :
    m_configured(false)
{
    // Do nothing
}

void STM32F4_DigitalOutput::setConfiguration(GPIO_TypeDef *port, GPIO_InitTypeDef& init);
{
    // Ensure it is not already initialised
    ASSERT(!m_initialised);

    // Ensure that only one pin is being configured
    ASSERT(getSetBitsCount(init.Pin) == 1u);

    // Ensure that it is being configured as an output
    ASSERT(
        (init.Mode == GPIO_MODE_OUTPUT_OD) ||
        (init.Mode == GPIO_MODE_OUTPUT_PP));

    // Store the configuration
    m_port = port;
    m_initStruct = init;

    m_configured = true;
}

void STM32F4_DigitalOutput::initialise()
{
    // Ensure it is configured but not already initialised
    ASSERT(m_configured && !m_initialised);

    // Enable the relevant port clock
    ENABLE_PORT_CLOCK(m_port);

    // Attempt to initialise the GPIO peripheral
    m_initialised = (HAL_GPIO_Init(m_port, &m_initStruct) == HAL_OK);

    // Ensure that the initialsation was successful
    ASSERT(m_initialised);
}

DigitalOutput_State_t STM32F4_DigitalOutput::getState()
{
    ASSERT(m_initialised);

    return (HAL_GPIO_ReadPin(m_port, m_initStruct.Pin) == GPIO_PIN_SET) ?
        DigitalOutput_State_High : DigitalOutput_State_Low;
}

void STM32F4_DigitalOutput::setState(const DigitalOutput_State_t state)
{
    ASSERT(m_initialised);
    ASSERT(state != DigitalOutput_State_NotConfigured);

    HAL_GPIO_WritePin(
        m_port,
        m_initStruct.Pin,
        (state == DigitalOutput_State_High) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static uint8_t getSetBitsCount(uint16_t input)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < 16; i++)
    {
        if (input & 0x01) {
            count++;
        }
        input >>= 1;
    }
    return count;
}