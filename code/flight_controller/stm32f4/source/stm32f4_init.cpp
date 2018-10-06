#include "stm32f4_init.hpp"

#include "stm32f4_config.hpp"

//
// #include "imu/HMC5883L.hpp"
// #include "imu/MPU6050.hpp"
// Peripherals
#include "peripherals/STM32F4_DigitalOutput.hpp"
#include "peripherals/STM32F4_I2C.hpp"
#include "peripherals/STM32F4_UART.hpp"

static STM32F4_I2C i2c1;
static STM32F4_UART uart1;
static STM32F4_UART uart2;

// static HMC5883L hmc5883l;
// static MPU6050 mpu6050;

void SystemClock_Config(void)
{
    // @todo: Clean up/comment
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

    __PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 168;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 |
                                  RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

bool stm32f4_initialiseFlightController(FlightController& flightController)
{
    // SystemClock_Config();
    bool okay = true;

    //stm32f4_initialisePeripherals(flightController.peripherals);
    //stm32f4_initialiseIMU(flightController.imu);

    return okay;
}



bool stm32f4_initialisePeripheralManager(PeripheralManager& peripheralManager)
{
    stm32f4_initialisePeripherals(peripheralManager);
}

// Accelerometer& stm32f4_getAccelerometer()
// {
//     return mpu6050.accelerometer;
// }

// Gyroscope& stm32f4_getGyroscope()
// {
//     return mpu6050.gyroscope;
// }

// Magnetometer& stm32f4_getMagnetometer()
// {
//     return hmc5883l;
// }


void stm32f4_initialiseIMU(IMU& imu)
{
    //mpu6050.setConfiguration(x);
    //hmc5883l.setConfiguration(x);

    // imu.setAccelerometer(&mpu6050.accelerometer);
    // imu.setGyroscope(&mpu6050.gyroscope);
    // imu.setMagnetometer(&hmc5883l);
}

void stm32f4_initialisePeripherals(PeripheralManager& peripheralManager)
{
    HAL_Init();
    
    SystemClock_Config();
    
    stm32f4_initialiseDigitalInput();
    stm32f4_initialiseDigitalOutput();
    stm32f4_initialiseI2C();
    stm32f4_initialisePWMInput();
    stm32f4_initialisePWMOutput();
    stm32f4_initialiseUART();

    peripheralManager.addI2C(&i2c1);
    peripheralManager.addUART(&uart1);
    peripheralManager.addUART(&uart2);
}

void stm32f4_initialiseDigitalInput()
{

}

void stm32f4_initialiseDigitalOutput()
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Ports Clock Enable */
    __GPIOD_CLK_ENABLE(); // @todo: #define

    // Configure GPIO pins
    GPIO_InitStruct.Mode    = GPIO_MODE_OUTPUT_PP;
    // GPIO_InitStruct.Pin = GPIO_PIN_1; // @todo: #define
    GPIO_InitStruct.Pin     = GPIO_PIN_1 |
                              GPIO_PIN_12 |
                              GPIO_PIN_13 |
                              GPIO_PIN_14 |
                              GPIO_PIN_15;
    GPIO_InitStruct.Pull    = GPIO_NOPULL;
    GPIO_InitStruct.Speed   = GPIO_SPEED_LOW;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct); // @todo: #define
}

void stm32f4_initialiseI2C()
{
    // Create a common I2C initialisation structure
    I2C_InitTypeDef i2cInit;
    i2cInit.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
    i2cInit.DualAddressMode = I2C_DUALADDRESS_DISABLED;
    i2cInit.DutyCycle       = I2C_DUTYCYCLE_2;
    i2cInit.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    i2cInit.NoStretchMode   = I2C_NOSTRETCH_DISABLED;
    i2cInit.OwnAddress1     = 0;
    i2cInit.OwnAddress2     = 0;
    
    // Set the clock speed for I2C1 and update the configuration
    i2cInit.ClockSpeed = I2C1_CLOCK_SPEED;
    i2c1.setConfiguration(I2C1, i2cInit);

    // Initialise the instance
    i2c1.initialise();



    // Enable DMA1 clock
    __DMA1_CLK_ENABLE();

    // Enable interrupts for DMA1 streams 0 and 6
    HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
    HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
}

void stm32f4_initialisePWMInput()
{

}

void stm32f4_initialisePWMOutput()
{

}

