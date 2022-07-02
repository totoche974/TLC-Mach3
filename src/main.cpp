/**
 * @file main.cpp
 * @author Gaston, Frozar, Gilles
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
#include "lipo.h"
#include "WiFi.h"

// SFE_MAX1704X lipo(MAX1704X_MAX17043);

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
  initLipo();

  // Bouton de sécurité pour la manivelle et le clavier
  pinMode(PIN_SECU_BT, INPUT_PULLUP);
  pinMode(PIN_START_BT, INPUT_PULLUP);
  pinMode(PIN_PAUSE_BT, INPUT_PULLUP);
  pinMode(PIN_ARRET_BT, INPUT_PULLUP);

  pinMode(PIN_AXE_X, INPUT_PULLUP);
  pinMode(PIN_AXE_Y, INPUT_PULLUP);
  pinMode(PIN_AXE_Z, INPUT_PULLUP);
  pinMode(PIN_AXE_A, INPUT_PULLUP);

  pinMode(PIN_LED_LIPO_ALERT, OUTPUT);
  digitalWrite(PIN_LED_LIPO_ALERT, LOW);

  pinMode(PIN_BT_VISU_CHARGE_LIPO, INPUT_PULLUP);
  //digitalWrite(PIN_BT_VISU_CHARGE_LIPO, HIGH);

  initSleep();

  screenSendMessage("TLC-M3 ON");

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

void DisableWifi()
{
  WiFi.disconnect(true); // Disconnect from the network
  WiFi.mode(WIFI_OFF);   // Switch WiFi off
}

void loop()
{
  long elapseTime = millis() - timestampOrigin;

  if (1000 < elapseTime)
  {
    checkBluetoothIsConnected();
    timestampOrigin = millis();
  }

  boutonVisuChargeLipo();

  checkMainBouton();

  manivelle();

  runCommandClavier();

  shouldSleep();
  ledAlertShouldBlink();

  loopScreen();
}
