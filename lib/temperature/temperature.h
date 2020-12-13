#ifndef TEMPERATURE_H_
#define TEMPERATURE_H_

#include <SPI.h>
#include <cstdint>

enum class TemperatureSensorStatus {
  ok,
  open_connection,
  short_circuit_ground,
  short_circuit_vcc,
};

class TemperatureSensorReading {
public:
  TemperatureSensorReading(uint32_t);
  TemperatureSensorStatus status();
  bool valid();
  float temperature();
  float temperature_internal();

private:
  int temperature_ : 14;
  int temperature_internal_ : 12;
  TemperatureSensorStatus status_;
  constexpr static float resolution_ = 0.25;
  constexpr static float resolution_internal_ = 0.0625;
};

class TemperatureSensor {
public:
  TemperatureSensor(SPIClass &, int);
  TemperatureSensorReading reading();

private:
  SPIClass &bus_;
  int chip_select_pin_;
  const static SPISettings settings_;
};

#endif // TEMPERATURE_H_
