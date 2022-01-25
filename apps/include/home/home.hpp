#ifndef HOME_APP_HPP
#define HOME_APP_HPP

#include "../../../graphics/graphics.hpp"

#include "../drawing/drawing.hpp"
#include "../note/note.hpp"
#include "../snake/snake.hpp"


extern bool (*loop_system)(void);

bool (*apps_include[])() = {
    app_drawing::run,
    app_note::menu,
    app_snake::run
};

String apps_name[] = {
    "dessin",
    "notes",
    "snake"
};

namespace app_home
{
    bool run();
    bool draw_gui();
    bool loop();

    byte page = 0;
}

#include "home.cpp"

#endif /* HOME_APP_HPP */