#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <string>
#include "TextureManager.h"

//rozdzielczość
const int WIDTH = 800;
const int HEIGHT = 600;

const int ANIMATION_FRAMES = 2; // Liczba klatek animacji
const int ANIMATION_SPEED = 10;

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
    SDL_Texture* playerTextures[ANIMATION_FRAMES];
    SDL_Texture* background;
    SDL_Texture* CHMORA;
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
    int animationCounter;
    int currentFrame;
    int speed;
    int licz;
    int P;
    int CHMORAA;
    int DAY;
    int WCHMORA;
    void CHMORKA();
    void UpdateBlocksAndHurdles();
    void CheckCollisions();
    void RenderScore();
    void RenderSpeed();
    void RenderGameOver();
    void InitializeGame();
};

#endif
