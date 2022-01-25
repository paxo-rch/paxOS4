#ifndef LOOP_SYSTEM
#define LOOP_SYSTEM

#include "../tasks/task.hpp"

bool (*loop_system)(void);

#include "apps.hpp"
#include "include/home/home.hpp"

void setLoopSystem(bool (*sloop_system)(void))
{
    loop_system = sloop_system;
}

void backgroud_process()
{
    if(screenIsTouch())
    {
        uint16_t tx, ty;
        tft.getTouch(&tx, &ty);
        if(270 < tx && tx < 320 && 0 < ty && ty < 25)
            exitApp();
    }
    //tasks.executeTasks();
}

void wait(int time)
{
    int chrono = time + millis();
    while (chrono > millis()) 
    {
        backgroud_process();
    }
}

#endif