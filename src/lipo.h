#pragma once

#include <Arduino.h>

// http://librarymanager/All#SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library
#include <SparkFun_MAX1704x_Fuel_Gauge_Arduino_Library.h>

const uint8_t PIN_LED_LIPO_ALERT = GPIO_NUM_27;
const uint8_t PIN_BT_VISU_CHARGE_LIPO = GPIO_NUM_25;

void initLipo();
void ledAlertShouldBlink();
void boutonVisuChargeLipo();