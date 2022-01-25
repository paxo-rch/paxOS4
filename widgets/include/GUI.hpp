#ifndef _GUI_HPP_
#define _GUI_HPP_

#include <stdint.h>
#include <vector>


class GUI
{
    public:
    GUI();
    ~GUI();

    virtual void draw() = 0;
    virtual bool isFocused() = 0;
    virtual bool isTouch() = 0;

    void testTouch();
    void drawAll();

    uint16_t getX();
    uint16_t getY();
    uint16_t getWidth();
    uint16_t getHeight();

    void setX(uint16_t value);
    void setY(uint16_t value);
    void setHeight(uint16_t value);
    void setWidth(uint16_t value);

    uint16_t getRelativeX();
    uint16_t getRelativeY();

    void setBackgroundColor(uint16_t color);
    uint16_t getBackgroundColor();

    void setBorderColor(uint16_t color);
    uint16_t getBorderColor();


    void addChild(GUI* child);
    void setParent(GUI* parent);

    void deleteChildren();

    GUI* getParent();

    bool isEnabled = 1;

    protected:
    std::vector<GUI*> m_children;
    GUI* m_parent = nullptr;

    private:
    bool hasChild = 0;

    uint16_t x, y, width, height;
    uint16_t relativeX, relativeY;
    uint16_t backgroundColor = 0xFFFF;
    uint16_t borderColor = 0x0000;
    uint16_t borderSize = 1;
};

#include "../src/GUI.cpp"

#endif
