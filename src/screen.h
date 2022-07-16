#pragma once

#include <Adafruit_SSD1306.h>

void initScreen();
void clearScreen();
void loopScreen();

void screenSendMessage(String message);

const int DISPLAY_DURATION = 5000;
