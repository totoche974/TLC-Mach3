#include "lipo.h"
#include "screen.h"

SFE_MAX1704X lipo(MAX1704X_MAX17043);

long timestampOriginLipo;

void initLipo()
{
  // Uncomment this line to enable helpful debug messages on Serial
  // lipo.enableDebugging();

  // Set up the MAX17044 LiPo fuel gauge:
  const int NB_LIPO_CONNEXTION_ATTEMPT = 3;
  int lipo_connexion_attempt = 0;
  while (lipo.begin(Wire) == false)
  {
    ++lipo_connexion_attempt;
    if (NB_LIPO_CONNEXTION_ATTEMPT < lipo_connexion_attempt)
    {
      screenSendMessage("NO LIPO");
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