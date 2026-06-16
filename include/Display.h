//
// Created by destin on 6/8/26.
//

#pragma once

#include <TFT_eSPI.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include "Screen.h"
#include "screens/Dashboard.h"


// Touchscreen pins
#define XPT2046_IRQ 36   // T_IRQ
#define XPT2046_MOSI 32  // T_DIN
#define XPT2046_MISO 39  // T_OUT
#define XPT2046_CLK 25   // T_CLK
#define XPT2046_CS 33    // T_CS

//SPIClass touchscreenSPI = SPIClass(VSPI);
//XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

#define FONT_SIZE 4

class Display
{
private:
    TFT_eSPI m_tft;
    Screen* m_activeScreen;
    Dashboard m_screenClock;

public:
    Display();
    void begin();
    void loop();
};
