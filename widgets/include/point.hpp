#ifndef __POINT__
#define __POINT__

#include <stdint.h>

class Point 
{
    public:
        Point();
        Point(const uint16_t x, const uint16_t y);

        uint16_t getX(void) const;
        uint16_t getY(void) const;

        void setX(const uint16_t& x);
        void setY(const uint16_t& y);

        bool isNull(void) const;

        bool operator ==(const Point& other);
        bool operator !=(const Point& other);

        Point operator+(const Point &other);
        Point operator-(const Point &other);

        bool operator>(const Point &other);
        bool operator<(const Point &other);

    private:
        uint16_t m_x;
        uint16_t m_y;
};

#endif /* __POINT__ */