#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <widgets/include/guielement.hpp>
#include <widgets/include/BOX.hpp>

#include "../../graphics/graphics.hpp"
#include <widgets/include/keyboard.hpp>

class Window : public GUI
{
    public:
        Window();
        
        void clear(void);
        void draw(void);
        bool isFocus()
        {
            if(opened())
                return screenIsTouch();
        }
        bool isTouch()
        {
            if(opened())
                return screenIsTouch();
        }

        void close(void);
        void open(void);

        bool opened(void);


    private:
        bool m_opened;
};

#endif /* __WINDOW__ */