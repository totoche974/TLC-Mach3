
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "screen.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
//#define OLED_RESET 4        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

extern Adafruit_SSD1306 *display;

// *** Initialise the screen
void initScreen()
{
  display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

  if (!display->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display->display();
  delay(2000); // Pause de 2 seconds

  clearScreen();
}

// *** Clear the screen
void clearScreen()
{
  // Clear the buffer
  display->clearDisplay();

  display->display();
}

// long chronos;
long startMessage;
String messageToPrint;
String messageToPrintLigne1;
String messageToPrintLigne2;

bool isDisplaying = false;
bool hasUpdate = false;

void screenSendMessage(String message)
{
  startMessage = millis();
  messageToPrint = message;
  hasUpdate = true;
}

void displayMessage()
{
  display->clearDisplay();

  display->setTextSize(2); // Draw 2X-scale text
  display->stopscroll();
  display->setCursor(0, 16);

  display->setTextColor(SSD1306_WHITE);
  display->println(F(messageToPrint.c_str()));
  display->display(); // Show initial text
  isDisplaying = true;
  hasUpdate = false;
}

void loopScreen()
{
  long elapseTime = millis() - startMessage;

  if (DISPLAY_DURATION < elapseTime)
  {
    messageToPrint = "";

    display->clearDisplay();
    display->display();
    display->stopscroll();
    isDisplaying = false;
  }
  else if (!messageToPrint.isEmpty())
  {
    if (!isDisplaying)
    {
      displayMessage();
    }
    else
    {
      if (hasUpdate)
      {
        displayMessage();
      }
    }
  }
}
