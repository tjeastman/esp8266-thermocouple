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

void test_temperature_sensor_reading_valid() {
  TEST_ASSERT_TRUE(TemperatureSensorReading(0).valid());
  TEST_ASSERT_FALSE(TemperatureSensorReading(1).valid());
  TEST_ASSERT_FALSE(TemperatureSensorReading(2).valid());
  TEST_ASSERT_FALSE(TemperatureSensorReading(3).valid());
  TEST_ASSERT_FALSE(TemperatureSensorReading(4).valid());
  TEST_ASSERT_FALSE(TemperatureSensorReading(5).valid());
  TEST_ASSERT_FALSE(TemperatureSensorReading(6).valid());
  TEST_ASSERT_FALSE(TemperatureSensorReading(7).valid());
  TEST_ASSERT_TRUE(TemperatureSensorReading(8).valid());
  TEST_ASSERT_FALSE(TemperatureSensorReading(0xffffffff).valid());
}

void test_temperature_sensor_reading_temperature() {
  TEST_ASSERT_EQUAL_FLOAT(
      1600.0, TemperatureSensorReading(0x64000000).temperatures().first);
  TEST_ASSERT_EQUAL_FLOAT(
      1000.0, TemperatureSensorReading(0x3e800000).temperatures().first);
  TEST_ASSERT_EQUAL_FLOAT(
      100.75, TemperatureSensorReading(0x064c0000).temperatures().first);
  TEST_ASSERT_EQUAL_FLOAT(
      25.0, TemperatureSensorReading(0x01900000).temperatures().first);
  TEST_ASSERT_EQUAL_FLOAT(
      0.0, TemperatureSensorReading(0x00000000).temperatures().first);
  TEST_ASSERT_EQUAL_FLOAT(
      -0.25, TemperatureSensorReading(0xfffc0000).temperatures().first);
  TEST_ASSERT_EQUAL_FLOAT(
      -1.0, TemperatureSensorReading(0xfff00000).temperatures().first);
  TEST_ASSERT_EQUAL_FLOAT(
      -250.0, TemperatureSensorReading(0xf0600000).temperatures().first);
}

void test_temperature_sensor_reading_internal_temperature() {
  TEST_ASSERT_EQUAL_FLOAT(
      127.0, TemperatureSensorReading(0x00007f00).temperatures().second);
  TEST_ASSERT_EQUAL_FLOAT(
      100.5625, TemperatureSensorReading(0x00006490).temperatures().second);
  TEST_ASSERT_EQUAL_FLOAT(
      25.0, TemperatureSensorReading(0x00001900).temperatures().second);
  TEST_ASSERT_EQUAL_FLOAT(
      0.0, TemperatureSensorReading(0x00000000).temperatures().second);
  TEST_ASSERT_EQUAL_FLOAT(
      -0.0625, TemperatureSensorReading(0x0000fff0).temperatures().second);
  TEST_ASSERT_EQUAL_FLOAT(
      -1.0, TemperatureSensorReading(0x0000ff00).temperatures().second);
  TEST_ASSERT_EQUAL_FLOAT(
      -20.0, TemperatureSensorReading(0x0000ec00).temperatures().second);
  TEST_ASSERT_EQUAL_FLOAT(
      -55.0, TemperatureSensorReading(0x0000c900).temperatures().second);
}

void setup() {
  UNITY_BEGIN();
  RUN_TEST(test_temperature_sensor_reading_status);
  RUN_TEST(test_temperature_sensor_reading_valid);
  RUN_TEST(test_temperature_sensor_reading_temperature);
  RUN_TEST(test_temperature_sensor_reading_internal_temperature);
  UNITY_END();
}

void loop() {}
