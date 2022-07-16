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

const double LIPO_THRESHOLD_ALERT = 20.0;
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

bool is_led_on = false;

void doBlink()
{

  long elapseTime = millis() - timestampOriginLipo;

  if (BLINK_DURATION < elapseTime)
  {
    is_led_on = !is_led_on;

    if (is_led_on)
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

// Etat du bouton poussoir
uint8_t boutonState = 0;       //état actuel du bouton poussoir
uint8_t boutonPushCounter = 0; // nombre d'appuis sur le bouton poussoir
uint8_t lastBoutonState = 0;   // Variable pour le précédent état du bouton poussoir

bool hasIncremented = false;
long lastChange = millis();

/**
 * @brief appui 1x sur bt poussoir affiche le voltage
 *        appui 2x sur bt poussoir affiche le % de charge
 *        appui 3x sur bt poussoir eteint l'afficheur
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
      boutonPushCounter++;
      hasIncremented = true;
      lastChange = millis();
      refreshSleepOriginTimestamp();
      // Serial.print("Appuyé :  ");
      // Serial.println(boutonPushCounter, DEC);
    }
    // mémorise l'état courant du bouton poussoir
    lastBoutonState = boutonState;
  }

  // affiche voltage de la batterie
  if (boutonPushCounter == 1)
  {
    if (hasIncremented)
    {
      char toPrint[50];
      sprintf(toPrint, "  %.2fV", lipo.getVoltage());
      screenSendMessage(toPrint);
    }
  }
  // affiche le % de charge de la batterie
  if (boutonPushCounter == 2)
  {
    if (hasIncremented)
    {
      char toPrint[50];
      sprintf(toPrint, "  %.2f %%", lipo.getSOC());
      screenSendMessage(toPrint);
    }
  }
  // nettoyer affichage
  if (boutonPushCounter == 3)
  {
    boutonPushCounter = 0;
    clearScreen();
  }

  hasIncremented = false;

  long elapseTime = millis() - lastChange;

  if (DISPLAY_DURATION < elapseTime)
  {
    boutonPushCounter = 0;
  }
}
