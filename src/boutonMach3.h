#pragma once
#include <Arduino.h>

// LOW: 0
// HIGH: 1

/**
 * @note Ajout de resistance de 10K pour passer les pins 34 et 35 en PULLUP
 *
 * Obligation d'appuyer sur le bouton (PIN_SECU_BT) pour pouvoir utiliser la manivelle
 */
const gpio_num_t PIN_SECU_BT = GPIO_NUM_14; // pin 26 - GPIO14

const gpio_num_t PIN_ARRET_BT = GPIO_NUM_25; // pin 23 - GPIO25 - BT tester = OK
const gpio_num_t PIN_PAUSE_BT = GPIO_NUM_26; // pin 24 - GPIO26 - BT tester = OK
const gpio_num_t PIN_START_BT = GPIO_NUM_27; // pin 25 - GPIO27 - BT tester = OK

void IRAM_ATTR btMach3(int pinNb);

void checkMainBouton();
