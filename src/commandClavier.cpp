/**
 * @file commandClavier.cpp
 */

#include <Arduino.h>
#include <Keypad.h>
#include <BleKeyboard.h>
#include <Keypad_I2C.h>

#include "commandClavier.h"

#include "screen.h"
#include "boutonMach3.h"
#include "sleep.h"
#include "axe.h"
#include "lipo.h"

extern BleKeyboard keyboard;

const uint8_t KEYPAD_ADDRESS = 0x27;

const byte ROWS = 4; // 4 lignes
const byte COLS = 4; // 4 colonnes
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

Keypad_I2C keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS, KEYPAD_ADDRESS, PCF8574, &Wire);

void initCommandClavier()
{
  keypad.begin();
  keypad.setHoldTime(1);
}

void Command_1(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage("Rembobinne");
  keyboard.press(KEY_LEFT_CTRL);
  keyboard.write(KEY_F12);
  delay(50);
  keyboard.releaseAll(); // touche Ctrl + touche F12
}

void Command_2(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage("  Z Haut");
  keyboard.press(KEY_F3);
  delay(50);
  keyboard.release(KEY_F3); // touche F3
}

void Command_3(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage(" Parking");
  keyboard.press(KEY_F7);
  delay(50);
  keyboard.release(KEY_F7); // touche F7
}

void Command_4(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage("Lubrifier");
  keyboard.press(KEY_LEFT_CTRL);
  keyboard.write('f');
  delay(50);
  keyboard.releaseAll(); // touche Ctrl + touche "F"
}

void Command_5(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage("M/A Broche");
  keyboard.press(KEY_F5);
  delay(50);
  keyboard.release(KEY_F5); // touche F5 - M/A broche
}

void Command_6(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage(" Probe Z");
  keyboard.press(KEY_F6);
  delay(50);
  keyboard.release(KEY_F6); // touche F3
}

void Command_7(char key)
{
  Serial.print("Key = ");
  Serial.println(key);
  screenSendMessage("XY=0 Work");
  keyboard.press(KEY_F2);
  delay(50);
  keyboard.release(KEY_F2); // touche F2
}

void Command_8(char key) // touche F8 - Choix du pas :2mm,1mm,0.5mm,0.25mm,0.1mm,0.01mmmm,0.001mm,0.0001mm
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage("Select Pas");
  keyboard.press(KEY_F8); // touche F8
  delay(50);
  keyboard.release(KEY_F8);
}

void Command_9(char key) // touche Ctrl + touche "J" - choix du mode : pas à pas, continu, mpg
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage("Mod. manuel");
  keyboard.press(KEY_LEFT_CTRL); // touche Ctrl
  keyboard.write(74);            // touche "J"
  delay(50);
  keyboard.releaseAll();
}

void Command_0(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage("RaZ XY = 0");
  keyboard.press(KEY_F9);
  delay(50);
  keyboard.release(KEY_F9); // touche F9
}

void Command_A(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage(" Home");
  keyboard.press(KEY_F4);
  delay(50);
  keyboard.release(KEY_F4); // touche F4
}

void Command_B(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage(" Ref. XYZ");
  keyboard.press(KEY_LEFT_CTRL);
  delay(50);
  keyboard.release(KEY_F8); // touche Ctrl + F8
}

void Command_C(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage("C: Not used");
}

void Command_D(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage("D: Not used");
}

// extern SFE_MAX1704X lipo;

void Command_E(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage("Pas a pas"); // Déplacement pas a pas
  keyboard.press(KEY_LEFT_CTRL);  // touche CTRL
}

void Command_F(char key)
{
  Serial.print("key = ");
  Serial.println(key);
  screenSendMessage("Dep.Rapide"); // Déplacement rapide
  keyboard.press(KEY_RIGHT_SHIFT); // touche MAJ
}

/**
 * @brief Detection de l'appui long ou court pour la mise à zéro des axes
 * Si BT pressé, < de 300ms éxécution de la remise à zéro de tous les axes
 * si BT préssé > de 300ms , remise à zéro de l'axe sélectionné
 *
 *
 */

boolean tempoActive = false;
unsigned long tempoDepart;
#define THRESHOLD_SHORT_HOLD_TIME 300 // Durée minimum de l'appui sur le bouton
const uint8_t NB_SHORT_LONG_PRESS_KEY = 1;
char listShortLongKey[NB_SHORT_LONG_PRESS_KEY] = {'0'};

// Dans le cas où on souhaite ajouter la touche '1' pour qu'elle
// gère appui court / appui long.
// const uint8_t NB_SHORT_LONG_PRESS_KEY = 2;
// char listShortLongKey[NB_SHORT_LONG_PRESS_KEY] = {'0', '1'};

bool doesKeyManageShortLongPress(char key)
{
  bool found = false;
  for (int i = 0; i < NB_SHORT_LONG_PRESS_KEY; ++i)
  {
    if (listShortLongKey[i] == key)
    {
      found = true;
      break;
    }
  }
  return found;
}

