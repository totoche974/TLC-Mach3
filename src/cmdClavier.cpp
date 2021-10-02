#include <Arduino.h>
#include "cmdClavier.h"
#include <Keypad.h>
#include <BleKeyboard.h>

#include "I2CKeyPad.h"

extern Clavier C;

//-------------------------- Clavier I2C Multiplexé ROWS 4 , COLS 3

const uint8_t KEYPAD_ADDRESS = 0x20;
I2CKeyPad keyPad(KEYPAD_ADDRESS);

char keys[ROWS][COLS] = {
  {'1', '2', '3',},   //  I=F1, U=F2
  {'4', '5', '6',},
  {'7', '8', '9',},
  {'*', '0', '#',}
  /*,   //  C=Esc
  {'L', '0', 'R', 'E'}*/
};

byte rowPins[ROWS] = {C.lig_1, C.lig_2, C.lig_3, C.lig_4};
byte colPins[COLS] = {C.col_1, C.col_2, C.col_3};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
/*
 if(keyPad.begin() == false) { 
  Serial.println("\nERREUR: Pas de communiquation avec le clavier.\nVeuillez rebooter le systeme.\n"); 
  while(1); 
  }
*/
extern BleKeyboard Keyboard;

void Command_1(char newkey) { Serial.print("newkey = ");Serial.println(newkey); } // action à définir

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