void stm32f4_initialiseUART()
{
    // Create a common UART initialisation structure
    UART_InitTypeDef uartInit;
    uartInit.WordLength     = UART_WORDLENGTH_8B;
    uartInit.StopBits       = UART_STOPBITS_1;
    uartInit.Parity         = UART_PARITY_NONE;
    uartInit.Mode           = UART_MODE_TX_RX;
    uartInit.HwFlowCtl      = UART_HWCONTROL_NONE;
    uartInit.OverSampling   = UART_OVERSAMPLING_16;

    // Set the baud rate for UART1 and update the configuration
    uartInit.BaudRate       = UART1_BAUD_RATE;
    uart1.setConfiguration(USART1, uartInit);

    // Set the baud rate for UART2 and update the configuration
    uartInit.BaudRate       = UART2_BAUD_RATE;
    uart2.setConfiguration(USART2, uartInit);

    // Initialise both instances
    uart1.initialise();
    uart2.initialise();
}

// CALLBACKS
extern "C" {
void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if(hi2c->Instance==I2C1)
    {
        __GPIOB_CLK_ENABLE();

        GPIO_InitStruct.Pin         = I2C1_SCL_PIN;
        GPIO_InitStruct.Mode        = GPIO_MODE_AF_OD;
        GPIO_InitStruct.Pull        = GPIO_PULLUP;
        GPIO_InitStruct.Speed       = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate   = GPIO_AF4_I2C1;
        HAL_GPIO_Init(I2C1_SCL_PORT, &GPIO_InitStruct);

        GPIO_InitStruct.Pin         = I2C1_SDA_PIN;
        GPIO_InitStruct.Alternate   = GPIO_AF4_I2C1;
        HAL_GPIO_Init(I2C1_SDA_PORT, &GPIO_InitStruct);
            
        __I2C1_CLK_ENABLE();





        // Create a common DMA initialisation structure
        DMA_HandleTypeDef dmahandle;
        dmaHandle.Init.FIFOMode               = DMA_FIFOMODE_DISABLE;
        dmaHandle.Init.MemDataAlignment       = DMA_MDATAALIGN_BYTE;
        dmaHandle.Init.MemInc                 = DMA_MINC_ENABLE;
        dmaHandle.Init.Mode                   = DMA_NORMAL;
        dmaHandle.Init.PeriphDataAlignment    = DMA_PDATAALIGN_BYTE;
        dmaHandle.Init.PeriphInc              = DMA_PINC_ENABLE;
        dmaHandle.Init.Priority               = DMA_PRIORITY_HIGH;

        // Set the channel and direction for I2C1 RX and update the configuration
        dmaHandle.Init.Direction              = DMA_PERIPH_TO_MEMORY;
        dmaHandle.Init.Channel                = DMA_CHANNEL_1;
        // @todo: Handle this like the I2C/UART modules
        dmaHandle.Instance                    = DMA1_Stream0;
        HAL_DMA_INIT(&dmaHandle);
        __HAL_LINKDMA(hi2c, hdmarx, dmaInit);

        // Set the channel and direction for I2C1 TX and update the configuration
        dmaHandle.Init.Direction              = DMA_MEMORY_TO_PERIPH;
        dmaHandle.Init.Channel                = DMA_CHANNEL_1;
        // @todo: Handle this like the I2C/UART modules
        dmaHandle.Instance                    = DMA1_Stream6;
        HAL_DMA_INIT(&dmaHandle);
        __HAL_LINKDMA(hi2c, hdmatx, dmaInit);
    }
}

void HAL_MspInit(void)
{
    HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    /* System interrupt init*/
    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if(huart->Instance==USART1)
    {
        __USART1_CLK_ENABLE();
        __GPIOA_CLK_ENABLE(); // @todo: Make this dependent on port
  
        GPIO_InitStruct.Pin         = UART1_RX_PIN;
        GPIO_InitStruct.Mode        = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull        = GPIO_NOPULL;
        GPIO_InitStruct.Speed       = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate   = GPIO_AF7_USART1;
        HAL_GPIO_Init(UART1_RX_PORT, &GPIO_InitStruct);

        GPIO_InitStruct.Pin         = UART1_TX_PIN;
        GPIO_InitStruct.Alternate   = GPIO_AF7_USART1;
        HAL_GPIO_Init(UART1_TX_PORT, &GPIO_InitStruct);

        HAL_NVIC_SetPriority(USART1_IRQn, 1, 1);
        HAL_NVIC_EnableIRQ(USART1_IRQn);

        // @todo: Add to class? Like enabling EXTI for button press
        __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
    }
}

}
