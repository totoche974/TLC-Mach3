#include <Arduino.h>
#include "cmdClavier.h"
#include "bouton.h"
#include <BleKeyboard.h>
#include <AiEsp32RotaryEncoder.h>

extern BleKeyboard Keyboard;
// extern Manivelle MAN;
extern AiEsp32RotaryEncoder rotaryEncoder;

int previousEncoderPosition = 0;

const int KEY_2 = 50;
const int KEY_4 = KEY_LEFT_ARROW;  // 37; // KEY_LEFT_ARROW; //100; // 52; // X- : 100
const int KEY_6 = KEY_RIGHT_ARROW; // 39; // KEY_RIGHT_ARROW; // 102; // 54; // X+ : 102
const int KEY_8 = 56;

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
    break;
  case Axe_y:
    printf("Axe Y\n");
    break;
  case Axe_z:
    printf("Axe Z\n");
    break;
  case Axe_a:
    printf("Axe A\n");
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

  if (digitalRead(PIN_SECU_BT) == LOW)
  { // Touche Ctrl à droite ou à gauche
    int currentEncoderPosition = -rotaryEncoder.readEncoder();
    int deltaEncoder = currentEncoderPosition - previousEncoderPosition;
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
    previousEncoderPosition = currentEncoderPosition;

    // Serial.print("Value: ");
    // Serial.println(-rotaryEncoder.readEncoder());
  }
}
