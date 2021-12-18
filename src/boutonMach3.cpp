#include <Arduino.h>
#include <BleKeyboard.h>

#include "sleep.h"
#include "screen.h"
#include "boutonMach3.h"

// BleKeyboard Keyboard("ESP32 Bluetooth clavier", "Espressif", 80);
extern BleKeyboard Keyboard;

const unsigned antiRebond = 10;

const uint8_t NB_BUTTON = 3;

const uint8_t buttons[NB_BUTTON] = {PIN_ARRET_BT, PIN_PAUSE_BT, PIN_START_BT};

bool oldBtStatus[NB_BUTTON] = {1, 1, 1};
bool btStatus[NB_BUTTON] = {HIGH, HIGH, HIGH};
unsigned long lastAntiRebond[NB_BUTTON] = {0, 0, 0};

void checkMainBouton()
{
  btMach3(PIN_ARRET_BT);
  btMach3(PIN_PAUSE_BT);
  btMach3(PIN_START_BT);
}

/**
 * @brief Mise en someil leger
 *
 * @param GPIO 14 (bt secu)
 * @return
 */

// void dodo()
//   {
//     esp_sleep_enable_ext0_wakeup(GPIO_NUM_14,LOW);
//     int ret = esp_light_sleep_start();
//     screenSendMessage("Au Dodo...");
//     Serial.println(ret);
//   }

/**
 * @brief Get the Idx Button object
 *
 * @param buttonPinNb
 * @return int
 */

int getIdxButton(uint8_t buttonPinNb)
{
  for (int i = 0; i < NB_BUTTON; ++i)
  {
    if (buttonPinNb == buttons[i])
    {
      return i;
    }
  }
  return 0;
}

void btMach3(int pinNb)
{

  int lireBt = digitalRead(pinNb);
  // printf("PASS pinNb: %d\n", pinNb);
  // printf("PASS lireBt: %d\n", lireBt);
  int idx = getIdxButton(pinNb);
  // printf("idx %d\n", idx);
  if (lireBt != oldBtStatus[idx])
  {
    lastAntiRebond[idx] = millis();
  }
  // printf("PASS 1\n");
  if ((millis() - lastAntiRebond[idx]) > antiRebond)
  {
    // printf("PASS 2\n");
    if (btStatus[idx] != lireBt)
    {
      btStatus[idx] = lireBt;

      // printf("PASS 3\n");
      if (lireBt == LOW)
      {
        // printf("pinNb %d\n", pinNb);
        // printf("PIN_ARRET_BT %d\n", PIN_ARRET_BT);
        // printf("PIN_PAUSE_BT %d\n", PIN_PAUSE_BT);
        // printf("PIN_START_BT %d\n", PIN_START_BT);
        switch (pinNb)
        {
        case PIN_ARRET_BT:
          // printf("ARRET\n");
          screenSendMessage("  ARRET  ");
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press(115); // touche LEFT_ALT + touche "s" en minuscule
          delay(100);
          Keyboard.releaseAll();
          refreshSleepOriginTimestamp();
          break;
        case PIN_PAUSE_BT:
          // printf("PAUSE\n");
          screenSendMessage("  PAUSE  ");
          Keyboard.press(32); // touche BACKSPACE
          delay(100);
          Keyboard.releaseAll();
          refreshSleepOriginTimestamp();
          break;
        case PIN_START_BT:
          // printf("START\n");
          screenSendMessage("  START  ");
          Keyboard.press(KEY_LEFT_ALT);
          Keyboard.press(114); // touche LEFT_ALT + touche "r" en minuscule
          delay(100);
          Keyboard.releaseAll();
          refreshSleepOriginTimestamp();
          break;
        } // fin du switch
      }   // fin du 4eme if
    }     // fin du 3eme if
  }       // fin du 2eme if
  // printf("BEFORE WRITE\n");
  oldBtStatus[idx] = lireBt;
  // printf("AFTER WRITE\n");

  // printf("\n");
} // fin de la fonction
