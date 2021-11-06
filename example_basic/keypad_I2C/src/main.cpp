// Example from repository : https://github.com/joeyoung/arduino_keypads
// file : ./Keypad_I2C/examples/HelloKeypad_I2C/HelloKeypad_I2C.ino

// Dependency library:
// https://github.com/Chris--A/Keypad
// Can be install through Platformio  |  chris--a/Keypad@^3.1.1

// To use joeyoung keypad library, file .cpp and .h must be copied
// in the lib directory. More information i the README of the lib.

/* @file HelloKeypad.ino

   Revised to use I2C i/o Feb 26/12 - G. D. Young
   Re-check with Keypad 3.0, arduino 1.0.1 Jul 29/12
   Add port-type parameter to constructor for Paul
   Williamson's modification of the Keypad_I2C library Sept 2/13

   April 6/2020 - Keypad_I2C allows optional WireX parameter. Note
   that if WireX parameter is spec'd, then the otherwise optional
   'width' parameter is needed. OK to omit both options when using
   8 bit port chips on Wire

|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>

#define I2CADDR 0x27

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

// Digitran keypad, bit numbers of PCF8574 i/o port
const byte lig_1 = 0;
const byte lig_2 = 1;
const byte lig_3 = 2;
const byte lig_4 = 3;

const byte col_1 = 4;
const byte col_2 = 5;
const byte col_3 = 6;
const byte col_4 = 7;

byte rowPins[ROWS] = {lig_1, lig_2, lig_3, lig_4};
byte colPins[COLS] = {col_1, col_2, col_3, col_4};

TwoWire *jwire = &Wire; //test passing pointer to keypad lib
Keypad_I2C kpd(makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574, jwire);

void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {
  }

  //  Wire.begin( );
  jwire->begin();
  //  kpd.begin( makeKeymap(keys) );
  kpd.begin();
  Serial.print("start with pinState = ");
  Serial.println(kpd.pinState_set(), HEX);
}

void loop()
{

  char key = kpd.getKey();

  if (key)
  {
    Serial.println(key);
  }
}
