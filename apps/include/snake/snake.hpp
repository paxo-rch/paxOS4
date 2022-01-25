#ifndef APP_SNAKE
#define APP_SNAKE

#include "../../../graphics/graphics.hpp"

#define SNAKE_X snake[0][1] * 10
#define SNAKE_Y snake[0][0] * 10

namespace app_snake
{
    short difference(short a, short b);
    bool run();
}

short app_snake::difference(short a, short b)
{
    if (b > a)
        return b - a;
    else
        return a - b;
}

bool app_snake::run()
{
    uint16_t tx, ty;
    clearAllScreen(0xFFFF);
    tft.drawRect(10, 40, 300, 430, 0x0000);
    byte snake[100][2] = {0};
    byte head = 0;
    byte deriere = 0;
    bool point = true;
    byte pointxy[2] = {0, 0};
    short speed;
    bool gameover = false;
    long chrono_snake = millis();
    snake[0][1] = 16;
    snake[0][0] = 24;
    byte direc = 2;
    int score = 5;
    pointxy[0] = random(2, 30);
    pointxy[1] = random(5, 46);
    tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 10, 10, tft.color565(30, 180, 30));
    while (1)
        while (gameover == false)
        {
            tft.getTouch(&tx, &ty);
            if (score < 20)
            {
                speed = score;
            }
            if (millis() - 300 > chrono_snake - speed * 10)
            {
                for (byte i = score; i != 0; i--)
                {
                    snake[i][1] = snake[i - 1][1];
                    snake[i][0] = snake[i - 1][0];
                }

                tft.getTouch(&tx, &ty);
                if (screenIsTouch())
                {
                    tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 10, 10, tft.color565(30, 180, 30));
                    byte mem = direc;
                    if (difference(SNAKE_X, tx) > difference(SNAKE_Y, ty) && SNAKE_X < tx)
                        direc = 1;

                    else if (difference(SNAKE_X, tx) < difference(SNAKE_Y, ty) && SNAKE_Y < ty)
                        direc = 2;

                    else if (difference(SNAKE_X, tx) > difference(SNAKE_Y, ty) && SNAKE_X > tx)
                        direc = 3;

                    else if (difference(SNAKE_X, tx) < difference(SNAKE_Y, ty) && SNAKE_Y > ty)
                        direc = 4;
                    if (mem == 1 && direc == 3)
                        direc = 1;
                    if (mem == 2 && direc == 4)
                        direc = 2;
                    if (mem == 3 && direc == 1)
                        direc = 3;
                    if (mem == 4 && direc == 2)
                        direc = 4;
                }
                if (direc == 1)
                    snake[0][1]++;
                if (direc == 3)
                    snake[0][1]--;
                if (direc == 2)
                    snake[0][0]++;
                if (direc == 4)
                    snake[0][0]--;

                tft.fillRect(snake[0][1] * 10, snake[0][0] * 10, 10, 10, 0x0000);
                tft.fillRect(snake[score - 1][1] * 10, snake[score - 1][0] * 10, 10, 10, 0xFFFF);
                chrono_snake = millis();
            }
            tft.getTouch(&tx, &ty);
            if (screenIsTouch())
            {
                tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 10, 10, tft.color565(30, 180, 30));
                byte mem = direc;
                if (difference(SNAKE_X, tx) > difference(SNAKE_Y, ty) && SNAKE_X < tx)
                    direc = 1;

                else if (difference(SNAKE_X, tx) < difference(SNAKE_Y, ty) && SNAKE_Y < ty)
                    direc = 2;

                else if (difference(SNAKE_X, tx) > difference(SNAKE_Y, ty) && SNAKE_X > tx)
                    direc = 3;

                else if (difference(SNAKE_X, tx) < difference(SNAKE_Y, ty) && SNAKE_Y > ty)
                    direc = 4;

                if (mem == 1 && direc == 3)
                    direc = 1;
                if (mem == 2 && direc == 4)
                    direc = 2;
                if (mem == 3 && direc == 1)
                    direc = 3;
                if (mem == 4 && direc == 2)
                    direc = 4;
            }
            head = 1;
            while (head != score)
            {
                if ((snake[0][1] == snake[head][1] && snake[0][0] == snake[head][0]) || snake[0][0] > 46 || snake[0][0] == 3 || snake[0][1] == 0 || snake[0][1] > 30)
                {
                    tft.fillRect(snake[0][1] * 10, snake[0][0] * 10, 10, 10, tft.color565(200, 10, 10));
                    tft.setTextColor(0x0000);
                    tft.setFreeFont(&FreeMono24pt7b);
                    tft.drawCentreString(String(score), 160, 100, 4);

                    while(!screenIsTouch());

                    return 0;
                }
                head++;
            }
            if (snake[0][0] == pointxy[1] && snake[0][1] == pointxy[0])
            {
                pointxy[0] = random(2, 30);
                pointxy[1] = random(5, 46);
                tft.fillRect(pointxy[0] * 10, pointxy[1] * 10, 10, 10, tft.color565(30, 180, 30));
                score++;
            }
        }
}

#endif