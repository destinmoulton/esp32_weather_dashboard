//
// Created by destin on 6/8/26.
//

#include "Screen.h"

#include "TFT_eSPI.h"

Screen::Screen(TFT_eSPI& tft)
    : m_tft(tft),
      m_centerX(SCREEN_WIDTH / 2),
      m_centerY(SCREEN_HEIGHT / 2)
{
}

void Screen::render()
{
}

void Screen::loop()
{
}

