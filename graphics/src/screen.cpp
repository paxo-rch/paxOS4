#ifndef SCREEN_CPP
#define SCREEN_CPP

#include "../include/screen.hpp"
#include "../graphics.hpp"

#include "../../hardware/hardware.hpp"



#define timeToWait 50

double lastClick = millis();
bool isPreviousTouch = 0;

void drawIsTouch(bool state)
{
    if (state && !isPreviousTouch)
    {
        isPreviousTouch = 1;
        tft.fillCircle(3, 3, 3, 0x8123);
    }
    if (!state && isPreviousTouch)
    {
        isPreviousTouch = 0;
        tft.fillCircle(3, 3, 3, 0xFFFF);
    }
}

#include "../../apps/apps.hpp"

void exitApp();

void checkExit()
{
    uint16_t tx, ty;
    tft.getTouch(&tx, &ty);
    if(270 < tx && tx < 320 && 0 < ty && ty < 25)
        exitApp();
}

bool screenIsTouch()
{
    uint16_t z = tft.getTouchRawZ();
    if (z > 1050 && z < 4000 && lastClick + timeToWait > millis())
    {
        lastClick = millis();
        drawIsTouch(1);
        checkExit();
        return 1;
    }
    if (z > 1050 && z < 4000)
    {
        lastClick = millis();
        drawIsTouch(1);
        checkExit();
        return 1;
    }
    if ((z < 4000 || z > 1050) && lastClick + timeToWait < millis())
    {
        drawIsTouch(0);
        return 0;
    }
    else
    {
        drawIsTouch(1);
        checkExit();
        return 1;
    }
}

void clearAllScreen(uint16_t color = 0xFFFF)
{
    tft.fillRect(0,0,15,15,0x0000);
    tft.fillRect(305,0,15,15,0x0000);
    tft.setTextSize(1);
    tft.fillRoundRect(0, 0, 320, 480, 20, color);
    tft.fillRoundRect(50, -20, 220, 45, 20, 0x0000);
    tft.fillRect(40, 0, 10, 10, 0x0000);
    tft.fillRect(270, 0, 10, 10, 0x0000);
    tft.fillCircle(37, 13, 13, color);
    tft.fillCircle(281, 13, 13, color);
    tft.setTextColor(0xFFFF);
    
    tft.drawCentreString("--:--", 160, -1, 4);
    //tft.drawCentreString("00:00", 160, -1, 4);

    quitt::draw();
    //TJpgDec.drawSdJpg(0, 0, "/paxo/usr/back.jpg");
    //bmpDrawSD("/paxo/usr/back.bmp", 1, 30);
}

#endif /* SCREEN_CPP */