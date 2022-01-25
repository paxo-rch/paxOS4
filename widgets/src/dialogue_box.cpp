#ifndef BOX_CPP
#define BOX_CPP

#include "../include/dialogue_box.hpp"

dialog_box::dialog_box(String title, byte option)
{
    this->title = title;
    this->option = option;

    byte sizeX = title.length() * 30;
    
    tft.fillRoundRect(x - sizeX, y, sizeX*2, 100, 20, 0xFFFF);
    tft.drawRoundRect(x - sizeX - 1, y - 1, sizeX*2 + 2, 100 + 2, 20, 0x1CFE);
    tft.setTextColor(0x1CFE);
    tft.drawCentreString(title, x, y + 10, 4);

    if (option == BOX_OK)
    {
        tft.drawLine(x - sizeX, y + 50, x + sizeX, y + 50, 0x1CFE);
        tft.setTextColor(0x1CFE);
        tft.drawCentreString("Ok", x, y + 60, 4);
    }
    if (option == BOX_YES_NO)
    {
        tft.drawLine(x - sizeX, y + 50, x + sizeX, y + 50, 0x1CFE);
        tft.drawLine(x, y + 50, x, y + 100, 0x1CFE);
        tft.setTextColor(0x1CFE);
        tft.drawCentreString("Oui", x - sizeX/2, y + 60, 4);
        tft.drawCentreString("Non", x + sizeX/2, y + 60, 4);
    }
}

dialog_box::dialog_box(String title, byte option, uint16_t x, uint16_t y)
{
    this->title = title;
    this->option = option;
    this->x = x;
    this->y = y;

    byte sizeX = title.length() * 30;

    tft.fillRoundRect(x - sizeX, y, sizeX*2, sizeX, 20, 0xFFFF);
    tft.drawRoundRect(x - sizeX - 1, y - 1, sizeX*2 + 2, 100 + 2, 20, 0x1CFE);
    tft.drawCentreString(title, x, y + 10, 4);

    if (option == BOX_OK)
    {
        tft.drawLine(x - sizeX, y + 50, x + sizeX, y + 50, 0x1CFE);
        tft.setTextColor(0x1CFE);
        tft.drawCentreString("Ok", x, y + 60, 4);
    }

    if (option == BOX_YES_NO)
    {
        tft.drawLine(x - sizeX, y + 50, x + sizeX, y + 50, 0x1CFE);
        tft.drawLine(x, y + 50, x, y + 100, 0x1CFE);
        tft.setTextColor(0x1CFE);
        tft.drawCentreString("Oui", x - sizeX/2, y + 60, 4);
        tft.drawCentreString("Non", x + sizeX/2, y + 60, 4);
    }
}

byte dialog_box::getOption()
{
    while(1) 
    {
        while (!screenIsTouch());
        byte sizeX = title.length() * 30;
        
        uint16_t tx, ty;
        tft.getTouch(&tx, &ty);

        if (option == BOX_OK && x - sizeX < tx && tx < x + sizeX && y + 50 < ty && ty < y + 100)
        {
            return BOX_OK;
        }

        if (option == BOX_YES_NO)
        {
            if (x - sizeX < tx && tx < x && y + 50 < ty && ty < y + 100)
                return BOX_YES;
            if (x < tx && tx < x + sizeX && y + 50 < ty && ty < y + 100)
                return BOX_NO;
        }
    }  
}

#endif