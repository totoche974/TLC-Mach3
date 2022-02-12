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

#include "commandClavier.h"
#include "boutonMach3.h"
#include "manivelle.h"
#include "selector.h"
#include "screen.h"
#include "sleep.h"
#include "setup_i2c.h"

BleKeyboard keyboard("ESP32 Bluetooth", "Espressif", 80);

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

  if (5000 < elapseTime)
  {
    checkBluetoothIsConnected();
    timestampOrigin = millis();
  }

  checkMainBouton();

  manivelle();

  runCommandClavier();

  loopScreen();

  shouldSleep();
} // end loop
