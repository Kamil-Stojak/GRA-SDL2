#include "GameLoop.h"

GameLoop* g = new GameLoop();

int main(int argc, char** argv) {

    g->Intialize();

    while (g->getGameState()) {
        g->Event();
        g->Render();
        g->Update();
    }

    g->Clear();

    delete g;

    return 0;
}
