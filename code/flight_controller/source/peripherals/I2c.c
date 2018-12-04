// --- Public header ---
#include "peripherals/I2c.h"

// --- Private header ---
#define I2C_PRIVATE
    #include "peripherals/I2c_private.h"
#undef I2C_PRIVATE

// --- Project includes ---
#include "macros.h"
#include "peripherals/Gpio.h"


/******************************************************************************
  Private Data
 ******************************************************************************/

bool I2c_isInitialised = false;

I2C_HandleTypeDef I2c_handles[I2c_Instance_MAX];


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool I2c_Initialise(void)
{
    ENSURE(!I2c_isInitialised);


    ENSURE(Gpio_IsInitialised()); // @todo: Maybe make this the ret value, don't assert?

    bool success = true;
    for (uint8_t i = 0; success && (i < I2c_Instance_MAX); i++)
    {
        const I2c_ConfigData_t *const conf = &I2c_configData[i];
        I2C_HandleTypeDef *const handle = &I2c_handles[i];

        I2c_EnableI2cClock(conf->halInstance);

        handle->Instance = conf->halInstance;
        handle->Init = conf->initStruct;
        success = (HAL_I2C_Init(handle) == HAL_OK);
    }

    I2c_isInitialised = success;
    return I2c_isInitialised;
}


bool I2c_IsInitialised(void)
{
    return I2c_isInitialised;
}


bool I2c_ReadMemory(I2c_Instance_t instance,
                    uint16_t deviceAddress,
                    uint16_t memoryAddress,
                    uint8_t *data,
                    uint8_t amount,
                    I2c_TransferMethod_t transferMethod)
{
    ENSURE(instance < I2c_Instance_MAX);
    ENSURE(I2c_isInitialised);

    // @todo: Check DMA is initialised and instance linked if using dma

    I2C_HandleTypeDef *const handle = &I2c_handles[instance];

    // Attempt to read from the memory location via the requested method
    bool success = false;
    switch(transferMethod)
    {
    case I2c_Blocking:
        success = HAL_I2C_Mem_Read(handle,
                                   (deviceAddress << 1), // @todo Make func/macro?
                                   memoryAddress,
                                   1u,
                                   data,
                                   amount,
                                   I2C_TRANSMIT_TIMEOUT) == HAL_OK;
        break;
    case I2c_Dma:
        success = HAL_I2C_Mem_Read_DMA(handle,
                                       (deviceAddress << 1), // @todo Make func/macro?
                                       memoryAddress,
                                       1u,
                                       data,
                                       amount) == HAL_OK;
        break;
    default:
        UNREACHABLE();
    }

    return success;
}


bool I2c_WriteMemory(I2c_Instance_t instance,
                     uint16_t deviceAddress,
                     uint16_t memoryAddress,
                     uint8_t *data,
                     uint8_t amount,
                     I2c_TransferMethod_t transferMethod)
{
    ENSURE(instance < I2c_Instance_MAX);
    ENSURE(I2c_isInitialised);

    // @todo: Check DMA is initialised and instance linked if using dma

    I2C_HandleTypeDef *const handle = &I2c_handles[instance];

    // Attempt to write to the memory location via the requested method
    bool success = false;
    switch(transferMethod)
    {
    case I2c_Blocking:
        success = HAL_I2C_Mem_Write(handle,
                                    (deviceAddress << 1), // @todo Make func/macro?
                                    memoryAddress,
                                    1u,
                                    data,
                                    amount,
                                    I2C_TRANSMIT_TIMEOUT) == HAL_OK;
        break;
    case I2c_Dma:
        success = HAL_I2C_Mem_Write_DMA(handle,
                                        (deviceAddress << 1), // @todo Make func/macro?
                                        memoryAddress,
                                        1u,
                                        data,
                                        amount) == HAL_OK;
        break;
    default:
        UNREACHABLE();
    }

    return success;
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/

void I2c_EnableI2cClock(I2C_TypeDef *instance)
{
    ENSURE(instance);

    if      (instance == I2C1)  __HAL_RCC_I2C1_CLK_ENABLE();
    else if (instance == I2C2)  __HAL_RCC_I2C2_CLK_ENABLE();
    else if (instance == I2C3)  __HAL_RCC_I2C3_CLK_ENABLE();
    else                        UNREACHABLE();
}
