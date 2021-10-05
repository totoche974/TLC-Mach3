#include <Arduino.h>
#include "cmdClavier.h"
#include <Keypad.h>
#include <BleKeyboard.h>
#include <Keypad_I2C.h>

extern Clavier C;
//extern Keypad keypad;

const uint8_t KEYPAD_ADDRESS = 0x20;

//-------------------------- Clavier Multiplexé ROWS 4 , COLS 3

char keys[ROWS][COLS] = {
  {'1', '2', '3', },   //  I=F1, U=F2
  {'4', '5', '6', },
  {'7', '8', '9', },
  {'*', '0', '#', }
};

byte rowPins[ROWS] = {C.lig_1, C.lig_2, C.lig_3, C.lig_4};
byte colPins[COLS] = {C.col_1, C.col_2, C.col_3};


//Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Keypad_I2C keypad = Keypad_I2C ( makeKeymap(keys), rowPins, colPins, ROWS, COLS, KEYPAD_ADDRESS); 

extern BleKeyboard Keyboard;

void Command_1(char customKey) { Serial.print("customKey = ");Serial.println(customKey); } // action à définir

void Command_2(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_3(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_4(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_5(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_6(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_7(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_8(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_9(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_0(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_A(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_B(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_C(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_D(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_E(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }

void Command_F(char newkey) { Serial.print("newkey = ");Serial.println(newkey); }