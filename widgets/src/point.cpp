#include "../include/point.hpp"

Point::Point()
{
    // empty
}


Point::Point(const uint16_t x = 0, const uint16_t y = 0) : m_x(x), m_y(y)  
{
    // empty
}

uint16_t Point::getX(void) const
{ 
    return m_x; 
}

uint16_t Point::getY(void) const
{ 
    return m_y; 
}

void Point::setX(const uint16_t& x)
{
    this->m_x = x;
}

void Point::setY(const uint16_t& y)
{
    this->m_y = y;
}

bool Point::isNull(void) const
{
    return (m_x == -1 && m_y == -1);
}

bool Point::operator ==(const Point& other)
{
    return (m_x == other.m_x && m_y == other.m_y);
}

bool Point::operator !=(const Point& other)
{
    return !(operator ==(other));
}

Point Point::operator+(const Point &other)
{
    return Point(this->m_x + other.m_x, this->m_y + other.m_y);
}

Point Point::operator-(const Point &other)
{
    return Point(this->m_x - other.m_x, this->m_y - other.m_y);
}

bool Point::operator>(const Point &other)
{
    return (this->m_x > other.m_x && this->m_y > other.m_y);
}

bool Point::operator<(const Point &other)
{
    return (this->m_x < other.m_x && this->m_y < other.m_y);
}