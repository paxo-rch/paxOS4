#ifndef shell_HPP
#define shell_HPP

#include "../../graphics/graphics.hpp"

class shell
{
    public:
    void addLine(String line);
    void getKeyboard();

    private:
    String text;
};

#include "../src/shell.cpp"

#endif