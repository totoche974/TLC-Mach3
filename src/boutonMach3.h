#pragma once
#include <Arduino.h>

// LOW: 0
// HIGH: 1

/**
 * @note Obligation d'appuyer sur le bouton (PIN_SECU_BT) pour pouvoir utiliser la manivelle
 */
const gpio_num_t PIN_SECU_BT = GPIO_NUM_33;

const gpio_num_t PIN_ARRET_BT = GPIO_NUM_15;
const gpio_num_t PIN_PAUSE_BT = GPIO_NUM_32;
const gpio_num_t PIN_START_BT = GPIO_NUM_14;

void IRAM_ATTR btMach3(int pinNb);

void checkMainBouton();
