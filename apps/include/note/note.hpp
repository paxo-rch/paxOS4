#ifndef NOTE_HPP
#define NOTE_HPP

namespace app_note
{
    bool run();

    bool menu();
    bool menu_loop();

    bool editor();
    bool editor_loop();

    String filename_opened = "";
    String text = "";
    button *newProject = new button(160, 400, "new", 0xAB00, 0xCD4E);
    keyboard *Keyboard = new keyboard(0xFFFF, 0x0000);
}

#include "note.cpp"

#endif