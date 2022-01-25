#ifndef HOUR_HPP
#define HOUR_HPP

#include "Sim800L.h"

int ACTUAL_HOUR = 0;
int ACTUAL_MINUTE = 0;

bool update_hour()
{
    Serial.println("hour actu");
    int day,month,year,minute,second,hour;
    GSM.getTime(&day,&month,&year,&hour,&minute,&second);
    ACTUAL_HOUR = hour;
    ACTUAL_MINUTE = minute;
    return 0;
}

int hourTimeUpdate = 15000;

void getHour(int *hours, int *minutes)
{
    if (hourTimeUpdate + 5000 < millis())
    {
        update_hour();
        hourTimeUpdate = millis();
    }
       
    Serial.println("give hour");
    *hours = ACTUAL_HOUR;
    *minutes = ACTUAL_MINUTE;
}

#endif