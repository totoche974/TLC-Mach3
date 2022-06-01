/**
 * @file main.cpp
 * @author
 * @brief Télécommande bluetooth pour mach3
 * @version 0.1
 * @date 2020-12-10
 *
 * @copyright Copyright (c) 2020
 *
 */

#include <Arduino.h>
#include <Keypad.h>
#include <BleKeyboard.h>
#include <AiEsp32RotaryEncoder.h>
#include <Wire.h>
#include <Keypad_I2C.h>
// #include <MAX1704X.h>

#include "commandClavier.h"
#include "boutonMach3.h"
#include "manivelle.h"
#include "selector.h"
#include "screen.h"
#include "sleep.h"
#include "setup_i2c.h"

// ***
// *** Connections:
// *** 1) Conect SDA pin to A4 on Uno
// *** 2) Connect SCL pin to A5 on Uno
// *** 3) Connect the GND pin to ground on the Uno.
// ***
// *** For other devices lookup the correct i2C
// *** (SDA and SCL) pins.
// ***

//
// Define the MAX17403 fuel gauge. Use MAX17044_mV
// for the MAX17044.
//
// MAX1704X _fuelGauge = MAX1704X(MAX17043_mV);
// MAX1704X _fuelGauge = MAX1704X(5.0 / (4096.0 * 2));

/**
 * @brief Bluetooth keyboard variable
 *
 */
BleKeyboard keyboard("ESP32 Bluetooth", "Espressif", 80);

/**
 * @brief Screen variable
 *
 */
Adafruit_SSD1306 *display = NULL;

/**
 * Time to handle sleep mode
 *
 */

long timestampOrigin;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  { /*wait*/
  }
  Serial.println("Starting Télécommande BLE mach3");

  keyboard.begin();

  initCommandClavier();
  initManivelle();
  initI2C();

  initScreen();

  // Bouton de sécurité pour la manivelle et le clavier
  pinMode(PIN_SECU_BT, INPUT_PULLUP);
  pinMode(PIN_START_BT, INPUT_PULLUP);
  pinMode(PIN_PAUSE_BT, INPUT_PULLUP);
  pinMode(PIN_ARRET_BT, INPUT_PULLUP);

  pinMode(PIN_AXE_X, INPUT_PULLUP);
  pinMode(PIN_AXE_Y, INPUT_PULLUP);
  pinMode(PIN_AXE_Z, INPUT_PULLUP);
  pinMode(PIN_AXE_A, INPUT_PULLUP);

  initSleep();

  screenSendMessage("TLC-M3 ON");

  //
  // Initialize the fuel gauge.
  //
  // if (_fuelGauge.begin(true, static_cast<uint8_t>(0x32)))
  // if (_fuelGauge.begin(&Wire, static_cast<uint8_t>(0x32)))
  // {
  //   Serial.println("The MAX1704X device was found.\n");

  //   //
  //   // Reset the device.
  //   //
  //   Serial.println("Resetting device...");
  //   _fuelGauge.reset();
  //   delay(250);

  //   //
  //   // Issue a quickstart command and wait
  //   // for the device to be ready.
  //   //
  //   Serial.println("Initiating quickstart mode...");
  //   _fuelGauge.quickstart();
  //   delay(125);
  // }
  // else
  // {
  //   Serial.println("The MAX1704X device was NOT found.\n");
  //   while (true)
  //     ;
  // }

  timestampOrigin = millis();
}

void checkBluetoothIsConnected()
{
  if (keyboard.isConnected())
  {
    printf("Bluetooth connected\n");
  }
  else
  {
    printf("Bluetooth NOT connected\n");
  }
}

void loop()
{
  long elapseTime = millis() - timestampOrigin;

  if (1000 < elapseTime)
  {
    // Serial.print("Battery Percent is ");
    // Serial.print(_fuelGauge.percent(true));
    // Serial.println("%");
    // printf("_fuelGauge.percent(true) %f \n", _fuelGauge.percent(true));
    checkBluetoothIsConnected();
    timestampOrigin = millis();
  }

  checkMainBouton();

  manivelle();

  runCommandClavier();

  shouldSleep();

  loopScreen();
}
