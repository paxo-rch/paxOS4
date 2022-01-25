#ifndef BITMAP_HPP
#define BITMAP_HPP

#include <SD.h>
#include "../../hardware/hardware.hpp"

uint16_t read16(fs::File &f)
{
    uint16_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read(); // MSB
    return result;
}

uint32_t read32(fs::File &f)
{
    uint32_t result;
    ((uint8_t *)&result)[0] = f.read(); // LSB
    ((uint8_t *)&result)[1] = f.read();
    ((uint8_t *)&result)[2] = f.read();
    ((uint8_t *)&result)[3] = f.read(); // MSB
    return result;
}

#define BUFFPIXEL 20

void bmpDrawSD(char *filename, uint8_t x, uint16_t y)
{
    if(!SD_card::isConnected()) return;

    File bmpFile;
    int bmpWidth, bmpHeight;            // W+H in pixels
    uint8_t bmpDepth;                   // Bit depth (currently must be 24)
    uint32_t bmpImageoffset;            // Start of image data in file
    uint32_t rowSize;                   // Not always = bmpWidth; may have padding
    uint8_t sdbuffer[3 * BUFFPIXEL];    // pixel buffer (R+G+B per pixel)
    uint8_t buffidx = sizeof(sdbuffer); // Current position in sdbuffer
    boolean goodBmp = false;            // Set to true on valid header parse
    boolean flip = true;                // BMP is stored bottom-to-top
    int w, h, row, col;
    uint8_t r, g, b;
    uint32_t pos = 0, startTime = millis();

    if ((x >= tft.width()) || (y >= tft.height()))
        return;

    Serial.println();
    Serial.print(F("Loading image '"));
    Serial.print(filename);
    Serial.println('\'');

    // Open requested file on SD card
    if ((bmpFile = SD.open(filename)) == NULL)
    {
        Serial.print(F("File not found"));
        return;
    }

    // Parse BMP header
    if (read16(bmpFile) == 0x4D42)
    { // BMP signature
        Serial.print(F("File size: "));
        Serial.println(read32(bmpFile));
        (void)read32(bmpFile);            // Read & ignore creator bytes
        bmpImageoffset = read32(bmpFile); // Start of image data
        Serial.print(F("Image Offset: "));
        Serial.println(bmpImageoffset, DEC);
        // Read DIB header
        Serial.print(F("Header size: "));
        Serial.println(read32(bmpFile));
        bmpWidth = read32(bmpFile);
        bmpHeight = read32(bmpFile);

        int SIZEBUFFER = 100; //bmpHeight;
        if (480 < SIZEBUFFER)
            SIZEBUFFER = bmpHeight;

        if (SIZEBUFFER > bmpHeight)
            SIZEBUFFER = bmpHeight;

        uint16_t *image = new uint16_t[bmpWidth * SIZEBUFFER];
        //uint16_t *image = (uint16_t *)ps_malloc(bmpWidth * SIZEBUFFER * sizeof(uint16_t));

        if (read16(bmpFile) == 1)
        {                               // # planes -- must be '1'
            bmpDepth = read16(bmpFile); // bits per pixel
            if ((bmpDepth == 24) && (read32(bmpFile) == 0))
            {

                goodBmp = true;

                rowSize = (bmpWidth * 3 + 3) & ~3;
                if (bmpHeight < 0)
                {
                    bmpHeight = -bmpHeight;
                    flip = false;
                }

                w = bmpWidth;
                h = bmpHeight;
                if ((x + w - 1) >= tft.width())
                    w = tft.width() - x;
                if ((y + h - 1) >= tft.height())
                    h = tft.height() - y;

                int counter = 0;

                for (row = 0; row < h; row++)
                {
                    if (flip)
                        pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
                    else
                        pos = bmpImageoffset + row * rowSize;
                    if (bmpFile.position() != pos)
                    {
                        bmpFile.seek(pos);
                        buffidx = sizeof(sdbuffer);
                    }

                    for (col = 0; col < w; col++)
                    {
                        if (buffidx >= sizeof(sdbuffer))
                        {
                            bmpFile.read(sdbuffer, sizeof(sdbuffer));
                            buffidx = 0;
                        }

                        b = sdbuffer[buffidx++];
                        g = sdbuffer[buffidx++];
                        r = sdbuffer[buffidx++];

                        image[(row - counter) * bmpWidth + col] = tft.color565(r, g, b);
                    }

                    if (row - SIZEBUFFER  + 1 == counter)
                    {
                        tft.setSwapBytes(true);
                        tft.pushImage(x, y + counter, bmpWidth, SIZEBUFFER, image);
                        counter = row + 1;
                    }
                    if (bmpHeight - row < SIZEBUFFER && row + 1 == bmpHeight)
                      tft.pushImage(x, y + counter, bmpWidth, bmpHeight - counter, image);
                }
            }
        }

        //delete[] image;
        free(image);
    }

    bmpFile.close();
    if (!goodBmp)
        Serial.println(F("BMP format not recognized."));
}

// Bodmers BMP image rendering function

void bmpDrawSPIFFS(const char *filename, int16_t x, int16_t y) {

  if ((x >= tft.width()) || (y >= tft.height())) return;

  fs::File bmpFS;

  // Open requested file on SD card
  bmpFS = SPIFFS.open(filename, "r");

  if (!bmpFS)
  {
    Serial.println("SPIFFS File not found");
    return;
  }

  uint32_t seekOffset;
  uint16_t w, h, row, col;
  uint8_t  r, g, b;

  uint32_t startTime = millis();

  if (read16(bmpFS) == 0x4D42)
  {
    read32(bmpFS);
    read32(bmpFS);
    seekOffset = read32(bmpFS);
    read32(bmpFS);
    w = read32(bmpFS);
    h = read32(bmpFS);

    if ((read16(bmpFS) == 1) && (read16(bmpFS) == 24) && (read32(bmpFS) == 0))
    {
      y += h - 1;

      bool oldSwapBytes = tft.getSwapBytes();
      tft.setSwapBytes(true);
      bmpFS.seek(seekOffset);

      uint16_t padding = (4 - ((w * 3) & 3)) & 3;
      uint8_t lineBuffer[w * 3 + padding];

      for (row = 0; row < h; row++) {

        bmpFS.read(lineBuffer, sizeof(lineBuffer));
        uint8_t*  bptr = lineBuffer;
        uint16_t* tptr = (uint16_t*)lineBuffer;
        // Convert 24 to 16 bit colours
        for (uint16_t col = 0; col < w; col++)
        {
          b = *bptr++;
          g = *bptr++;
          r = *bptr++;
          *tptr++ = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
        }

        // Push the pixel row to screen, pushImage will crop the line if needed
        // y is decremented as the BMP image is drawn bottom up
        tft.pushImage(x, y--, w, 1, (uint16_t*)lineBuffer);
      }
      tft.setSwapBytes(oldSwapBytes);
      Serial.print("Loaded in "); Serial.print(millis() - startTime);
      Serial.println(" ms");
    }
    else Serial.println("BMP format not recognized.");
  }
  bmpFS.close();
}


#endif /* BITMAP_HPP */
