#include <Arduino.h>
#include <Keypad.h>
#include <BleKeyboard.h>
#include <Keypad_I2C.h>

#include "cmdClavier.h"

//-------------------------- Clavier Multiplexé ROWS 4 , COLS 3

const byte ROWS = 4; //4 lignes
const byte COLS = 3; //3 colonnes
char keys[ROWS][COLS] = {
    {
        '1',
        '2',
        '3',
    },
    {
        '4',
        '5',
        '6',
    },
    {
        '7',
        '8',
        '9',
    },
    {
        '*',
        '0',
        '#',
    }};

// entrées/sortie du PCF8574
const byte lig_1 = 3;
const byte lig_2 = 2;
const byte lig_3 = 1;
const byte lig_4 = 0;

const byte col_1 = 4;
const byte col_2 = 5;
const byte col_3 = 6;

byte rowPins[ROWS] = {lig_1, lig_2, lig_3, lig_4};
byte colPins[COLS] = {col_1, col_2, col_3};

const uint8_t KEYPAD_ADDRESS = 0x20;
TwoWire *jwire = &Wire; //test passing pointer to keypad lib
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, KEYPAD_ADDRESS, PCF8574, jwire);

void initCommandClavier()
{
  jwire->begin();
  jwire->setClock(400000);
  keypad.begin();
}

// extern BleKeyboard Keyboard;
// BleKeyboard Keyboard("ESP32 Bluetooth clavier", "Espressif", 80);

void Command_1(char key)
{
  Serial.print("key = ");
  Serial.println(key);
} // action à définir

void Command_2(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_3(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_4(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_5(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_6(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_7(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_8(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_9(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_0(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_A(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_B(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_C(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_D(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_E(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void Command_F(char key)
{
  Serial.print("key = ");
  Serial.println(key);
}

void runCommandClavier()
{
  char key = keypad.getKey();

  if (key)
  {
    Serial.println(key);
  }

  switch (key)
  {
  case '1':
    Command_1(key);
    break;
  case '2':
    Command_2(key);
    break;
  case '3':
    Command_3(key);
    break;
  case '4':
    Command_4(key);
    break;
  case '5':
    Command_5(key);
    break;
  case '6':
    Command_6(key);
    break;
  case '7':
    Command_7(key);
    break;
  case '8':
    Command_8(key);
    break;
  case '9':
    Command_9(key);
    break;
  case '0':
    Command_0(key);
    break;
  case 'A':
    Command_0(key);
    break;
  case 'B':
    Command_0(key);
    break;
  case 'C':
    Command_0(key);
    break;
  case 'D':
    Command_0(key);
    break;
  case 'E':
    Command_0(key);
    break;
  case 'F':
    Command_0(key);
    break;

  } // fin du switch
}

//  if (Keyboard.isConnected() && customKey != NO_KEY)
//  {
//    switch (customKey)
//    {
//    case '1': Command_1(customKey); break;
//    case '2': Command_2(customKey); break;
// //   case '3':
// //     Command_3(newkey);
// //     break;
// //   case '4':
// //     Command_4(newkey);
// //     break;
// //   case '5':
// //     Command_5(newkey);
// //     break;
// //   case '6':
// //     Command_6(newkey);
// //     break;
// //   case '7':
// //     Command_7(newkey);
// //     break;
// //   case '8':
// //     Command_8(newkey);
// //     break;
// //   case '9':
// //     Command_9(newkey);
// //     break;
// //   case '0':
// //     Command_0(newkey);
// //     break;
// //   case 'A':
// //     Command_0(newkey);
// //     break;
// //   case 'B':
// //     Command_0(newkey);
// //     break;
// //   case 'C':
// //     Command_0(newkey);
// //     break;
// //   case 'D':
// //     Command_0(newkey);
// //     break;
// //   case 'E':
// //     Command_0(newkey);
// //     break;
// //   case 'F':
// //     Command_0(newkey);
// //     break;

//    } // fin du switch

//  } // fin du if Keyboard.isConnected

//}// fin du test btSecu
