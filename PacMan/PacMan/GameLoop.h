#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include "TextureManager.h"

const int WIDTH = 800;
const int HEIGHT = 600;

class GameLoop {
public:
    GameLoop();
    ~GameLoop();
    
    bool getGameState();
    void Intialize();
    void Event();
    void Update();
    void Render();
    void Clear();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* player;
    SDL_Texture* background;
    SDL_Texture* blockTexture;
    SDL_Texture* hurdleTexture;
    SDL_Texture* gameOverBackground;
    SDL_Texture* digits[10];
    SDL_Rect srcPlayer, destPlayer;
    std::vector<SDL_Rect> blocks;
    std::vector<SDL_Rect> hurdles;
    SDL_Event event1;
    bool GameState;
    bool isGameOver;
    int playerYVelocity;
    bool isJumping;
    int score;
    int jumpCount;

    void UpdateBlocksAndHurdles();
    void CheckCollisions();
    void RenderScore();
    void RenderGameOver();
    void InitializeGame();
};

#endif // GAMELOOP_H
