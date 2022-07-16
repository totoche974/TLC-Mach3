#include <Arduino.h>

#include "boutonMach3.h"
#include "screen.h"
#include "sleep.h"
#include "lipo.h"

/**
 * @brief Durée avant mise en veille.
 *
 */
const int SLEEP_THRESHOLD = 5 * 60 * 1000; // 5 minutes
// const int SLEEP_THRESHOLD = 3000; // test 3 secondes

ulong lastActivityTimestamp = 0;

void setupWakeupBouton(const gpio_num_t gpio)
{
  esp_err_t pinSleepConfigResult = gpio_wakeup_enable(gpio, GPIO_INTR_LOW_LEVEL);

  switch (pinSleepConfigResult)
  {
  case ESP_OK:
    printf("%d: ESP_OK\n", gpio);
    break;
  case ESP_ERR_INVALID_ARG:
    printf("%d: ESP_ERR_INVALID_ARG\n", gpio);
    break;
  }
}

void initSleep()
{

  esp_err_t pinSleepEnableResult = esp_sleep_enable_gpio_wakeup();

  switch (pinSleepEnableResult)
  {
  case ESP_OK:
    printf("enable_gpio_wakeup: ESP_OK\n");
    break;
  case ESP_ERR_INVALID_STATE:
    printf("enable_gpio_wakeup: ESP_ERR_INVALID_STATE\n");
    break;
  }

  setupWakeupBouton(PIN_SECU_BT);
  setupWakeupBouton(PIN_START_BT);
  setupWakeupBouton(PIN_PAUSE_BT);
  setupWakeupBouton(PIN_ARRET_BT);
  setupWakeupBouton(PIN_BT_VISU_CHARGE_LIPO);

  lastActivityTimestamp = millis();
}

void refreshSleepOriginTimestamp()
{
  lastActivityTimestamp = millis();
}

void shouldSleep()
{

  ulong currentTimestamp = millis();
  ulong elapseTime = currentTimestamp - lastActivityTimestamp;

  if (SLEEP_THRESHOLD < elapseTime)
  {
    clearScreen();
    digitalWrite(PIN_LED_LIPO_ALERT, LOW);

    printf("START SLEEP\n");
    Serial.flush();

    setCpuFrequencyMhz(80);

    esp_light_sleep_start();
    refreshSleepOriginTimestamp();
    printf("WAKEUP\n");
    Serial.flush();
    screenSendMessage("  WAKEUP  ");

    setCpuFrequencyMhz(240);

    // printf("digitalRead(PIN_START_BT): %d\n", digitalRead(PIN_START_BT));
    // printf("digitalRead(PIN_PAUSE_BT): %d\n", digitalRead(PIN_PAUSE_BT));
    // printf("digitalRead(PIN_ARRET_BT): %d\n", digitalRead(PIN_ARRET_BT));
    // printf("digitalRead(PIN_SECU_BT): %d\n", digitalRead(PIN_SECU_BT));

    checkMainBouton();
  }
}
