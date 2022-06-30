#include "lipo.h"
#include "screen.h"

SFE_MAX1704X lipo(MAX1704X_MAX17043);
extern SFE_MAX1704X lipo;

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
int boutonState = 0;       //état actuel du bouton poussoir
int boutonPushCounter = 0; // nombre d'appuis sur le bouton poussoir
int lastBoutonState = 0;   // Variable pour le précédent état du bouton poussoir

void boutonVisuChargeLipo()
{
  /**
   * @brief appui court sur bt poussoir affiche le voltage
   *        appui long sur bt poussoir affiche le % restant
   *
   */
  // lit l'état actuel du bouton poussoir
  boutonState = digitalRead(PIN_BT_VISU_CHARGE_LIPO);

  if (boutonState != lastBoutonState)
  {
    // si état du bouton poussoir change vers le HAUT, on incrémente la variable de comptage
    if (boutonState == HIGH)
    {
      // si l'état actuel du bouton est HAUT
      boutonPushCounter++;
    }
    // mémorise l'état courant du bouton poussoir
    lastBoutonState = boutonState;
  }
  // affiche voltage et % batterie
  if (boutonPushCounter % 2 == 0)
  { // affiche le voltage
    char toPrint[50];
    sprintf(toPrint, "  %.2fV", lipo.getVoltage());
    screenSendMessage(toPrint, TypeMessage::Small);
  }
  else
  { // affiche le %
    char toPrint[50];
    sprintf(toPrint, "  %.2f %%", lipo.getSOC());
    screenSendMessage(toPrint, TypeMessage::Small);
  }
}