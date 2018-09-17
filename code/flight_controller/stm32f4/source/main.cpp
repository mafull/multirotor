/**
 ******************************************************************************
 * @file    main.cpp
 * @author  Max Fuller
 * @version V1.0
 * @date    04/08/2018
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f4xx.h"

#include "stm32f4_init.hpp"

#include "devices/HMC5883L.hpp"
#include "devices/MPU6050.hpp"

#include "Assert.hpp"
#include "FlightController.hpp"

void assert_callback(const char *file, int line);

/**
 * The main entry point of the application
 */
UART *uart;
Logger *logger;

int main()
{
    // Initialise the assert handler
    assert_init(&assert_callback);

    // PERIPHERALS
    PeripheralManager peripheralManager;
    stm32f4_initialisePeripheralManager(peripheralManager);
    
    uart = &peripheralManager.uart(0);

    // 
    MPU6050 mpu6050(peripheralManager.i2c(0));
    HMC5883L hmc5883l(peripheralManager.i2c(0));
    
    // 
    Accelerometer& accelerometer = mpu6050.accelerometer;
    Gyroscope& gyroscope = mpu6050.gyroscope;
    Magnetometer& magnetometer = hmc5883l;

    // Create an instance of FlightController
    FlightController flightController(peripheralManager,
                                      accelerometer,
                                      gyroscope,
                                      magnetometer);

    logger = &flightController._logger;
    // Attempt to initialise the instance
    //ASSERT(stm32f4_initialiseFlightController(flightController));

    // Run the flight controller
    flightController.run();

    return 0;
}

/**
 * The callback function that is called when an assert fails
 * @param[in] file The filename where the assert failed
 * @param[in] line The line number where the assert failed
 */
void assert_callback(const char *file, int line) // @todo: Do this
{

    // Do something here
    // flightController.peripherals.uart(0).write("#");
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_1, GPIO_PIN_SET); // @todo: #define
    //logger->Suspend();
    uart->write("ASSERT: " + std::string(file) + ":" + std::to_string(line));
    for (;;) { }
}


#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif
