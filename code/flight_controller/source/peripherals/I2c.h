#ifndef __I2C_H
#define __I2C_H


// --- Standard includes ---
#include <stdbool.h>
#include <stdint.h>


/******************************************************************************
  Public Data Types
 ******************************************************************************/

/**
 *
 */
typedef enum I2c_Instance_e
{
    I2c1 = 0u,

    I2c_Instance_MAX
} I2c_Instance_t;

/**
 *
 */
typedef enum I2c_TransferMethod_e
{
    I2c_Blocking,
    I2c_Dma
} I2c_TransferMethod_t;


/******************************************************************************
  Public Function Prototypes
 ******************************************************************************/

/**
 *
 */
bool I2c_Initialise(void);

/**
 *
 */
bool I2c_IsInitialised(void);

/**
 *
 */
bool I2c_ReadMemory(I2c_Instance_t instance,
                    uint16_t deviceAddress,
                    uint16_t memoryAddress,
                    uint8_t *data,
                    uint8_t amount,
                    bool dma);

/**
 *
 */
bool I2c_WriteMemory(I2c_Instance_t instance,
                     uint16_t deviceAddress,
                     uint16_t memoryAddress,
                     uint8_t *data,
                     uint8_t amount,
                     bool dma);


#endif // __I2C_H
