#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "TextureManager.h"

class GameLoop {
private:
//okno gry
    const int HEIGHT = 640;
    const int WIDTH = 800;


    bool GameState;
    SDL_Window* window;
    SDL_Event event1;
    SDL_Renderer* renderer;
    SDL_Texture* player;
    SDL_Texture* background;
    SDL_Texture* blockTexture;
    SDL_Texture* hurdleTexture;
    SDL_Rect srcPlayer, destPlayer;
    std::vector<SDL_Rect> blocks;
    std::vector<SDL_Rect> hurdles;
    SDL_Texture* digits[10];
    int score;
    bool isJumping;
    int playerYVelocity;
    int jumpCount;

public:
    GameLoop();
    bool getGameState();
    void Update();
    void Intialize();
    void Event();
    void Render();
    void Clear();
    void UpdateBlocksAndHurdles();
    void CheckCollisions();
    void RenderScore();
};
