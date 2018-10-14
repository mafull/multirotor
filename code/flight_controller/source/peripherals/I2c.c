// --- Public header ---
#include "peripherals/I2c.h"

// --- Private header ---
#define I2C_PRIVATE
    #include "peripherals/I2c_private.h"
#undef I2C_PRIVATE


#define ENSURE(x) // @todo: Implement externally


/******************************************************************************
  Public Function Implementations
 ******************************************************************************/

bool I2c_Initialise(I2c_Instance_t instance)
{
    ENSURE(instance < I2c_Instance_MAX);

    I2c_Handle_t *const handle = &I2c_handles[(uint8_t)instance]; // @todo: Make func/macro (global?)

    ENSURE(instance == handle->instance);
    ENSURE(!handle->initialised);

    handle->initialised = (HAL_I2C_Init(&handle->halHandle) == HAL_OK);

    return handle->initialised;
}

bool I2c_ReadMemory(I2c_Instance_t instance,
                    uint16_t deviceAddress,
                    uint16_t memoryAddress,
                    uint8_t *data,
                    uint8_t amount)
{
    ENSURE(instance < I2c_Instance_MAX);

    I2c_Handle_t *const handle = &I2c_handles[(uint8_t)instance];

    ENSURE(handle->initialised);
    
    return (HAL_I2C_Mem_Read(&handle->halHandle,
                             (deviceAddress << 1), // @todo Make func?
                             memoryAddress,
                             1u,
                             data,
                             amount,
                             I2C_TRANSMIT_TIMEOUT) == HAL_OK);
}

bool I2c_WriteMemory(I2c_Instance_t instance,
                     uint16_t deviceAddress,
                     uint16_t memoryAddress,
                     uint8_t *data,
                     uint8_t amount)
{
    ENSURE(instance < I2c_Instance_MAX);

    I2c_Handle_t *const handle = &I2c_handles[(uint8_t)instance];

    ENSURE(handle->initialised);

    return (HAL_I2C_Mem_Write(&handle->halHandle,
                              (deviceAddress << 1), // @todo Make func?
                              memoryAddress,
                              1u,
                              data,
                              amount,
                              I2C_TRANSMIT_TIMEOUT) == HAL_OK);
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/


void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if(hi2c->Instance==I2C1)
    {
        __GPIOB_CLK_ENABLE();

        GPIO_InitStruct.Pin         = GPIO_PIN_6; //I2C1_SCL_PIN;
        GPIO_InitStruct.Mode        = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull        = GPIO_PULLUP;
        GPIO_InitStruct.Speed       = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate   = GPIO_AF4_I2C1;
        HAL_GPIO_Init(GPIOB/*I2C1_SCL_PORT*/, &GPIO_InitStruct);

        GPIO_InitStruct.Pin         = GPIO_PIN_7; //I2C1_SDA_PIN;
        GPIO_InitStruct.Alternate   = GPIO_AF4_I2C1;
        HAL_GPIO_Init(GPIOB/*I2C1_SDA_PORT*/, &GPIO_InitStruct);
            
        __I2C1_CLK_ENABLE();





        // // Create a common DMA initialisation structure
        // DMA_HandleTypeDef dmahandle;
        // dmaHandle.Init.FIFOMode               = DMA_FIFOMODE_DISABLE;
        // dmaHandle.Init.MemDataAlignment       = DMA_MDATAALIGN_BYTE;
        // dmaHandle.Init.MemInc                 = DMA_MINC_ENABLE;
        // dmaHandle.Init.Mode                   = DMA_NORMAL;
        // dmaHandle.Init.PeriphDataAlignment    = DMA_PDATAALIGN_BYTE;
        // dmaHandle.Init.PeriphInc              = DMA_PINC_ENABLE;
        // dmaHandle.Init.Priority               = DMA_PRIORITY_HIGH;

        // // Set the channel and direction for I2C1 RX and update the configuration
        // dmaHandle.Init.Direction              = DMA_PERIPH_TO_MEMORY;
        // dmaHandle.Init.Channel                = DMA_CHANNEL_1;
        // // @todo: Handle this like the I2C/UART modules
        // dmaHandle.Instance                    = DMA1_Stream0;
        // HAL_DMA_INIT(&dmaHandle);
        // __HAL_LINKDMA(hi2c, hdmarx, dmaInit);

        // // Set the channel and direction for I2C1 TX and update the configuration
        // dmaHandle.Init.Direction              = DMA_MEMORY_TO_PERIPH;
        // dmaHandle.Init.Channel                = DMA_CHANNEL_1;
        // // @todo: Handle this like the I2C/UART modules
        // dmaHandle.Instance                    = DMA1_Stream6;
        // HAL_DMA_INIT(&dmaHandle);
        // __HAL_LINKDMA(hi2c, hdmatx, dmaInit);
    }
}