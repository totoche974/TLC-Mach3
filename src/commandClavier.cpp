#include <Arduino.h>
#include <Keypad.h>
#include <BleKeyboard.h>
#include <Keypad_I2C.h>
#include "WiFi.h"

#include "commandClavier.h"

#include "screen.h"
#include "axe.h"

extern BleKeyboard Keyboard;

const uint8_t KEYPAD_ADDRESS = 0x27;

const byte ROWS = 4; //4 lignes
const byte COLS = 4; //4 colonnes
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'E', '0', 'F', 'D'}};

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
Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, KEYPAD_ADDRESS, PCF8574, jwire);


void initCommandClavier()
{
  jwire->begin();
  jwire->setClock(400000);
  keypad.begin();
  keypad.setHoldTime(1);
}

// extern BleKeyboard Keyboard;
// BleKeyboard Keyboard("ESP32 Bluetooth clavier", "Espressif", 80);

void Command_1(char key)
{
  Serial.print("key = "); Serial.println(key);
  screenSendMessage("Rembobinne");
  Keyboard.press(KEY_LEFT_CTRL); Keyboard.write(KEY_F12); delay(50); Keyboard.releaseAll();// touche Ctrl + touche F12 
  } 

void Command_2(char key)
{
  Serial.print("key = "); Serial.println(key);
  screenSendMessage("  Z Haut"); 
  Keyboard.press(KEY_F3); delay(50); Keyboard.release(KEY_F3); // touche F3  
}

void Command_3(char key)
{
  Serial.print("key = "); Serial.println(key);
  screenSendMessage(" Parking");
  Keyboard.press(KEY_F7); delay(50); Keyboard.release(KEY_F7); // touche F7  
}

void Command_4(char key)
{  
  Serial.print("key = "); Serial.println(key);
  screenSendMessage("Lubrifier");
  Keyboard.press(KEY_LEFT_CTRL); Keyboard.write('f');delay(50); Keyboard.releaseAll();// touche Ctrl + touche "F"
}

void Command_5(char key)
{
Serial.print("key = "); Serial.println(key);
screenSendMessage("M/A Broche");
Keyboard.press(KEY_F5); delay(50); Keyboard.release(KEY_F5);// touche F5 - M/A broche
}

void Command_6(char key)
{
  Serial.print("key = "); Serial.println(key);
  screenSendMessage(" Probe Z");
  Keyboard.press(KEY_F6); delay(50); Keyboard.release(KEY_F6);// touche F3  
}

void Command_7(char key)
{
  Serial.print("Key = "); Serial.println(key);
  screenSendMessage("XY=0 table");
  Keyboard.press(KEY_F2); delay(50); Keyboard.release(KEY_F2); // touche F2  
}

void Command_8(char key)
{
  Serial.print("key = "); Serial.println(key);
  screenSendMessage("Select Pas");
  Keyboard.press(KEY_F8); delay(50); Keyboard.release(KEY_F8); // touche F8  
}

void Command_9(char key)
{
  Serial.print("key = "); Serial.println(key);
 screenSendMessage("Mod. manuel"); 
 Keyboard.press(KEY_LEFT_CTRL); Keyboard.write(74); delay(50); Keyboard.releaseAll();// touche Ctrl + touche "J"
}

void Command_0(char key)
{
  Serial.print("key = "); Serial.println(key);
  screenSendMessage("RaZ XY = 0");
  Keyboard.press(KEY_F9); delay(50); Keyboard.release(KEY_F9); // touche F9  
}

void Command_A(char key)
{
  Serial.print("key = "); Serial.println(key);
  screenSendMessage(" Home"); 
  Keyboard.press(KEY_F4); delay(50); Keyboard.release(KEY_F4); // touche F4 
}

void Command_B(char key)
{
  Serial.print("key = "); Serial.println(key);
  screenSendMessage(" Ref: XYZ");
  Keyboard.press(KEY_LEFT_CTRL); delay(50); Keyboard.release(KEY_F8); // touche Ctrl + F8 
}

void Command_C(char key)
{
  Serial.print("key = "); Serial.println(key);
  screenSendMessage("C: Not used");
}

void Command_D(char key)
{
  Serial.print("key = "); Serial.println(key);
  screenSendMessage("D: Not used");
}

void Command_E(char key)
{
  Serial.print("key = "); Serial.println(key);
  screenSendMessage("E: Not used");
}

void Command_F(char key)
{
  Serial.print("key = "); Serial.println(key);
  screenSendMessage("F: Not used");
}

