#ifndef shell_CPP
#define shell_CPP

#include "../../graphics/graphics.hpp"


void shell::addLine(String line)
{
    text+=line;
    int counterLine = 0;
    int counterChar = text.length();

    for(; counterLine < 20; counterChar--)
    {
        if (text.charAt(counterChar) == '\n')
        {
            counterLine++;
        }

        if (counterChar == 0) break;
    }
    tft.setTextColor(0xFFFF);
    int counter_Y = 0;
    for (int i=counterChar; i != text.length(); i++)
    {
        if (text.charAt(i) == '\n')
        {
            tft.fillRect(0, counter_Y +40, 320, 20, 0x0000);
            tft.drawString(text.substring(counterChar+1, i+1),10,40 + counter_Y,4);
            counter_Y+=20;
            counterChar = i;
        }
    }
}

void shell::getKeyboard()
{

}

#endif