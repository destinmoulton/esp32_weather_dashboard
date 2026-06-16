/**
 * main.cpp
 * ESP32 · LovyanGFX · LVGL v8
 *
 * Displays a simple "Contact" form with:
 *   • Name    – text input
 *   • Email   – text input
 *   • Message – multi-line text area
 *   • Submit  – button that pops a confirmation message box
 *
 * The on-screen LVGL keyboard appears whenever a text area is focused and
 * dismisses automatically when the user presses the LVGL ✓ key.
 */

#include <Arduino.h>

#include "Display.h"
#include "WifiInterface.h"

Display display;
WifiInterface wifi;

void setup()
{
  Serial.begin(115200);

  // Start the SPI for the touchscreen and init the touchscreen
  //touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  //touchscreen.begin();
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
  //touchscreen.setRotation(1);

  wifi.connect();

  display.begin();
  //
  //tft.drawLine(10, 10, 100, 10, TFT_WHITE);  // Draw a white line
  //tft.drawRect(10, 20, 50, 30, TFT_RED);     // Draw a red rectangle
  //tft.fillRect(70, 20, 50, 30, TFT_GREEN);   // Draw a filled green rectangle
  //tft.drawCircle(50, 100, 20, TFT_YELLOW);   // Draw a yellow circle
  //tft.fillCircle(100, 100, 20, TFT_BLUE);    // Draw a filled blue circle

  // Set X and Y coordinates for center of display

  //tft.drawCentreString("Touch screen to test", centerX, centerY, FONT_SIZE);
}

void loop()
{
  display.loop();
  // Checks if Touchscreen was touched, and prints X, Y and Pressure (Z) info on the TFT display and Serial Monitor
  /*
  if (touchscreen.tirqTouched() && touchscreen.touched()) {
    // Get Touchscreen points
    TS_Point p = touchscreen.getPoint();
    // Calibrate Touchscreen points with map function to the correct width and height
    x = map(p.x, 200, 3700, 1, SCREEN_WIDTH);
    y = map(p.y, 240, 3800, 1, SCREEN_HEIGHT);
    z = p.z;

    printTouchToSerial(x, y, z);
    printTouchToDisplay(x, y, z);

    delay(100);
  }
  */
}
