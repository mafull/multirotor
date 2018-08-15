#include "FlightController.hpp"

#define Peripherals int

bool stm32f4_initialiseFlightController(FlightController& flightController);
void stm32f4_initialisePeripherals(const Peripherals& peripherals);

void stm32f4_initialiseDigitalInput(const Peripherals& peripherals);
void stm32f4_initialiseDigitalOutput(const Peripherals& peripherals);
void stm32f4_initialiseI2C(const Peripherals& peripherals);
void stm32f4_initialisePWMInput(const Peripherals& peripherals);
void stm32f4_initialisePWMOutput(const Peripherals& peripherals);
void stm32f4_initialiseUART(const Peripherals& peripherals);
