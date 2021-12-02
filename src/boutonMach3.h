#pragma once
#include <Arduino.h>

void IRAM_ATTR btMach3(uint8_t pinNb);

/**
     * @note Ajout de resistance de 10K pour passer les
     * pins 34 et 35 en PULLUP
     * 
     * Obligation d'appuyer sur le bouton (PIN_SECU_BT) pour pouvoir utiliser la manivelle  
     */

const uint8_t PIN_SECU_BT = 14 ; // pin 26 - GPIO14

const uint8_t PIN_ARRET_BT = 25; //pin 23 - GPIO25 - BT tester = OK
const uint8_t PIN_PAUSE_BT = 26; //pin 24 - GPIO26 - BT tester = OK
const uint8_t PIN_START_BT = 27; //pin 25 - GPIO27 - BT tester = OK