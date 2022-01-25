#ifndef SD_CPP
#define SD_CPP

bool SD_card::init()
{
    if (!SD.begin(4))
    {
        return 1;
    }
    return 0;
}

void SD_card::quitt()
{
}

bool SD_card::isConnected()
{
    uint8_t cardType = SD.cardType();

    if (cardType == CARD_NONE)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

#endif /* SD_CPP */