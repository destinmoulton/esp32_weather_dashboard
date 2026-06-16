//
// Created by destin on 6/8/26.
//

// Use custom setup file
// Original is: User_Setups/Setup42_ILI9341_ESP32.h

#define USER_SETUP_LOADED
#include "User_Setup.h"
#include "Screen.h"
#include "screens/Dashboard.h"
#include "Display.h"

Display::Display()
    : m_tft(),
      m_activeScreen(nullptr),
      m_screenClock(m_tft)
{
}


void Display::begin()
{
    // Start the tft display
    //m_tft.begin();
    m_tft.init();
    // Set the TFT display rotation in landscape mode
    m_tft.setRotation(1);
    m_tft.fillScreen(TFT_BLACK);
    m_tft.setTextColor(TFT_WHITE, TFT_BLACK);

    m_activeScreen = &m_screenClock;
}


void Display::loop()
{
    m_activeScreen->loop();
}



