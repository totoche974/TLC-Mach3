#pragma once
#include <Arduino.h>

// uint8_t

const uint8_t ROTARY_ENCODER_A_PIN = GPIO_NUM_12; // 32
const uint8_t ROTARY_ENCODER_B_PIN = GPIO_NUM_13; // 21
const uint8_t ROTARY_ENCODER_BUTTON_PIN = -1;     // 25
const uint8_t ROTARY_ENCODER_VCC_PIN = -1;        /* 27 put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */

void initManivelle();
void manivelle();