enum pressState
{
  In_progress,
  Finished,
};

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

/**
 * @brief Configure le comportement des touches en appui court / appui long.
 */
void manageShortLongPressKey()
{
  // Sanity check
  char key = keypad.key[0].kchar;
  if ((keypad.getState() == IDLE) || (!doesKeyManageShortLongPress(key)))
  {
    return;
  }

  shortPressedResult resultIsShortPressed = isShortPressed();
  if (resultIsShortPressed.state != pressState::Finished)
  {
    return;
  }

  bool isShortPressed = resultIsShortPressed.isShort;

  // Cas de l'appui court
  if (isShortPressed)
  {
    switch (key)
    {
      // Remise à zéro des axes XY
    case '0':
    {
      Command_0(key);
      refreshSleepOriginTimestamp();
      break;
    }
      // Dans le cas où on souhaite ajouter la touche '1' pour qu'elle
      // gère appui court / appui long.
      // case '1':
      // {
      //   break;
      // }
    }
  }

  // Cas de l'appui long
  else
  {
    switch (key)
    {
      // Remise à zéro de l'axes sélectionné
    case '0':
    {
      String toPrint = "Raz ";
      switch (getCurrentAxe())
      {
      case Axe_x:
      {
        toPrint += "X = 0";
        keyboard.press(KEY_LEFT_CTRL);
        keyboard.press(KEY_F3);
        delay(50);
        keyboard.releaseAll();
        break;
      }
      case Axe_y:
      {
        toPrint += "Y = 0";
        keyboard.press(KEY_LEFT_CTRL);
        keyboard.press(KEY_F4);
        delay(50);
        keyboard.releaseAll();
        break;
      }
      case Axe_z:
      {
        toPrint += "Z = 0";
        keyboard.press(KEY_LEFT_CTRL);
        keyboard.press(KEY_F5);
        delay(50);
        keyboard.releaseAll();
        break;
      }
      case Axe_a:
      {
        toPrint += "A = 0";
        keyboard.press(KEY_LEFT_CTRL);
        keyboard.press(KEY_F6);
        delay(50);
        keyboard.releaseAll();
        break;
      }
      }
      screenSendMessage(toPrint);
      refreshSleepOriginTimestamp();
      break;
    }

      // Dans le cas où on souhaite ajouter la touche '1' pour qu'elle
      // gère appui court / appui long.
      // case '1':
      // {
      //   break;
      // }
    }
  }
}

/**
 * @brief Configure le comportement des touches qui sont protégées par
 *        le bouton de sécurité.
 */
void manageKeyProtectedBySecurityButton()
{
  if ((digitalRead(PIN_SECU_BT) == LOW))
  {
    char key = keypad.getKey();
    if (key)
    {
      Serial.println(key);
    }
    switch (key)
    {
      // La touche '0' gère des appuis courts / appuis longs.
      // case '0':
      //   Command_0(key);
      //   refreshSleepOriginTimestamp();
      //   break;

      // Dans le cas où on souhaite ajouter la touche '1' pour qu'elle
      // gère appui court / appui long.
      // Il faut commenter le case '1'
    case '1':
      Command_1(key);
      refreshSleepOriginTimestamp();
      break;
    case '2':
      Command_2(key);
      refreshSleepOriginTimestamp();
      break;
    case '3':
      Command_3(key);
      refreshSleepOriginTimestamp();
      break;
    case '4':
      Command_4(key);
      refreshSleepOriginTimestamp();
      break;
    case '5':
      Command_5(key);
      refreshSleepOriginTimestamp();
      break;
    case '6':
      Command_6(key);
      refreshSleepOriginTimestamp();
      break;
    case '7':
      Command_7(key);
      refreshSleepOriginTimestamp();
      break;
    case '8': // increment pas
      Command_8(key);
      refreshSleepOriginTimestamp();
      break;
    case '9': // Mode manuel 
      Command_9(key);
      refreshSleepOriginTimestamp();
      break;
    // case '0': Command_0(key); break;
    case 'A':
      Command_A(key);
      refreshSleepOriginTimestamp();
      break;
    case 'B':
      Command_B(key);
      refreshSleepOriginTimestamp();
      break;
    case 'C':
      Command_C(key);
      refreshSleepOriginTimestamp();
      break;
    case 'D':
      Command_D(key);
      refreshSleepOriginTimestamp();
      break;
      // default:
      //   Serial.print("DEFAULT key = ");
      //   Serial.println(key);
      //   break;
    }
  } // fin du if

  char key = keypad.getKey();
  switch (key)
  {
  case 'E':
    Command_E(key);
    refreshSleepOriginTimestamp();
    break;
  case 'F':
    Command_F(key);
    refreshSleepOriginTimestamp();
    break;
  }
}

void runCommandClavier()
{
  manageShortLongPressKey();
  manageKeyProtectedBySecurityButton();
}
