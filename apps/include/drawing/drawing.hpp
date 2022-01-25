#ifndef APP_DRAWING_HPP
#define APP_DRAWING_HPP

#include "../../../graphics/graphics.hpp"

#include "../../../widgets/widgets.hpp"

extern bool (*loop_system)(void);

#define PENCIL 0
#define PEN 1
#define RUBBER 3

namespace app_drawing
{
    bool run();
    bool draw_gui();
    bool loop();
    bool pencil(uint16_t x, uint16_t y, uint16_t strength, uint16_t radius);
    bool pen(uint16_t x, uint16_t y, uint16_t radius);
    bool rubber(uint16_t x, uint16_t y, uint16_t radius);
    bool edit();
    bool tools();
    bool loop_tools();

    button newProject(160, 400, "New Project", 0x7bcf, 0xFFFF);

    uint16_t color = 0x0000;
    byte tool_used = 0;
    String file_opended = "";
}

#include "drawing.cpp"

#endif /* APP_DRAWING_HPP */