#ifndef TEXT_CPP
#define TEXT_CPP

#include "text.h"

void setText::printRectText(String text)
{
    tft.setColor(r, g, b);
    tft.fillRoundRect(posx, posy, posx + sizex, posy + sizey);
    tft.setColor(0, 0, 0);
    setSize(2);
    tft.setCursor((posx + sizex / 2) - text.length() * 6, (posy + sizey / 2) + 9);
    tft.println(text);
}

printRectText::printRectText(short px, short py, short sx, short sy, short red, short green, short blue)
{
    posx = px;
    posy = py;
    sizex = sx;
    sizey = sy;
    r = red;
    g = green;
    b = blue;
    tft.fillRoundRect(posx, posy, posx + sizex, posy + sizey, 10, color565(r, g, b));
}

#endif