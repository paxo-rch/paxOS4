#ifndef PHONE_HPP
#define PHONE_HPP

#include "Sim800L.h"
#include <SoftwareSerial.h>

#define RX 26
#define TX 27

Sim800L SIM(RX, TX);

namespace SIM_MODS
{
    void init();
    void mode();
}

void SIM_MODS::init()
{
    pinMode(23, OUTPUT);
    digitalWrite(23, 1);
    GSM.begin();
}

#endif /* PHONE_HPP */