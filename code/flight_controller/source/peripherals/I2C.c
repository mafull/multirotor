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

    I2c_Handle_t *const handle = &I2c_handles[(uint8_t)instance];

    ENSURE(instance == handle->instance);
    ENSURE(!handle->initialised);

    handle->initialised = (HAL_I2C_Init(&handle->halHandle) == HAL_OK);

    return handle->initialised;
}


/******************************************************************************
  Private Function Implementations
 ******************************************************************************/
