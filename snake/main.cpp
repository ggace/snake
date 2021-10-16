/**
@file main.cpp
*/

#include <iostream>
using namespace std;

#include <conio.h>

#include "common.h"
#include "snake_game.h"

int main()
{
    SnakeGame game;
    ReturnCode ret;

    while (FOREVER)
    {
        ret = game.start();
        if (ret != RETURN_SUCCESS)
            return 1;

        ret = game.play();
        if (ret == RETURN_NEWGAME)
            continue;
        else if (ret == RETURN_EXIT)
            return 0;
        else if ((ret != RETURN_STOP) && (ret != RETURN_SUCCESS))
            return 1;

        ret = game.stop();

        if (ret == RETURN_NEWGAME)
            continue;

        break;
    }

    return 0;
}