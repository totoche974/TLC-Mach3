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
//#include "I2CKeyPad.h"
#include <Keypad_I2C.h>

#define ROTARY_ENCODER_A_PIN 19      // 32
#define ROTARY_ENCODER_B_PIN 18      // 21
#define ROTARY_ENCODER_BUTTON_PIN -1 // 25
#define ROTARY_ENCODER_VCC_PIN -1    /* 27 put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */

#define ROTARY_ENCODER_STEPS 4

extern Keypad_I2C keypad;
extern BleKeyboard Keyboard;

// definition des structures
// Manivelle MAN;
 Clavier C;

//instead of changing here, rather change numbers above
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN,
                                                          ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN,
                                                          ROTARY_ENCODER_STEPS);

// const uint8_t KEYPAD_ADDRESS = 0x38;
const uint8_t KEYPAD_ADDRESS = 0x20;
// const uint8_t KEYPAD_ADDRESS = 0x27;

//I2CKeyPad keyPad(KEYPAD_ADDRESS);

uint32_t start, stop;
uint32_t lastKeyPressed = 0;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting Télécommande BLE mach3");

  Keyboard.begin();
  keypad.begin();

  //we must initialize rotary encoder
  rotaryEncoder.begin();

  rotaryEncoder.setup(
      []
      {
        rotaryEncoder.readEncoder_ISR();
      },
      [] {});

  rotaryEncoder.setAcceleration(250);

  Wire.begin();
  Wire.setClock(400000);
  //if (keyPad.begin() == false)
  //   {
    //Serial.println("\nERROR: cannot communicate to keypad.\nPlease reboot.\n");
    //while (1)
     // ;
  //}

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

char customKey = keypad.getKey();
  
  if (customKey != NO_KEY){
    Serial.println(customKey);
  }

  // // Bouton mach3: STOP - PAUSE - START
  // btMach3WK(PIN_ARRET_BT);
  // btMach3WK(PIN_PAUSE_BT);
  // btMach3WK(PIN_START_BT);

  // manivelle();

  //uint32_t now = millis();
  //char keys[] = "123A456B789C*0#DNF"; // N = Nokey, F = Fail
  //char keys[] = "123456789*0#NF"; // N = Nokey, F = Fail

  //if (now - lastKeyPressed >= 100)
  //{
  //  lastKeyPressed = now;

  //  start = micros();
  //  uint8_t idx = KeyPad.getKey();
  //  stop = micros();

  //  Serial.print(millis());
  //  Serial.print("\t");
  //  Serial.print(idx);
  //  Serial.print("\t");
  //  Serial.print(keys[idx]);
  //  Serial.print("\t");
  //  Serial.println(stop - start);
  //}

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
