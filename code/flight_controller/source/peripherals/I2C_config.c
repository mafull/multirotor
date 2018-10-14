// --- Private header ---
#define I2C_PRIVATE
    #include "peripherals/I2c_private.h"
#undef I2C_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

I2c_Handle_t I2c_handles[] = 
    {
        {
            .instance = I2c1,

            .halHandle =
                {
                    .Init = 
                        {
                            .AddressingMode  = I2C_ADDRESSINGMODE_7BIT,
                            .ClockSpeed      = 400000u,
                            .DualAddressMode = I2C_DUALADDRESS_DISABLED,
                            .DutyCycle       = I2C_DUTYCYCLE_2,
                            .GeneralCallMode = I2C_GENERALCALL_DISABLED,
                            .NoStretchMode   = I2C_NOSTRETCH_DISABLED,
                            .OwnAddress1     = 0u,
                            .OwnAddress2     = 0u
                        },
                    .Instance = I2C1
                }
        }
    };