
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
  // display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
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

  clearDisplay();
}

// *** Clear the screen
void clearDisplay()
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
TypeMessage typeMessage;

// void screenSendMessage(String message, TypeMessage type = TypeMessage::Big)
void screenSendMessage(String message, TypeMessage type)
{
  startMessage = millis();
  messageToPrint = message;
  typeMessage = type;
}

bool isDisplaying = false;

void loopScreen()
{
  if (!messageToPrint.isEmpty())
  {
    if (!isDisplaying)
    {
      display->clearDisplay();

      switch (typeMessage)
      {
      case TypeMessage::Small:
      {
        display->setTextSize(2); // Draw 1X-scale text
        display->startscrollleft(0x00, 0x0F);
        display->setCursor(0, 16);
        break;
      }
      case TypeMessage::Big:
      {
        display->setTextSize(2); // Draw 2X-scale text
        display->stopscroll();
        display->setCursor(0, 16);
        break;
      }
      }

      display->setTextColor(SSD1306_WHITE);
      display->println(F(messageToPrint.c_str()));
      display->display(); // Show initial text
      isDisplaying = true;
    }
  }

  else
  {
    display->clearDisplay();
    display->display();
    isDisplaying = false;
  }

  long elapseTime = millis() - startMessage;

  if (5000 < elapseTime)
  {
    messageToPrint = "";
  } // Délai d'affichage du message limité à 5 secondes
}
