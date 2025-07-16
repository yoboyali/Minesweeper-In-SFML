// minesweeper_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"

using namespace sf;
using namespace std;


int main()
{
    
 
    Game game;
    while (game.running()) {
        game.update();
        game.render();

    }
   
}

    