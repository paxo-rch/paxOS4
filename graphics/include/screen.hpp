#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "FS.h"
#include <SPI.h>
#include "../../libraries/TFT_eSPI/TFT_eSPI.h"

TFT_eSPI tft = TFT_eSPI();

#include <TJpg_Decoder.h>
#include "bitmap.hpp"

// Include SD
#include <FS.h>
#include "SPIFFS.h"

namespace quitt
{
    void draw()
    {
        tft.fillRoundRect(270, 2, 45, 25, 13, 0x8607);
        tft.setTextColor(0x0000);
        tft.drawCentreString("<-", 292, 4, 4);
    }
}

bool screenIsTouch();

#include "../src/screen.cpp"

#endif /* SCREEN_HPP */