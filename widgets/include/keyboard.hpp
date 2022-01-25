#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "../../graphics/graphics.hpp"


class keyboard
{
public:
    keyboard(uint16_t textColor, uint16_t backgroundColor);

    bool isTouch();

    void draw();

    bool isEnd();

    String getString();

    void setString(String newString);

private:
    char* alphabet[3] = {
        {"azertyuiop"},
        {"qsdfghjklm"},
        {"wxcvbn,.?!"}
    };
    String text;
    uint16_t textColor, backgroundColor;
};

#include "../src/keyboard.cpp"

#endif /* KEYBOARD_HPP */