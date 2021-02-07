#include <Arduino.h>
#include <temperature.h>

TemperatureSensor sensor = TemperatureSensor(SPI, D8);

void setup() {
  Serial.begin(115200);
  SPI.begin();

  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);
}

void loop() {
  auto reading = sensor.reading();
  auto status = reading.status();
  if (status == TemperatureSensorStatus::open_connection) {
    Serial.println("status: open_connection");
  } else if (status == TemperatureSensorStatus::short_circuit_ground) {
    Serial.println("status: short_circuit_ground");
  } else if (status == TemperatureSensorStatus::short_circuit_vcc) {
    Serial.println("status: short_circuit_vcc");
  } else {
    Serial.print("temperature (deg C): ");
    Serial.print(reading.temperature());
    Serial.print(" ");
    Serial.println(reading.temperature_internal());
  }

  delay(2000);
}
