#ifndef APP_DRAWING_CPP
#define APP_DRAWING_CPP

#include "drawing.hpp"

bool app_drawing::run()
{
    loop_system = app_drawing::draw_gui;
    return 0;
}

bool app_drawing::draw_gui()
{
    clearAllScreen(0x0000);
    bmpDrawSD("/paxo/apps/drawing/home_ico.bmp", 10, 50);
    app_drawing::newProject.draw();
    loop_system = app_drawing::loop;
    return 0;
}

bool app_drawing::loop()
{
    if (app_drawing::newProject.isTouch())
    {
        clearAllScreen(0xFFFF);
        tft.fillRoundRect(280, 40, 60, 400, 20, 0x0000);
        pencil(300, 100, 100, 10);
        pen(300, 250, 10);
        rubber(300, 400, 10);
        loop_system = app_drawing::edit;
    }

    return 0;
}

bool app_drawing::edit()
{
    uint16_t tx, ty;
    tft.getTouch(&tx, &ty);

    if (screenIsTouch())
    {
        if (tx < 280)
        switch (tool_used)
        {
            case 0:
                app_drawing::pencil(tx, ty, 50, 5);
            break;

            case 1:
                app_drawing::pen(tx, ty, 3);
            break;

            case 2:
                app_drawing::rubber(tx, ty, 20);
            break;
        }

        else if (280 < tx && tx < 480 && 40 < ty && ty < 440)
            app_drawing::tools();
    }
    return 0;
}

bool app_drawing::pencil(uint16_t x, uint16_t y, uint16_t strength, uint16_t radius)
{
    if (y < 30 + radius) return 1;

    for (int i = 0; i < strength; i++)
    {
        int ax;
        int ay;
        ax = random(-radius, radius);
        int gen = sqrt((radius * radius) - (ax * ax));
        ay = random(-gen, gen);
        tft.drawPixel(x + ax, y + ay, 0x5AEB);
    }

    return 0;
}

bool app_drawing::pen(uint16_t x, uint16_t y, uint16_t radius)
{
    if (y < 30 + radius) return 1;

    tft.fillCircle(x, y, radius, 0x236F);

    return 0;
}

bool app_drawing::rubber(uint16_t x, uint16_t y, uint16_t radius)
{
    if (y < 30 + radius) return 1;

    tft.fillCircle(x, y, radius, 0xFFFF);

    return 0;
}

bool app_drawing::tools()
{
    tft.fillRoundRect(280, 40, 60, 400, 20, 0x39E7);
    pencil(300, 100, 100, 10);
    pen(300, 250, 10);
    rubber(300, 400, 10);
    loop_system = app_drawing::loop_tools;
    return 0;
}

bool app_drawing::loop_tools()
{
    if (screenIsTouch)
    {
        uint16_t tx, ty;
        tft.getTouch(&tx, &ty);

        if (tx > 280) 
        {
            if (50 < ty && ty < 150)
            {
                tool_used = 0;
            }
            if (200 < ty && ty < 300)
            {
                tool_used = 1;
            }
            if (350 < ty && ty < 450)
            {
                tool_used = 2;
            }
        }
        else if(tx > 0)
        {
            loop_system = app_drawing::edit;
            tft.fillRoundRect(280, 40, 60, 400, 20, 0x0000);
            pencil(300, 100, 100, 10);
            pen(300, 250, 10);
            rubber(300, 400, 10);
        }
    }
    return 0;
}

#endif /* APP_DRAWING_CPP */