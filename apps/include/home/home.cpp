#ifndef HOME_CPP
#define HOME_CPP

#include "home.hpp"

#define nb_app 3

bool app_home::run()
{
    loop_system = app_home::draw_gui;
    return 0;
}

bool app_home::draw_gui()
{
    clearAllScreen(0x05DC);
    loop_system = app_home::loop;

    byte apps_drawed = 0;

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            tft.fillRoundRect(20 + j * 100, 50 + i * 100, 80, 80, 20, 0xFFFF);
            tft.setFreeFont(&FreeMono12pt7b);
            tft.drawCentreString(String(apps_name[j + i*3]), 60 + j * 100, 130 + i * 100, 4);
            apps_drawed++;

            if (apps_drawed == nb_app)
                return 0;
        }
    }
    return 0;
}

bool app_home::loop()
{
    uint16_t tx, ty;
    tft.getTouch(&tx, &ty);

    byte apps_checked = 0;

    if(screenIsTouch())
    {
        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                if (20 + j * 100 < tx && tx < 100 + j * 100 && 50 + i * 100 < ty && ty < 130 + i * 100 && apps_checked < nb_app)
                {
                    tft.fillRoundRect(20 + j * 100, 50 + i * 100, 80, 80, 20, 0x0000);
                    while (screenIsTouch());
                    tft.fillRoundRect(20 + j * 100, 50 + i * 100, 80, 80, 20, 0xFFFF);
                    if (apps_checked < nb_app)
                        loop_system = apps_include[apps_checked];
                }
                apps_checked++;
            }
        }
    }

    return 0;
}

#endif /* HOME_CPP */