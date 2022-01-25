#ifndef NOTE_CPP
#define NOTE_CPP

#include "../../../graphics/graphics.hpp"
#include "../../../widgets/widgets.hpp"
#include "../../../hardware/hardware.hpp"

#include "note.hpp"


bool app_note::run()
{
    loop_system = app_note::menu;
}

bool app_note::menu()
{
    clearAllScreen(0xFEAC);
    newProject->draw();
    loop_system = app_note::menu_loop;
    return 0;
}

bool app_note::menu_loop()
{
    while(1)
    {
        if(newProject->isTouch())
        {
            loop_system = app_note::editor;
            return 0;
        }
    }
}

bool app_note::editor()
{
    clearAllScreen(0xFEAC);
    Keyboard->draw();
    loop_system = app_note::editor_loop;
    File doc = SD.open("/doc.txt");
    text = "";
    while(doc.available())
    {
        text += char(doc.read());
    }
    doc.close();
    Keyboard->setString(text);
    return 0;
}

bool app_note::editor_loop()
{
    if(Keyboard->isTouch())
    {
        tft.setFreeFont(&FreeMono12pt7b);
        String newText = Keyboard->getString();

        if (newText < text)
        {
            tft.setTextColor(0xFEAC);
            tft.setCursor(0, 50);
            tft.print(text);
            text = text.substring(0, text.length() - 1);
        }
        else
        {
            text = newText;
        }

        tft.setTextColor(0x0000);
        tft.setCursor(0, 50);
        tft.print(text);
        //SD.remove("doc.txt");
        File doc = SD.open("/doc.txt", FILE_WRITE);
        doc.print(text);
        doc.close();
    }
    return 0;
}

#endif