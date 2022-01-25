#ifndef DEF_BUTTON
#define DEF_BUTTON

#include "../../graphics/include/screen.hpp"
#include "GUI.hpp"

class button
{
public:
    button(int centerX, int centerY, String text, uint16_t colorPress, uint16_t colorNotPress);
    button(int centerX, int centerY, String text, uint16_t colorPress, uint16_t colorNotPress, bool (*whenPress)());
    button(int centerX, int centerY, String text, uint16_t colorTheme);
    button(int centerX, int centerY, String text, uint16_t colorTheme, bool (*whenPress)());

    void changeText(String text);
    void changeColor(uint16_t colorPress, uint16_t colorNotPress);
    void changeColor(uint16_t colorTheme);
    void changePosition(int centerX, int centerY);

    void draw();
    bool isFocused();

    String getText();
    void getPosition(uint16_t *centerX, uint16_t *centerY);
    bool isTouch();
    bool isTouch(uint16_t X, uint16_t Y);

private:
    uint16_t getLengthOfText();

    String text = "";
    bool (*whenPress)() = NULL;
    uint16_t colorTheme = 0xFFFF;
    bool isColorThemeEnable = 0;
    uint16_t colorPress, colorNotPress = 0xFFFF;
    int centerX, centerY;
};

#include "../src/button.cpp"

#endif
