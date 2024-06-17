#include "GameLoop.h"

GameLoop::GameLoop() : window(nullptr), renderer(nullptr), GameState(false), event1{} {}

bool GameLoop::getGameState() {
    return GameState;
}

void GameLoop::Intialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "SDL Initialization Failed: " << SDL_GetError() << endl;
        return;
    }

    window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if (window) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            cout << "uda�o si�" << endl;
            GameState = true;
        } else {
            cout << "Renderer creation failed: " << SDL_GetError() << endl;
        }
    } else {
        cout << "Window creation failed: " << SDL_GetError() << endl;
    }
}

void GameLoop::Event() {
    SDL_PollEvent(&event1);
    if (event1.type == SDL_QUIT) {
        GameState = false;
    }
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void GameLoop::Clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
