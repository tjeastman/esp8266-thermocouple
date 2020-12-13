#include "temperature.h"
#include <SPI.h>
#include <cstdint>
#include <utility>

TemperatureSensorReading::TemperatureSensorReading(uint32_t value)
  : temperature_(value >> 18), temperature_internal_((value >> 4) & 0x0fff) {
  if (value & 0x1) {
    status_ = TemperatureSensorStatus::open_connection;
  } else if (value & 0x2) {
    status_ = TemperatureSensorStatus::short_circuit_ground;
  } else if (value & 0x4) {
    status_ = TemperatureSensorStatus::short_circuit_vcc;
  } else {
    status_ = TemperatureSensorStatus::ok;
  }
}

bool TemperatureSensorReading::valid() {
  return status_ == TemperatureSensorStatus::ok;
}

TemperatureSensorStatus TemperatureSensorReading::status() { return status_; }

float TemperatureSensorReading::temperature() {
  return temperature_ * resolution_;
}

float TemperatureSensorReading::temperature_internal() {
  return temperature_internal_ * resolution_internal_;
}

const SPISettings TemperatureSensor::settings_{5000000, MSBFIRST, SPI_MODE0};

TemperatureSensor::TemperatureSensor(SPIClass &bus, int pin)
    : bus_(bus), chip_select_pin_(pin) {
  pinMode(chip_select_pin_, OUTPUT);
}

TemperatureSensorReading TemperatureSensor::reading() {
  uint32_t value = 0;

  bus_.beginTransaction(settings_);
  digitalWrite(chip_select_pin_, LOW);
  value |= bus_.transfer(0) << 24;
  value |= bus_.transfer(0) << 16;
  value |= bus_.transfer(0) << 8;
  value |= bus_.transfer(0);
  digitalWrite(chip_select_pin_, HIGH);
  bus_.endTransaction();

  return TemperatureSensorReading(value);
}
