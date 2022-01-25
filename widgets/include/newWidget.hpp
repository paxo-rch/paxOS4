#ifndef _NEW_WIDGET_
#define _NEW_WIDGET_

#include "GUI.hpp"
#include "../../graphics/graphics.hpp"

class newWidget : public GUI
{
    public:
    newWidget(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height, void (*function)(void));
    void draw();
    bool isTouch();
    bool isFocused();

    private:
    void (*function)() = nullptr;
};

newWidget::newWidget(const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height, void (*function)(void))
{
    setX(x);
    setY(y);
    setHeight(height);
    setWidth(width);
}

void newWidget::draw()
{

}

bool newWidget::isTouch()
{
    uint16_t tx, ty;
    tft.getTouch(&tx, &ty);
    if(screenIsTouch() && getX() < tx && tx < getX() + getWidth() && getY() < ty && ty < getY() + getHeight())
    {
        function();
        return 1;
    }
    return 0;
}

bool newWidget::isFocused()
{
    uint16_t tx, ty;
    tft.getTouch(&tx, &ty);
    if(screenIsTouch() && getX() < tx && tx < getX() + getWidth()&& getY() < ty && ty < getY() + getHeight())
        return 1;
    return 0;
}

#endif // _NEW_WIDGET_