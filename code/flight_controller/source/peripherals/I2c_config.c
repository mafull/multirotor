// --- Private header ---
#define I2C_PRIVATE
    #include "peripherals/I2c_private.h"
#undef I2C_PRIVATE


/******************************************************************************
  Private Data
 ******************************************************************************/

const I2c_ConfigData_t I2c_configData[I2c_Instance_MAX] = 
    {
        /*
          |Inst.| I2C Init Struct
          |     | | Clock Speed
          |     | |       | Duty Cycle     | Own Address 1
          |     | |       |                |  | Own Address 2
          |     | |       |                |  |  | General Call Mode       | Nostretch Mode
        */
        { I2C1, { 400000, I2C_DUTYCYCLE_2, 0, 0, I2C_GENERALCALL_DISABLED, I2C_NOSTRETCH_DISABLED } }, // I2c1
    };
