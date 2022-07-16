/**
 * @file lipo.cpp
 * @author Frozar, Gilles
 * @brief Télécommande bluetooth pour mach3
 */

#include "lipo.h"
#include "screen.h"
#include "sleep.h"

SFE_MAX1704X lipo(MAX1704X_MAX17043);

long timestampOriginLipo;

void initLipo()
{
  // Uncomment this line to enable helpful debug messages on Serial
  // lipo.enableDebugging();

  // Set up the MAX17043 LiPo fuel gauge:
  const int NB_LIPO_CONNEXTION_ATTEMPT = 3;
  int lipo_connexion_attempt = 0;
  while (lipo.begin(Wire) == false)
  {
    ++lipo_connexion_attempt;
    if (NB_LIPO_CONNEXTION_ATTEMPT < lipo_connexion_attempt)
    {
      screenSendMessage(" NO LIPO ");
      break;
    }
  }

  // Quick start restarts the MAX17044 in hopes of getting a more accurate
  // guess for the SOC.
  lipo.quickStart();

  timestampOriginLipo = millis();
}

/**
 * @var const double LIPO_THRESHOLD_ALERT
 * @brief Seuil d'alert pour le niveau de charge de la batterie
 */
const double LIPO_THRESHOLD_ALERT = 20.0;

/**
 * @var const int BLINK_DURATION
 * @brief Durée du clignotement de la LED d'alerte
 */
const int BLINK_DURATION = 500;

void doBlink();

void ledAlertShouldBlink()
{
  if (lipo.getSOC() < LIPO_THRESHOLD_ALERT)
  {
    doBlink();
  }
  else
  {
    digitalWrite(PIN_LED_LIPO_ALERT, LOW);
  }
}

bool ledState = false;

void doBlink()
{
  long elapseTime = millis() - timestampOriginLipo;

  if (BLINK_DURATION < elapseTime)
  {
    ledState = !ledState;

    if (ledState)
    {
      digitalWrite(PIN_LED_LIPO_ALERT, HIGH);
    }
    else
    {
      digitalWrite(PIN_LED_LIPO_ALERT, LOW);
    }

    timestampOriginLipo = millis();
  }
}

/**
 * @var uint8_t boutonState
 * @brief Etat du bouton poussoir
 */
uint8_t boutonState = 0;
/**
 * @var uint8_t boutonPushCounter
 * @brief Nombre d'appuis sur le bouton poussoir
 */
uint8_t boutonPushCounter = 0;
/**
 * @var uint8_t lastBoutonState
 * @brief Variable pour le précédent état du bouton poussoir
 */
uint8_t lastBoutonState = 0;

/**
 * @var bool hasIncremented
 * @brief Variable qui détecte les changements d'état du bouton poussoir
 */
bool hasIncremented = false;
/**
 * @var long lastChange
 * @brief Chronomètre le temps écoulé depuis le dernier changement d'état
 */
long lastChange = millis();

/**
 * @brief Affiche le voltage et charge restante de la batterie
 *
 * En fonction du nombre d'appuis sur le bouton poussoir :
 *  - appui 1x : affiche le voltage
 *  - appui 2x : affiche le % de charge
 *  - appui 3x : eteint l'afficheur
 */
void boutonVisuChargeLipo()
{
  // lit l'état actuel du bouton poussoir
  boutonState = digitalRead(PIN_BT_VISU_CHARGE_LIPO);

  if (boutonState != lastBoutonState)
  {
    // si état du bouton poussoir change vers le HAUT, on incrémente la variable de comptage
    if (boutonState == LOW)
    {
      boutonPushCounter = (boutonPushCounter + 1) % 3;
      hasIncremented = true;
      lastChange = millis();
      refreshSleepOriginTimestamp();
      // Serial.print("Appuyé :  ");
      // Serial.println(boutonPushCounter, DEC);
    }
    // mémorise l'état courant du bouton poussoir
    lastBoutonState = boutonState;
  }

  switch (boutonPushCounter)
  {
    // nettoyer affichage
  case 0:
  {
    if (hasIncremented)
    {
      clearScreen();
    }
    break;
  }
    // affiche voltage de la batterie
  case 1:
  {
    if (hasIncremented)
    {
      char toPrint[50];
      sprintf(toPrint, "  %.2fV", lipo.getVoltage());
      screenSendMessage(toPrint);
    }
    break;
  }
    // affiche le % de charge de la batterie
  case 2:
  {
    if (hasIncremented)
    {
      char toPrint[50];
      sprintf(toPrint, "  %.2f %%", lipo.getSOC());
      screenSendMessage(toPrint);
    }
    break;
  }
  }

  hasIncremented = false;

  long elapseTime = millis() - lastChange;

  if (DISPLAY_DURATION < elapseTime)
  {
    boutonPushCounter = 0;
  }
}
