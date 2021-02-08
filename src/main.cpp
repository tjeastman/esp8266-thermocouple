#include "secrets.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <temperature.h>

TemperatureSensor sensor = TemperatureSensor(SPI, D8);

void setup() {
  Serial.begin(115200);
  SPI.begin();

  pinMode(D1, OUTPUT);
  digitalWrite(D1, HIGH);

  WiFi.mode(WIFI_STA);
  WiFi.begin(NETWORK, PASSWORD);

  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("OK");
  Serial.print("connected to WiFi network with IP address ");
  Serial.print(WiFi.localIP());
  Serial.print(" and hostname ");
  Serial.println(WiFi.hostname());
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
