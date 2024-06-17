#include "GameLoop.h"
#include "TextureManager.h"

GameLoop::GameLoop() : GameState(false), window(nullptr), renderer(nullptr), player(nullptr) {}

bool GameLoop::getGameState() {
    return GameState;
}

void GameLoop::Intialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if (window) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            std::cout << "udalo sie" << std::endl;
            player = TextureManager::Texture("Image/shiba.png", renderer);
            background = TextureManager::Texture("Image/TLO2.png", renderer);
            if (player == nullptr) {
                std::cout << "Failed to load texture" << std::endl;
                GameState = false;
                return;
            }
            GameState = true;
        } else {
            std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl;
        }
    } else {
        std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
    }
}

void GameLoop::Event() {
    SDL_PollEvent(&event1);
    if (event1.type == SDL_QUIT) {
        GameState = false;
    }
    if (event1.type == SDL_MOUSEMOTION) {
        std::cout << event1.motion.x << "  X:Y  " << event1.motion.y << std::endl;
    }
    if (event1.type == SDL_MOUSEBUTTONDOWN) {
        std::cout << "KLIK!!!" << std::endl;
    }
}

void GameLoop::Update(){
//wielkość postaci
srcPlayer.h = 60;
srcPlayer.w = 60;
srcPlayer.x = srcPlayer.y = 0;

//Gdzie się spawni postać
destPlayer.w = 80;
destPlayer.h = 80;
destPlayer.x = 10; 
destPlayer.y++;

}

void GameLoop::Render() {
    SDL_RenderClear(renderer);
       SDL_RenderCopy(renderer, background, NULL, NULL); 
       SDL_RenderCopy(renderer, player, &srcPlayer, &destPlayer);

    SDL_RenderPresent(renderer);
}

void GameLoop::Clear() {
    SDL_DestroyTexture(player);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
