#ifndef Sim800L_h
#define Sim800L_h
#include <SoftwareSerial.h>
#include "Arduino.h"

#define DEFAULT_RX_PIN 27
#define DEFAULT_TX_PIN 26
#define DEFAULT_RESET_PIN 5 // pin to the reset pin Sim800L

#define DEFAULT_LED_FLAG true // true: use led.	 false: don't user led.
#define DEFAULT_LED_PIN 13    // pin to indicate states.

#define BUFFER_RESERVE_MEMORY 255
#define DEFAULT_BAUD_RATE 9600
#define TIME_OUT_READ_SERIAL 5000

class Sim800L : public SoftwareSerial
{
private:
    uint32_t _baud;
    int _timeout;
    String _buffer;
    bool _sleepMode;
    uint8_t _functionalityMode;
    String _locationCode;
    String _longitude;
    String _latitude;

    String _readSerial();
    String _readSerial(uint32_t timeout);

public:
    uint8_t RX_PIN;
    uint8_t TX_PIN;
    uint8_t RESET_PIN;
    uint8_t LED_PIN;
    bool LED_FLAG;

    Sim800L(void);
    Sim800L(uint8_t rx, uint8_t tx);
    Sim800L(uint8_t rx, uint8_t tx, uint8_t rst);
    Sim800L(uint8_t rx, uint8_t tx, uint8_t rst, uint8_t led);

    void turnOn()
    {
        digitalWrite(23, 1);
    }

    void turnOff()
    {
        digitalWrite(23, 0);
    }

    void begin();
    void begin(uint32_t baud);
    void reset();

    bool setSleepMode(bool state);
    bool getSleepMode();
    bool setFunctionalityMode(uint8_t fun);
    uint8_t getFunctionalityMode();

    bool setPIN(String pin);
    String getProductInfo();

    String getOperatorsList();
    String getOperator();

    bool calculateLocation();
    String getLocationCode();
    String getLongitude();
    String getLatitude();

    bool answerCall();
    void callNumber(char *number);
    bool hangoffCall();
    uint8_t getCallStatus();

    const uint8_t checkForSMS();
    void prepareForSmsReceive();
    bool sendSms(char *number, char *text);
    String readSms(uint8_t index);
    String getNumberSms(uint8_t index);
    bool delAllSms();

    String signalQuality();
    void setPhoneFunctionality();
    void activateBearerProfile();
    void deactivateBearerProfile();

    void getTime(int *day, int *month, int *year, int *hour, int *minute, int *second);
    String dateNet();
    bool updateRtc(int utc);
};

#include "../src/Sim800L.cpp"

Sim800L GSM(RX, TX);

#endif
