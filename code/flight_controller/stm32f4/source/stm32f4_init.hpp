#include "FlightController.hpp"

bool stm32f4_initialiseFlightController(FlightController& flightController);
bool stm32f4_initialisePeripheralManager(PeripheralManager& peripheralManager);

void stm32f4_initialiseIMU(IMU& imu);
void stm32f4_initialisePeripherals(PeripheralManager& peripheralManager);

void stm32f4_initialiseDigitalInput();
void stm32f4_initialiseDigitalOutput();
void stm32f4_initialiseI2C();
void stm32f4_initialisePWMInput();
void stm32f4_initialisePWMOutput();
void stm32f4_initialiseUART();
