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
#include "cmdClavier.h"
#include "btMach3.h"
#include "manivelle.h"
#include <Keypad.h>
#include <BleKeyboard.h>
#include <AiEsp32RotaryEncoder.h>
#include "bouton.h"

#include "Wire.h"
#include "I2CKeyPad.h"

#define ROTARY_ENCODER_A_PIN 19      // 32
#define ROTARY_ENCODER_B_PIN 18      // 21
#define ROTARY_ENCODER_BUTTON_PIN -1 // 25
#define ROTARY_ENCODER_VCC_PIN -1    /* 27 put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */

#define ROTARY_ENCODER_STEPS 4

extern Keypad keypad;
extern BleKeyboard Keyboard;

// definition des structures
// Manivelle MAN;
Clavier C;

//instead of changing here, rather change numbers above
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN,
                                                          ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN,
                                                          ROTARY_ENCODER_STEPS);

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting Télécommande BLE mach3");

  Keyboard.begin();
  Wire.begin();
  Wire.setClock(400000);

  //we must initialize rotary encoder
  rotaryEncoder.begin();

  rotaryEncoder.setup(
      []
      {
        rotaryEncoder.readEncoder_ISR();
      },
      [] {});

  rotaryEncoder.setAcceleration(250);

  pinMode(PIN_SECU_BT, INPUT_PULLUP); // CTRL bouton pour la manivelle

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
  btMach3WK(PIN_ARRET_BT);
  btMach3WK(PIN_PAUSE_BT);
  btMach3WK(PIN_START_BT);

  manivelle();

  // if (Keyboard.isConnected() && newkey)
  // {
  //   switch (newkey)
  //   {
  //   case '1':
  //     Command_1(newkey);
  //     break;
  //   case '2':
  //     Command_2(newkey);
  //     break;
  //   case '3':
  //     Command_3(newkey);
  //     break;
  //   case '4':
  //     Command_4(newkey);
  //     break;
  //   case '5':
  //     Command_5(newkey);
  //     break;
  //   case '6':
  //     Command_6(newkey);
  //     break;
  //   case '7':
  //     Command_7(newkey);
  //     break;
  //   case '8':
  //     Command_8(newkey);
  //     break;
  //   case '9':
  //     Command_9(newkey);
  //     break;
  //   case '0':
  //     Command_0(newkey);
  //     break;
  //   case 'A':
  //     Command_0(newkey);
  //     break;
  //   case 'B':
  //     Command_0(newkey);
  //     break;
  //   case 'C':
  //     Command_0(newkey);
  //     break;
  //   case 'D':
  //     Command_0(newkey);
  //     break;
  //   case 'E':
  //     Command_0(newkey);
  //     break;
  //   case 'F':
  //     Command_0(newkey);
  //     break;

  //   } // fin du switch

  // } // fin du if Keyboard.isConnected

  //}// fin du test btSecu

} // end loop
