#define VERSION "1.1.1"

#include <iostream>
using namespace std;

#include "apps/apps.hpp"
#include "graphics/graphics.hpp"
#include "hardware/hardware.hpp"
#include "widgets/widgets.hpp"
#include "tasks/task.hpp"
#include <stdlib.h>

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap)
{
    // Stop further decoding as image is running off bottom of screen
    if (y >= tft.height())
        return 0;

    // This function will clip the image block rendering automatically at the TFT boundaries
    tft.pushImage(x, y, w, h, bitmap);

    // This might work instead if you adapt the sketch to use the Adafruit_GFX library
    // tft.drawRGBBitmap(x, y, bitmap, w, h);

    // Return 1 to decode next block
    return 1;
}

int initAll()
{
    //setPowerBoostKeepOn();

    tft.init();
    tft.setRotation(0);

    uint16_t calData[5] = {221, 3600, 225, 3711, 4};

    tft.setTouch(calData);

    Serial.begin(115200);
    psramInit();

    tft.fillScreen(0x0000);


    while (SD_card::init())
    {
        dialog_box errorBox("demarer sans \ncarte SD", BOX_YES_NO);
        if (errorBox.getOption() == BOX_YES)
            break;
        else
            ESP.restart();
    }

    tft.setSwapBytes(true);

    while(!SPIFFS.begin(true))
    {
        Serial.println("SPIFFS not detected\n");
        delay(10);
    }

    clearAllScreen();
    bmpDrawSD("/logo.bmp", 3, 100);
    delay(1000);
    tft.setTextColor(0x0000);
    tft.drawCentreString(VERSION, 160, 300, 4);
}

void setup()
{
    pinMode(19, INPUT_PULLDOWN); // allumer les peripheriques
    pinMode(22, OUTPUT);
    digitalWrite(22, HIGH);
    pinMode(25, OUTPUT);
    digitalWrite(25, HIGH);

    /*pinMode(23, OUTPUT);
    digitalWrite(23, 1);
    delay(100);
    GSM.begin(4800);
    GSM.println("AT");
    while (!GSM.available())
    {
        delay(200);
        GSM.println("AT");
    }
    Serial.println("sim800l OK");*/
    initAll();

    //Task* auto_hour_update = new Task(update_hour, 1000, 1);
}

void loop()
{
    //bmpDrawSPIFFS("/drawing.bmp", 0, 0);
    /*keyboard clavier(0xFFFF, 0x0000);
    clavier.draw();
    String lastStr = "";
    while(1)
    if(clavier.isTouch())
    {
        tft.setTextColor(0xFFFF);
        tft.drawCentreString(lastStr, 160, 100, 4);
        tft.setTextColor(0x0000);
        tft.drawCentreString(clavier.getString(), 160, 100, 4);
        lastStr = clavier.getString();
    }*/


    button home(160, 400, "menu", 0x7bcf, 0xd6ba);
    home.draw();

    while (!home.isTouch())
    {
        uint16_t tx, ty;
        tft.getTouch(&tx, &ty);
    }

      run_app_system();
}
