
// #include <Arduino.h>
// #include <Keypad.h>
// #include <BleKeyboard.h>
#include <Keypad_I2C.h>
// #include "WiFi.h"

#include "setup_i2c.h"

// #include "screen.h"
// #include "boutonMach3.h"
// #include "sleep.h"
// #include "axe.h"

TwoWire *jwire = &Wire; // test passing pointer to keypad lib

void initI2C()
{
  jwire->setPins(PIN_SDA, PIN_SCL);
  jwire->begin();
  jwire->setClock(400000);
}