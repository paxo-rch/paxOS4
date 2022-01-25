#ifndef APP_HPP
#define APP_HPP

//#include "../tasks/task.hpp"

#include "include/home/home.hpp"
#include "include/drawing/drawing.hpp"
#include "include/note/note.hpp"
#include "include/snake/snake.hpp"

#include "loop_system.hpp"

void exitApp()
{
    loop_system = app_home::run;
}

void run_app_system()
{
    while (1)
    {
        loop_system = app_home::run;
        
        while (!(*loop_system)())
        {
            backgroud_process();
        }
    }
}

#endif /* APP_HPP */