#ifndef _SIMPLE_BOX_
#define _SIMPLE_BOX_

#include "GUI.hpp"
#include "../../graphics/graphics.hpp"

class Box : public GUI
{
    public:
    Box(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height);
    void draw();
    bool isTouch();
    bool isFocused();
};

Box::Box(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height)
{
    setX(x);
    setY(y);
    setHeight(height);
    setWidth(width);
}

void Box::draw()
{
    tft.fillRoundRect(getX(), getY(), getWidth(), getHeight(), 10, getBackgroundColor());
    tft.drawRoundRect(getX(), getY(), getWidth(), getHeight(), 10, getBorderColor());
}

bool Box::isTouch()
{
    uint16_t tx, ty;
    tft.getTouch(&tx, &ty);
    if(screenIsTouch() && getX() < tx && tx < getX() + getWidth()&& getY() < ty && ty < getY() + getHeight())
    {
        tft.fillRoundRect(getX(), getY(), getWidth(), getHeight(), 10, 0x32B5);
        tft.drawRoundRect(getX(), getY(), getWidth(), getHeight(), 10, getBorderColor());
        while(screenIsTouch());
        drawAll();  
    }
}

bool Box::isFocused()
{
    uint16_t tx, ty;
    tft.getTouch(&tx, &ty);
    if(screenIsTouch() && getX() < tx && tx < getX() + getWidth()&& getY() < ty && ty < getY() + getHeight())
        return 1;
    return 0;
}

#endif // _SIMPLE_BOX