#include <temperature.h>
#include <unity.h>

void test_temperature_sensor_reading_status() {
  TEST_ASSERT_EQUAL(TemperatureSensorReading(0).status(),
                    TemperatureSensorStatus::ok);
  TEST_ASSERT_EQUAL(TemperatureSensorReading(1).status(),
                    TemperatureSensorStatus::open_connection);
  TEST_ASSERT_EQUAL(TemperatureSensorReading(2).status(),
                    TemperatureSensorStatus::short_circuit_ground);
  TEST_ASSERT_EQUAL(TemperatureSensorReading(3).status(),
                    TemperatureSensorStatus::open_connection);
  TEST_ASSERT_EQUAL(TemperatureSensorReading(4).status(),
                    TemperatureSensorStatus::short_circuit_vcc);
  TEST_ASSERT_EQUAL(TemperatureSensorReading(5).status(),
                    TemperatureSensorStatus::open_connection);
  TEST_ASSERT_EQUAL(TemperatureSensorReading(6).status(),
                    TemperatureSensorStatus::short_circuit_ground);
  TEST_ASSERT_EQUAL(TemperatureSensorReading(7).status(),
                    TemperatureSensorStatus::open_connection);
  TEST_ASSERT_EQUAL(TemperatureSensorReading(8).status(),
                    TemperatureSensorStatus::ok);
  TEST_ASSERT_EQUAL(TemperatureSensorReading(0xffffffff).status(),
                    TemperatureSensorStatus::open_connection);
}

void test_temperature_sensor_reading_temperature() {
  TEST_ASSERT_EQUAL_FLOAT(1600.0,
                          TemperatureSensorReading(0x64000000).temperature());
  TEST_ASSERT_EQUAL_FLOAT(1000.0,
                          TemperatureSensorReading(0x3e800000).temperature());
  TEST_ASSERT_EQUAL_FLOAT(100.75,
                          TemperatureSensorReading(0x064c0000).temperature());
  TEST_ASSERT_EQUAL_FLOAT(25.0,
                          TemperatureSensorReading(0x01900000).temperature());
  TEST_ASSERT_EQUAL_FLOAT(0.0,
                          TemperatureSensorReading(0x00000000).temperature());
  TEST_ASSERT_EQUAL_FLOAT(-0.25,
                          TemperatureSensorReading(0xfffc0000).temperature());
  TEST_ASSERT_EQUAL_FLOAT(-1.0,
                          TemperatureSensorReading(0xfff00000).temperature());
  TEST_ASSERT_EQUAL_FLOAT(-250.0,
                          TemperatureSensorReading(0xf0600000).temperature());
}

void test_temperature_sensor_reading_temperature_internal() {
  TEST_ASSERT_EQUAL_FLOAT(
      127.0, TemperatureSensorReading(0x00007f00).temperature_internal());
  TEST_ASSERT_EQUAL_FLOAT(
      100.5625, TemperatureSensorReading(0x00006490).temperature_internal());
  TEST_ASSERT_EQUAL_FLOAT(
      25.0, TemperatureSensorReading(0x00001900).temperature_internal());
  TEST_ASSERT_EQUAL_FLOAT(
      0.0, TemperatureSensorReading(0x00000000).temperature_internal());
  TEST_ASSERT_EQUAL_FLOAT(
      -0.0625, TemperatureSensorReading(0x0000fff0).temperature_internal());
  TEST_ASSERT_EQUAL_FLOAT(
      -1.0, TemperatureSensorReading(0x0000ff00).temperature_internal());
  TEST_ASSERT_EQUAL_FLOAT(
      -20.0, TemperatureSensorReading(0x0000ec00).temperature_internal());
  TEST_ASSERT_EQUAL_FLOAT(
      -55.0, TemperatureSensorReading(0x0000c900).temperature_internal());
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_temperature_sensor_reading_status);
  RUN_TEST(test_temperature_sensor_reading_temperature);
  RUN_TEST(test_temperature_sensor_reading_temperature_internal);
  UNITY_END();
}

void loop() {}
