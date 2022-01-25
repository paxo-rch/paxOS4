#ifndef SD_HPP
#define SD_HPP

#include <SD.h>

namespace SD_card
{
    bool init();
    void quitt();
    bool isConnected();
}

#include "../src/SD.cpp"

#endif /* SD_HPP */