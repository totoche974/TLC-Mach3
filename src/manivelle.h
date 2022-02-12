#pragma once
#include <Arduino.h>

// uint8_t

const uint8_t ROTARY_ENCODER_A_PIN = GPIO_NUM_21;
const uint8_t ROTARY_ENCODER_B_PIN = GPIO_NUM_17;
const uint8_t ROTARY_ENCODER_BUTTON_PIN = -1;
/* put -1 of Rotary encoder Vcc is connected directly to 3,3V;
   else you can use declared output pin for powering rotary encoder */
const uint8_t ROTARY_ENCODER_VCC_PIN = -1;

void initManivelle();
void manivelle();
