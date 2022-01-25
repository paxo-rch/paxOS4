#ifndef APP_CALCULATOR_HPP
#define APP_CALCULATOR_HPP

#include "../../../graphics/graphics.hpp"
#include "../../../widgets/widgets.hpp"

#include "calculate.hpp"

namespace app_calculator
{
    bool run();
    bool drawGui();
    bool calculate();

    Window gui();
}

#include "calculator.cpp"

#endif /* APP_CALCULATOR_HPP */