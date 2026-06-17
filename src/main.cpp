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
#include "MicroSD.h"
#include "WifiInterface.h"

Display display;
WifiInterface wifi;
MicroSD sd;

void setup()
{
  Serial.begin(115200);

  wifi.connect();

  display.begin();

  sd.begin();
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
