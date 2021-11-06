#include <Arduino.h>
#include <BleKeyboard.h>
#include <AiEsp32RotaryEncoder.h>

#include "boutonMach3.h"
#include "selector.h"
#include "screen.h"

extern BleKeyboard Keyboard;

#define ROTARY_ENCODER_A_PIN 19      // 32
#define ROTARY_ENCODER_B_PIN 18      // 21
#define ROTARY_ENCODER_BUTTON_PIN -1 // 25
#define ROTARY_ENCODER_VCC_PIN -1    /* 27 put -1 of Rotary encoder Vcc is connected directly to 3,3V; else you can use declared output pin for powering rotary encoder */

#define ROTARY_ENCODER_STEPS 4

// extern BleKeyboard Keyboard;

//instead of changing here, rather change numbers above
AiEsp32RotaryEncoder rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN,
                                                          ROTARY_ENCODER_BUTTON_PIN, ROTARY_ENCODER_VCC_PIN,
                                                          ROTARY_ENCODER_STEPS);

void initManivelle()
{
  //we must initialize rotary encoder
  rotaryEncoder.begin();

  rotaryEncoder.setup(
      []
      {
        rotaryEncoder.readEncoder_ISR();
      },
      [] {});

  rotaryEncoder.setAcceleration(250);
}

int previousEncoderPosition = 0;

// const int KEY_2 = 50;
// const int KEY_4 = KEY_LEFT_ARROW;  // 37; // KEY_LEFT_ARROW; //100; // 52; // X- : 100
// const int KEY_6 = KEY_RIGHT_ARROW; // 39; // KEY_RIGHT_ARROW; // 102; // 54; // X+ : 102
// const int KEY_8 = 56;

const int KEY_2 = KEY_DOWN_ARROW;  // 40;
const int KEY_4 = KEY_LEFT_ARROW;  // 37; // KEY_LEFT_ARROW; //100; // 52; // X- : 100
const int KEY_6 = KEY_RIGHT_ARROW; // 39; // KEY_RIGHT_ARROW; // 102; // 54; // X+ : 102
const int KEY_8 = KEY_UP_ARROW;    // 38;

enum Axe
{
  Axe_x,
  Axe_y,
  Axe_z,
  Axe_a
};

Axe selectedAxe = Axe_x;
uint8_t selectedAxePositiveKey;
uint8_t selectedAxeNegativeKey;

void printAxe()
{
  switch (selectedAxe)
  {
  case Axe_x:
    printf("Axe X\n");
    screenSendMessage("Axe X");
    break;
  case Axe_y:
    printf("Axe Y\n");
    screenSendMessage("Axe Y");
    break;
  case Axe_z:
    printf("Axe Z\n");
    screenSendMessage("Axe Z");
    break;
  case Axe_a:
    printf("Axe A\n");
    screenSendMessage("Axe A");
    break;
  }
}

void selectAxe()
{
  if ((digitalRead(PIN_AXE_X) == LOW) && selectedAxe != Axe_x)
  {
    selectedAxePositiveKey = KEY_4; // ACSII 4 : 52
    selectedAxeNegativeKey = KEY_6; // ACSII 6 : 54
    selectedAxe = Axe_x;
    printAxe();
  }
  if ((digitalRead(PIN_AXE_Y) == LOW) && selectedAxe != Axe_y)
  {
    selectedAxePositiveKey = KEY_8; // ACSII 8 : 56
    selectedAxeNegativeKey = KEY_2; // ACSII 2 : 50
    selectedAxe = Axe_y;
    printAxe();
  }
  if ((digitalRead(PIN_AXE_Z) == LOW) && selectedAxe != Axe_z)
  {
    selectedAxePositiveKey = KEY_PAGE_UP;
    selectedAxeNegativeKey = KEY_PAGE_DOWN;
    selectedAxe = Axe_z;
    printAxe();
  }
  if ((digitalRead(PIN_AXE_A) == LOW) && selectedAxe != Axe_a)
  {
    selectedAxePositiveKey = KEY_HOME;
    selectedAxeNegativeKey = KEY_END;
    selectedAxe = Axe_a;
    printAxe();
  }
}

void manivelle()
{
  selectAxe();

  int currentEncoderPosition = -rotaryEncoder.readEncoder();
  int deltaEncoder = currentEncoderPosition - previousEncoderPosition;
  if (digitalRead(PIN_SECU_BT) == LOW)
  { // Touche Ctrl à droite ou à gauche
    if (deltaEncoder != 0)
    {
      printAxe();
      printf("deltaEncoder: %d\n", deltaEncoder);
    }
    if (deltaEncoder > 0)
    {

      printf("CodRotIncrement > 0\n");
      // Keyboard.press(KEY_LEFT_CTRL);
      printf("commande %d\n\n", selectedAxePositiveKey);
      Keyboard.press(selectedAxePositiveKey);
      delay(50);
      Keyboard.releaseAll();
    }
    else if (deltaEncoder < 0)
    {

      printf("CodRotIncrement < 0\n");
      // Keyboard.press(KEY_LEFT_CTRL);
      printf("commande %d\n\n", selectedAxeNegativeKey);
      Keyboard.press(selectedAxeNegativeKey);
      delay(50);
      Keyboard.releaseAll();
    }
  }
  previousEncoderPosition = currentEncoderPosition;
}