/**
 * @brief Detection de l'appui long ou court pour le référencement des axes
 * Si BT pressé, < de 300ms éxécution de la remise à zéro de tous les axes 
 * si BT préssé > de 300ms , remise à zéro de l'axe sélectionné
 * 
 * 
 */

boolean tempoActive = false;
unsigned long tempoDepart;
#define THRESHOLD_SHORT_HOLD_TIME 300 // Durée minimum de l'appui sur le bouton
const uint8_t NB_AUTORISED_BUTTON = 1; 
char authorisedBouton[NB_AUTORISED_BUTTON] = {'0'};

bool isAuthoriseKey(char key)
{
  bool found = false;
  for (int i = 0; i < NB_AUTORISED_BUTTON; ++i)
  {
    if (authorisedBouton[i] == key)
    {
      found = true;
      break;
    }
  }
  return found;
}

enum pressState { In_progress, Finished, };

struct shortPressedResult
{
  pressState state;
  bool isShort;
};

shortPressedResult isShortPressed()
{
  shortPressedResult res;
  // Serial.println("keypad.getState() : " + String(keypad.getState()));
  // Si le bouton est enfoncé,
  if (!tempoActive && (keypad.getState() == PRESSED))
  {
    tempoActive = true;
    tempoDepart = millis();
    // Serial.println("on démare la temporisation");
    // Serial.println("00 tempoDepart : " + String(tempoDepart));
  }

  // Si le bouton est relache,
  if (tempoActive && (keypad.getState() == RELEASED))
  {
    tempoActive = false;
    unsigned long tempoStop = millis();
    unsigned long elapseTime = tempoStop - tempoDepart;
    // Serial.println("on ARRETE la temporisation");
    // Serial.println("11 tempoDepart : " + String(tempoDepart));
    // Serial.println("tempoStop : " + String(tempoStop));
    // Serial.println("elapseTime : " + String(elapseTime));
    if (elapseTime < THRESHOLD_SHORT_HOLD_TIME)
    {
      res.state = pressState::Finished;
      res.isShort = true;
      return res;
    }
    else
    {
      res.state = pressState::Finished;
      res.isShort = false;
      return res;
    }
  }

  res.state = pressState::In_progress;
  res.isShort = false;
  return res;
}

//
void managePressBoutonShortLong()
{
  // Sanity check
  char key = keypad.key[0].kchar;
  if ((keypad.getState() == IDLE) || (!isAuthoriseKey(key)))
  {
    return;
  }

  shortPressedResult resultIsShortPressed = isShortPressed();
  if (resultIsShortPressed.state != pressState::Finished)
    {
    return;
    }

  bool isShortPressed = resultIsShortPressed.isShort;

  if (isShortPressed)
  {
    switch (key)
    {
    case '0': Command_0(key); break; // Remise à zéro des axes XYZ
   
    
    } // Fin du swich
  } // Fin du if

  else if ((key == '0'))
  {
    String toPrint = "Raz ";
    switch (getCurrentAxe())
    {
    case Axe_x: { toPrint += "X = 0"; Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_F3); delay(50); Keyboard.releaseAll(); break; }
    case Axe_y: { toPrint += "Y = 0"; Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_F4); delay(50); Keyboard.releaseAll(); break; }
    case Axe_z: { toPrint += "Z = 0"; Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_F6); delay(50); Keyboard.releaseAll(); break; }
    case Axe_a: { toPrint += "A = 0"; Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_F5); delay(50); Keyboard.releaseAll(); break; }
    }
    screenSendMessage(toPrint);
  } // fin du else

  //else if ((key == '9')) { } 

} // Fin de la fonction

void runCommandClavier()
{
  char key = keypad.getKey();

  managePressBoutonShortLong();

  if (key) { Serial.println(key); }
  switch (key)
  {
  case '1': Command_1(key); break;
  case '2': Command_2(key); break;
  case '3': Command_3(key); break;
  case '4': Command_4(key); break;
  case '5': Command_5(key); break;
  case '6': Command_6(key); break;
  case '7': Command_7(key); break;
  case '8': Command_8(key); break;
  case '9': Command_9(key); break;
  //case '0': Command_0(key); break;
  case 'A': Command_A(key); break;
  case 'B': Command_B(key); break;
  case 'C': Command_C(key); break;
  case 'D': Command_D(key); break;
  case 'E': Command_E(key); break;
  case 'F': Command_F(key); break;
    // default:
    //   Serial.print("DEFAULT key = ");
    //   Serial.println(key);
    //   break;

  } // fin du switch
} // Fin de la fonction