#pragma once

#include <Adafruit_SSD1306.h>

void initScreen();
void clearDisplay();
void loopScreen();

enum TypeMessage
{
  Small,
  Big
};

void screenSendMessage(String message, TypeMessage type = TypeMessage::Big);
// void screenSendMessage(String message, TypeMessage type);
