#ifndef BOX_HPP
#define BOX_HPP

#include "../../graphics/include/screen.hpp"

#define BOX_OK 1
#define BOX_YES_NO 2

#define BOX_YES 2
#define BOX_NO 3

class dialog_box
{
    public:
    dialog_box(String title, byte option);
    dialog_box(String title, byte option, uint16_t x, uint16_t y);

    byte getOption();

    private:
    String title = "";
    byte option;
    uint16_t x = 160;
    uint16_t y = 200;
};

#include "../src/dialogue_box.cpp"

#endif