#pragma once

#include <Adafruit_SSD1306.h>

void initScreen();
void clearDisplay();
void loopScreen();

void screenSendMessage(String message);
