#ifndef DEF_RECT_TEXT
#define DEF_RECT_TEXT

class textZone
{
public:
    printRectText(uint16_t px, uint16_t py, uint16_t sx, uint16_t sy, uint16_t color);
    void setText(String text);
    void draw();

private:
    uint16_t color;
    int posx, posy;
    int sizex, sizey;
};

#include "text.cpp"

#endif