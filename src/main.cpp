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

// Externalised variable
Adafruit_SSD1306 *display = NULL;
// <----- Externalised variable

long timestampOrigin;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  { /*wait*/
  }
  Serial.println("Starting Télécommande BLE mach3");

  // keyboard.begin();

  // initCommandClavier();
  // initManivelle();
  // initI2C();

  initScreen();

  // // Bouton de sécurité pour la manivelle et le clavier
  // pinMode(PIN_SECU_BT, INPUT_PULLUP);
  // pinMode(PIN_START_BT, INPUT_PULLUP);
  // pinMode(PIN_PAUSE_BT, INPUT_PULLUP);
  // pinMode(PIN_ARRET_BT, INPUT_PULLUP);

  // pinMode(PIN_AXE_X, INPUT_PULLUP);
  // pinMode(PIN_AXE_Y, INPUT_PULLUP);
  // pinMode(PIN_AXE_Z, INPUT_PULLUP);
  // pinMode(PIN_AXE_A, INPUT_PULLUP);

  // initSleep();

  // screenSendMessage("TLC-M3 ON");

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

void showRectangle()
{
  display->clearDisplay();
  for (int x = 0; x < 128; ++x)
  {
    for (int y = 0; y < 32; ++y)
    {
      display->drawPixel(x, y, SSD1306_WHITE);
    }
  }
  display->display();
}

const int analogInPin = A13;
int dummy_int = 0;
bool paintScreen = true;

void loop()
{
  // long elapseTime = millis() - timestampOrigin;

  // if (5000 < elapseTime)
  // {
  //   checkBluetoothIsConnected();
  //   timestampOrigin = millis();
  // }

  // checkMainBouton();

  // manivelle();

  // runCommandClavier();

  // showRectangle();

  // shouldSleep();

  int sensorValue = analogRead(analogInPin);

  dummy_int += 1;

  // sensorValue : 2427
  // tension mesuré au multimètre : 4.2 V

  long elapseTime = millis() - timestampOrigin;

  if (1000 < elapseTime)
  {
    printf("sensorValue %d\n", sensorValue);

    if (paintScreen)
    {
      showRectangle();
    }
    else
    {
      display->clearDisplay();
      display->display();
    }

    paintScreen = !paintScreen;
    timestampOrigin = millis();
  }
}

// http://www.pinon-hebert.fr/Knowledge/index.php/ESP32#Lecture_de_la_charge_batterie
// int RATIO = 2;
// float vbat = RATIO * sensorValue / (4096.0 / 3.29);
// float vbat = RATIO * sensorValue / (4096.0 / 3.5);
// printf("vbat %f\n", vbat);
