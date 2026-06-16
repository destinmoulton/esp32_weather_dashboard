//
// Created by destin on 6/8/26.
//

#pragma once
#include "TFT_eSPI.h"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

class Screen
{
protected:
    TFT_eSPI& m_tft;
    int m_centerX;
    int m_centerY;

public:
    explicit Screen(TFT_eSPI& tft);
    virtual void render();
    virtual void loop();
};
