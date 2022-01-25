#ifndef KEYBOARD_CPP
#define KEYBOARD_CPP

#include "../../graphics/include/screen.hpp"

keyboard::keyboard(uint16_t textColor, uint16_t backgroundColor)
{
    tft.fillRoundRect(5, 250, 310, 200, 15, 0x4A69);
    for (byte j = 0; j < 3; j++)
    {
        for (byte i = 0; i < 10; i++)
        {
            tft.fillRoundRect(12 + i * 30, 253 + j * 40, 28, 35, 5, 0x7BEF);
            tft.setTextColor(0xFFFF);
            tft.drawCentreString(String(alphabet[j][i]), 26 + i * 30, 262 + j * 40, 4);
        }
    }

    tft.fillRoundRect(40, 373, 240, 35, 5, 0x9CF3);
    tft.setTextColor(0xFFFF);
    tft.drawCentreString("espace", 160, 382, 4);

    tft.fillRoundRect(290, 373, 28, 35, 5, 0x9CF3);
    tft.setTextColor(0xFFFF);
    tft.drawCentreString("S", 160, 382, 4);
}

void keyboard::draw()
{
    tft.fillRoundRect(5, 250, 310, 200, 15, 0x4A69);
    for (byte j = 0; j < 3; j++)
    {
        for (byte i = 0; i < 10; i++)
        {
            tft.fillRoundRect(12 + i * 30, 253 + j * 40, 28, 35, 5, 0x7BEF);
            tft.setTextColor(0xFFFF);
            tft.drawCentreString(String(alphabet[j][i]), 26 + i * 30, 262 + j * 40, 4);
        }
    }

    tft.fillRoundRect(40, 373, 240, 35, 5, 0x9CF3);
    tft.setTextColor(0xFFFF);
    tft.drawCentreString("espace", 160, 382, 4);

    tft.fillRoundRect(282, 373, 28, 35, 5, 0x9CF3);
    tft.setTextColor(0xFFFF);
    tft.drawCentreString("S", 296, 382, 4);
}

bool keyboard::isTouch()
{
    if(screenIsTouch())
    {
        uint16_t tx, ty = 0;
        tft.getTouch(&tx, &ty);

        for (byte j = 0; j < 3; j++)
        {
            for (byte i = 0; i < 10; i++)
            {
                if (12 + i * 30 < tx && tx < 40 + i * 30 && 253 + j * 40 < ty && ty < 288 + j * 40)
                {
                    tft.fillRoundRect(12 + i * 30, 253 + j * 40, 28, 35, 5, 0x9CF3);
                    tft.setTextColor(0xFFFF);
                    tft.drawCentreString(String(alphabet[j][i]), 26 + i * 30, 262 + j * 40, 4);
                    while(screenIsTouch());
                    tft.fillRoundRect(12 + i * 30, 253 + j * 40, 28, 35, 5, 0x7BEF);
                    tft.setTextColor(0xFFFF);
                    tft.drawCentreString(String(alphabet[j][i]), 26 + i * 30, 262 + j * 40, 4);
                    text+=alphabet[j][i];
                    return 1;
                }
            }
        }

        if (40 < tx && tx < 280 && 373 < ty && ty < 408)
        {
            tft.fillRoundRect(40, 373, 240, 35, 5, 0x9CF3);
            tft.setTextColor(0xFFFF);
            tft.drawCentreString("espace", 160, 382, 4);
            while(screenIsTouch());
            tft.fillRoundRect(40, 373, 240, 35, 5, 0x7BEF);
            tft.setTextColor(0xFFFF);
            tft.drawCentreString("espace", 160, 382, 4);
            text+=" ";
            return 1;
        }

        if (282 < tx && tx < 310 && 373 < ty && ty < 408)
        {
            tft.fillRoundRect(282, 373, 28, 35, 5, 0x9CF3);
            tft.setTextColor(0xFFFF);
            tft.drawCentreString("S", 296, 382, 4);
            while(screenIsTouch());
            tft.fillRoundRect(282, 373, 28, 35, 5, 0x7BEF);
            tft.setTextColor(0xFFFF);
            tft.drawCentreString("S", 296, 382, 4);
            text = text.substring(0, text.length() - 1);
            return 1;
        }

        tx, ty = 0;
    }
    return 0;
}

bool keyboard::isEnd()
{
    return 0;
}

String keyboard::getString()
{
    return text;
}

void keyboard::setString(String newString)
{
    text = newString;
}

#endif /* KEYBOARD_CPP */