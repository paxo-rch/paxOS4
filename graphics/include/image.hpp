#ifndef IMAGE_HPP
#define IMAGE_HPP

#define BMP_IMG 0
#define JPG_IMG 1
#define JPEG_IMG 2
#define PNG_IMG 3

class image
{
public:
    image(String filename, uint16_t x, uint16_t y);
    void draw();
    byte type_file();

private:
    String filename;
    byte type;
    uint16_t x, y;
    void imgerror();
};

image::image(String filename, uint16_t x, uint16_t y)
{
    this->filename = filename;
    this->x = x;
    this->y = y;
}

byte image::type_file()
{
    if (filename.find(".bmp") || filename.find(".BMP"))
        return BMP_IMG;
    if (filename.find(".jpg") || filename.find(".JPG"))
        return JPG_IMG;
    if (filename.find("jpeg") || filename.find(".JPEG"))
        return JPEG_IMG;
    if (filename.find("png") || filename.find(".PNG"))
        return PNG_IMG;
}

void image::imgerror
#include "FS.h"
#include <SPI.h>
#include "../../libraries/TFT_eSPI/TFT_eSPI.h"

    TFT_eSPI tft = TFT_eSPI();

#include <TJpg_Decoder.h>
()
{
}

void image::draw()
{
    switch (type_file())
    {
    case BMP_IMG:
        bmpDrawSD(filename, x, y);
        break;
    case JPG_IMG:
        TJpgDec.drawSdJpg(x, y, filename);
        break;
    case JPEG_IMG:
        TJpgDec.drawSdJpg(x, y, filename);
        break;
    case PNG_IMG:
        imgerror();
        break;
    }
}

#endif /* IMAGE_HPP */