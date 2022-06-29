#pragma once

#include <Arduino.h>

// Click here to get the library:
// http://librarymanager/All#SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>

const uint8_t PIN_LED_LIPO_ALERT = GPIO_NUM_26;

void initLipo();
void ledAlertShouldBlink();