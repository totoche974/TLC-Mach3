#pragma once

#ifndef _SELECTOR_H
#define _SELECTOR_H

#include <Arduino.h>

/**
 * @note Obligation d'appuyer sur le bouton (PIN_SECU_BT) pour pouvoir utiliser la manivelle
 *  
 */

const uint8_t PIN_AXE_X = GPIO_NUM_5;
const uint8_t PIN_AXE_Y = GPIO_NUM_18;
const uint8_t PIN_AXE_Z = GPIO_NUM_19;
const uint8_t PIN_AXE_A = GPIO_NUM_21;

#endif // _SELECTOR_H
