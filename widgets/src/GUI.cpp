#ifndef _GUI_CPP_ 
#define _GUI_CPP_

#include "../include/GUI.hpp"

GUI::GUI()
{

}

GUI::~GUI()
{
    for(int i = 0; i < m_children.size(); i++)
    {
        if(m_children[i] != nullptr)
            delete m_children[i];
    }
}

void GUI::deleteChildren()
{
    for(int i = 0; i < m_children.size(); i++)
    {
        if(m_children[i] != nullptr)
            delete m_children[i];
    }
}

void GUI::drawAll()
{
    if(isEnabled == false)
        return;

    draw();

    for(int i = 0; i < m_children.size(); i++)
    {
        if(m_children[i] != nullptr)
            m_children[i]->drawAll();
    }
}

void GUI::testTouch()
{
    if(isEnabled == false)
        return;

    if(hasChild && isFocused())
    {
        for(int i = 0; i < m_children.size(); i++)
        {
            if(m_children[i] != nullptr)
                m_children[i]->testTouch();
        }
    }
    else if(!hasChild && isFocused())
    {
        isTouch();
    }
}

uint16_t GUI::getX()
{
    if(m_parent == nullptr)
        return x;
    else
        return m_parent->getX() + x;
}

uint16_t GUI::getY()
{
    if(m_parent == nullptr)
        return y;
    else
        return m_parent->getY() + y;
}

uint16_t GUI::getHeight()
{
    return height;
}

uint16_t GUI::getWidth()
{
    return width;
}

void GUI::setX(uint16_t value)
{
    x = value;
}

void GUI::setY(uint16_t value)
{
    y = value;
}

void GUI::setHeight(uint16_t value)
{
    height = value;
}

void GUI::setWidth(uint16_t value)
{
    width = value;
}

uint16_t GUI::getRelativeX()
{
    return x;
}

uint16_t GUI::getRelativeY()
{
    return y;
}

void GUI::setBackgroundColor(uint16_t color)
{
    backgroundColor = color;
}

uint16_t GUI::getBackgroundColor()
{
    return backgroundColor;
}

void GUI::setBorderColor(uint16_t color)
{
    borderColor = color;
}

uint16_t GUI::getBorderColor()
{
    return borderColor;
}

void GUI::addChild(GUI* child)
{
    if(child != nullptr)
    {
        hasChild = 1;
        m_children.push_back(child);
        child->setParent(this);
    }
}

void GUI::setParent(GUI* parent)
{
    m_parent = parent;
}

GUI* GUI::getParent()
{
    if(m_parent!=nullptr)
        return m_parent;
}

#endif // _GUI_CPP_