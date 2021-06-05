#pragma once

#ifndef _BOUTON_H
#define _BOUTON_H

#include <Arduino.h>

/**
     * @note Ajout de resistance de 10K pour passer les
     * pins 34 et 35 en PULLUP
     * 
     * Obligation d'appuyer sur le bouton (BT_SECU) pour pouvoir utiliser la manivelle  
     */

const uint8_t BT_SECU = 14; // pin 26 - GPIO14

const uint8_t Axe_X = 34; // pin 19 - GPIO34 - BT tester = OK
const uint8_t Axe_Y = 35; // pin 20 - GPIO35 - BT tester = OK
const uint8_t Axe_Z = 32; // pin 21 - GPIO32 - BT tester = OK
const uint8_t Axe_A = 33; // pin 22 - GPIO33 - BT tester = OK
//uint8_t Secu  = 3;

const uint8_t ARRET_BT = 25; //pin 23 - GPIO25 - BT tester = OK
const uint8_t PAUSE_BT = 26; //pin 24 - GPIO26 - BT tester = OK
const uint8_t START_BT = 27; //pin 25 - GPIO27 - BT tester = OK

#endif // _BOUTON_H