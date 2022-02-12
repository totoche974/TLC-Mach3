
#pragma once

#ifndef _SETUP_I2C_H
#define _SETUP_I2C_H

#include <Arduino.h>

const int PIN_SDA = (int)GPIO_NUM_23;
const int PIN_SCL = (int)GPIO_NUM_22;

void initI2C();

#endif // _SETUP_I2C_H
