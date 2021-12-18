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

BleKeyboard Keyboard("ESP32 Bluetooth clavier", "Espressif", 80);

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  { /*wait*/
  }
  // Serial.println("Starting Télécommande BLE mach3");

  Keyboard.begin();

  initCommandClavier();
  initManivelle();
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

  printf("digitalRead(PIN_SECU_BT): %d\n", digitalRead(PIN_SECU_BT));
  printf("LOW %d\n", LOW);
  printf("HIGH %d\n", HIGH);

  screenSendMessage("TLC-M3 ON");
}

void loop()
{
  checkMainBouton();

  manivelle();

  runCommandClavier();

  loopScreen();

  shouldSleep();
} // end loop
