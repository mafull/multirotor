#include "stm32f4_init.hpp"

#include "stm32f4_config.hpp"

//
#include "imu/HMC5883L.hpp"
#include "imu/MPU6050.hpp"
// Peripherals
#include "peripherals/STM32F4_DigitalOutput.hpp"
#include "peripherals/STM32F4_I2C.hpp"
#include "peripherals/STM32F4_UART.hpp"

static STM32F4_I2C i2c1;
static STM32F4_UART uart1;
static STM32F4_UART uart2;

static HMC5883L hmc5883l;
static MPU6050 mpu6050;

void SystemClock_Config(void)
{
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

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
        |RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

    //while(HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000000)) {};
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
}

bool stm32f4_initialiseFlightController(FlightController& flightController)
{
    SystemClock_Config();
    bool ok = true;

    stm32f4_initialisePeripherals(flightController.peripherals);
    stm32f4_initialiseIMU(flightController.imu);

    return ok;
}

void stm32f4_initialiseIMU(IMU& imu)
{
    imu.setAccelerometer(&mpu6050.accelerometer);
    imu.setGyroscope(&mpu6050.gyroscope);
    imu.setMagnetometer(&hmc5883l);
}

void stm32f4_initialisePeripherals(PeripheralManager& peripheralManager)
{
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

}

void stm32f4_initialiseI2C()
{
    // Create a common initialisation structure
    I2C_InitTypeDef init;
    init.DutyCycle = I2C_DUTYCYCLE_2;
    init.OwnAddress1 = 0;
    init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
    init.OwnAddress2 = 0;
    init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    init.NoStretchMode = I2C_NOSTRETCH_DISABLED;

    // Set the clock speed for I2C1 and update the configuration
    init.ClockSpeed = I2C1_CLOCK_SPEED;
    i2c1.setConfiguration(I2C1, init);

    // Initialise the instance
    i2c1.initialise();
}

void stm32f4_initialisePWMInput()
{

}

void stm32f4_initialisePWMOutput()
{

}

void stm32f4_initialiseUART()
{
    // Create a common initialisation structure
    UART_InitTypeDef init;
    init.WordLength = UART_WORDLENGTH_8B;
    init.StopBits= UART_STOPBITS_1;
    init.Parity = UART_PARITY_NONE;
    init.Mode = UART_MODE_TX_RX;
    init.HwFlowCtl = UART_HWCONTROL_NONE;
    init.OverSampling = UART_OVERSAMPLING_16;

    // Set the baud rate for UART1 and update the configuration
    init.BaudRate = UART1_BAUD_RATE;
    uart1.setConfiguration(USART1, init);

    // Set the baud rate for UART2 and update the configuration
    init.BaudRate = UART2_BAUD_RATE;
    uart2.setConfiguration(USART2, init);

    // Initialise both instances
    uart1.initialise();
    uart2.initialise();
}

// CALLBACKS

//extern "C" {
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    if(huart->Instance==USART1)
    {
        __USART1_CLK_ENABLE();
  
        GPIO_InitStruct.Pin = UART1_RX_PIN;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(UART1_RX_PORT, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = UART1_TX_PIN;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(UART1_TX_PORT, &GPIO_InitStruct);

        HAL_NVIC_SetPriority(USART1_IRQn, 1, 1);
        HAL_NVIC_EnableIRQ(USART1_IRQn);

        // @todo: Add to class? Like enabling EXTI for button press
        __HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
    }
}
//}
