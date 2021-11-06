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

BleKeyboard Keyboard("ESP32 Bluetooth clavier", "Espressif", 80);

uint32_t start, stop;
uint32_t lastKeyPressed = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  { /*wait*/
  }
  Serial.println("Starting Télécommande BLE mach3");

  Keyboard.begin();

  initCommandClavier();
  initManivelle();
  initScreen();

  // CTRL bouton pour la manivelle
  pinMode(PIN_SECU_BT, INPUT_PULLUP);

  pinMode(PIN_AXE_X, INPUT_PULLUP);
  pinMode(PIN_AXE_Y, INPUT_PULLUP);
  pinMode(PIN_AXE_Z, INPUT_PULLUP);
  pinMode(PIN_AXE_A, INPUT_PULLUP);
  pinMode(PIN_START_BT, INPUT_PULLUP);
  pinMode(PIN_PAUSE_BT, INPUT_PULLUP);
  pinMode(PIN_ARRET_BT, INPUT_PULLUP);
}

/**
 * @file fonction correspondantes au fichier :btMach3.cpp - cmdClavier.cpp - manivelle.cpp
 * @author
 * @brief Boutton de commande : STOP - PAUSE - ARRET
 *
 * @copyright Copyright (c) 2020
 *
 */
void loop()
{
  // Bouton mach3: STOP - PAUSE - START
  btMach3(PIN_ARRET_BT);
  btMach3(PIN_PAUSE_BT);
  btMach3(PIN_START_BT);

  manivelle();

  runCommandClavier();

} // end loop
