#include <Arduino.h>
#include "cmdClavier.h"
#include "bouton.h"
#include <BleKeyboard.h>
#include <AiEsp32RotaryEncoder.h>

extern BleKeyboard Keyboard;
extern Manivelle MAN;
extern AiEsp32RotaryEncoder rotaryEncoder;

int previousEncoderPosition = 0;

const int KEY_2 = 50;
const int KEY_4 = KEY_LEFT_ARROW;  // 37; // KEY_LEFT_ARROW; //100; // 52; // X- : 100
const int KEY_6 = KEY_RIGHT_ARROW; // 39; // KEY_RIGHT_ARROW; // 102; // 54; // X+ : 102
const int KEY_8 = 56;

void manivelleInit()
{
  if (digitalRead(Axe_X) == LOW)
  {
    printf("Axe X\n");
    MAN.changeAxe = KEY_4;  // ACSII 4 : 52
    MAN.changeAxe1 = KEY_6; // ACSII 6 : 54
  }
  if (digitalRead(Axe_Y) == LOW)
  {
    printf("Axe Y\n");
    MAN.changeAxe = KEY_8;  // ACSII 8 : 56
    MAN.changeAxe1 = KEY_2; // ACSII 2 : 50
  }
  if (digitalRead(Axe_Z) == LOW)
  {
    printf("Axe Z\n");
    MAN.changeAxe = KEY_PAGE_UP;
    MAN.changeAxe1 = KEY_PAGE_DOWN;
  }
  if (digitalRead(Axe_A) == LOW)
  {
    printf("Axe A\n");
    MAN.changeAxe = KEY_HOME;
    MAN.changeAxe1 = KEY_END;
  }
}

void manivelle()
{
  //dont print anything unless value changed
  if (!rotaryEncoder.encoderChanged())
  {
    return;
  }
  manivelleInit();

  if (digitalRead(BT_SECU) == LOW)
  { // Touche Ctrl à droite ou à gauche
    int currentEncoderPosition = -rotaryEncoder.readEncoder();
    int deltaEncoder = currentEncoderPosition - previousEncoderPosition;
    if (deltaEncoder > 0)
    {

      printf("CodRotIncrement > 0\n");
      // Keyboard.press(KEY_LEFT_CTRL);
      printf("commande %d\n", MAN.changeAxe);
      // Keyboard.press(MAN.changeAxe);
      Keyboard.press(MAN.changeAxe);
      //delay(50);
      Keyboard.releaseAll();
    }
    else if (deltaEncoder < 0)
    {

      printf("CodRotIncrement < 0\n");
      // Keyboard.press(KEY_LEFT_CTRL);
      printf("commande %d\n", MAN.changeAxe1);
      // Keyboard.press(MAN.changeAxe);
      Keyboard.press(MAN.changeAxe1);
      //delay(50);
      Keyboard.releaseAll();
    }
    previousEncoderPosition = currentEncoderPosition;

    Serial.print("Value: ");
    Serial.println(-rotaryEncoder.readEncoder());
  }
}
