#ifndef BUTTON_CPP
#define BUTTON_CPP

#include "../../graphics/include/screen.hpp"

button::button(int centerX, int centerY, String text, uint16_t colorPress, uint16_t colorNotPress)
{
    this->centerX = centerX;
    this->centerY = centerY;
    this->colorPress = colorPress;
    this->colorNotPress = colorNotPress;
    isColorThemeEnable = 0;
    this->text = text;
}

button::button(int centerX, int centerY, String text, uint16_t colorPress, uint16_t colorNotPress, bool (*whenPress)())
{
    this->centerX = centerX;
    this->centerY = centerY;
    this->colorPress = colorPress;
    this->colorNotPress = colorNotPress;
    isColorThemeEnable = 0;
    this->text = text;
    this->whenPress = whenPress;
}

button::button(int centerX, int centerY, String text, uint16_t colorTheme)
{
    this->centerX = centerX;
    this->centerY = centerY;
    this->colorTheme = colorTheme;
    isColorThemeEnable = 1;
    this->text = text;
}

button::button(int centerX, int centerY, String text, uint16_t colorTheme, bool (*whenPress)())
{
    this->centerX = centerX;
    this->centerY = centerY;
    this->colorTheme = colorTheme;
    isColorThemeEnable = 1;
    this->text = text;
    this->whenPress = whenPress;
}

void button::draw()
{
    if (isColorThemeEnable)
        tft.fillRoundRect(centerX - getLengthOfText() / 2, centerY, getLengthOfText(), 30, 7, colorTheme);
    else
        tft.fillRoundRect(centerX - getLengthOfText() / 2, centerY, getLengthOfText(), 30, 7, colorNotPress);

    tft.setTextColor(0x0000);
    tft.drawCentreString(text, centerX, centerY + 2, 4);
}

bool button::isFocused()
{
    uint16_t tx, ty;
    tft.getTouch(&tx, &ty);
    if (centerX - getLengthOfText() / 2 < tx && tx < centerX + getLengthOfText() / 2 && centerY < ty && ty < centerY + 30 && screenIsTouch())
        return 1;
    return 0;
}

void button::changeText(String text)
{
    this->text = text;
}

void button::changeColor(uint16_t colorPress, uint16_t colorNotPress)
{
    this->colorPress = colorPress;
    this->colorNotPress = colorNotPress;
}

void button::changeColor(uint16_t colorTheme)
{
    this->colorTheme = colorTheme;
}

void button::changePosition(int centerX, int centerY)
{
    this->centerX = centerX;
    this->centerY = centerY;
}

uint16_t button::getLengthOfText()
{
    return (this->text.length()) * 22;
}

String button::getText()
{
    return text;
}

void button::getPosition(uint16_t *centerX, uint16_t *centerY)
{
    *centerX = this->centerX;
    *centerY = this->centerY;
}

bool button::isTouch()
{
    uint16_t tx, ty;
    tft.getTouch(&tx, &ty);
    bool touch = screenIsTouch();
    if (centerX - getLengthOfText() / 2 < tx && tx < centerX + getLengthOfText() / 2 && centerY < ty && ty < centerY + 30 && touch)
    {
        if (isColorThemeEnable)
            tft.fillRoundRect(centerX - getLengthOfText() / 2, centerY, getLengthOfText(), 30, 7, colorTheme);
        else
            tft.fillRoundRect(centerX - getLengthOfText() / 2, centerY, getLengthOfText(), 30, 7, colorPress);

        tft.setTextColor(0x0000);
        tft.drawCentreString(text, centerX, centerY + 2, 4);

        while (screenIsTouch())
        {
        }

        if (isColorThemeEnable)
            tft.fillRoundRect(centerX - getLengthOfText() / 2, centerY, getLengthOfText(), 30, 7, colorTheme);
        else
            tft.fillRoundRect(centerX - getLengthOfText() / 2, centerY, getLengthOfText(), 30, 7, colorNotPress);

        tft.setTextColor(0x0000);
        tft.drawCentreString(text, centerX, centerY + 2, 4);
        return 1;
    }
    return 0;
}

#endif /* BUTTON_CPP */