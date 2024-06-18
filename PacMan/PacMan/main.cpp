#include <SDL.h>
#include <iostream>
#include "GameLoop.h"

GameLoop game;

int main(int argc, char* argv[]) {
    game.Intialize();

    while (game.getGameState()) {
        game.Event();
        game.Update();
        game.Render();
    }

    game.Clear();

    return 0;
}
