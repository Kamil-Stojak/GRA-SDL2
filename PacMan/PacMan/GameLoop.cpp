#include "GameLoop.h"
#include "TextureManager.h"

GameLoop::GameLoop() {
    window = NULL;
    renderer = NULL;
    GameState = false;
    playerYVelocity = 0;
    isJumping = false;
    score = 0;
    jumpCount = 0;
}

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
            //zdjęcia
            player = TextureManager::Texture("Image/shiba.png", renderer);
            background = TextureManager::Texture("Image/TLO2.png", renderer);
            blockTexture = TextureManager::Texture("Image/KOSTKA.png", renderer);
            hurdleTexture = TextureManager::Texture("Image/PLOTEK.png", renderer);
            //licznik zdjęcia
            for (int i = 0; i < 10; ++i) {
                std::string path = "Image/liczby/" + std::to_string(i) + ".png";
                digits[i] = TextureManager::Texture(path.c_str(), renderer);
            }
            //błąd textur
            if (!player || !background || !blockTexture || !hurdleTexture) {
                std::cout << "Failed to load textures" << std::endl;
                GameState = false;
                return;
            }
            
            for (int i = 0; i < WIDTH / 40 + 1; ++i) {
                SDL_Rect block = { i * 40, HEIGHT - 40, 40, 40 };
                blocks.push_back(block);
            }
            
            for (int i = 1; i < WIDTH / 200; ++i) {
                SDL_Rect hurdle = { i * 200 + rand() % 200, HEIGHT - 70, 20, 60 };
                hurdles.push_back(hurdle);
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
    if (event1.type == SDL_KEYDOWN && event1.key.keysym.sym == SDLK_SPACE && jumpCount < 2) {
        isJumping = true;
        playerYVelocity = -15;
        jumpCount++;
    }
}

void GameLoop::Update() {
    //postać
    srcPlayer.h = 60;
    srcPlayer.w = 60;
    srcPlayer.x = srcPlayer.y = 0;
//ogólnie spawn postaci
    destPlayer.w = 60;  
    destPlayer.h = 60;  
    destPlayer.x = 10;
    if (destPlayer.y == 0) {
        destPlayer.y = HEIGHT - 100;
    }
//skok postaci
    if (isJumping) {
        destPlayer.y += playerYVelocity;
        playerYVelocity += 1;
        if (destPlayer.y >= HEIGHT - 100) {
            destPlayer.y = HEIGHT - 100;
            isJumping = false;
            jumpCount = 0; // <---- Reset liczby skoków po wylądowaniu
        }
    }

    UpdateBlocksAndHurdles();
    CheckCollisions();
    
    static int scoreCounter = 0;
    scoreCounter++;
    if (scoreCounter >= 30) { // Liczenie punktów co 30 cykli
        score++;
        scoreCounter = 0;
    }

    // Opóźnienie aby spowolnić grę
    SDL_Delay(20);
}

void GameLoop::UpdateBlocksAndHurdles() {
    for (auto& block : blocks) {
        block.x -= 2;
        if (block.x < -40) {
            block.x = WIDTH;
        }
    }
    
    for (auto& hurdle : hurdles) {
        hurdle.x -= 2;
        if (hurdle.x < -40) {
            hurdle.x = WIDTH + rand() % 200;
        }
    }
}

void GameLoop::CheckCollisions() {
    for (const auto& hurdle : hurdles) {
        if (SDL_HasIntersection(&destPlayer, &hurdle)) {
            GameState = false;
            break;
        }
    }
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL);

    for (const auto& block : blocks) {
        SDL_RenderCopy(renderer, blockTexture, NULL, &block);
    }
    
    for (const auto& hurdle : hurdles) {
        SDL_RenderCopy(renderer, hurdleTexture, NULL, &hurdle);
    }

    SDL_RenderCopy(renderer, player, &srcPlayer, &destPlayer);
    
    RenderScore();

    SDL_RenderPresent(renderer);
}

void GameLoop::RenderScore() {
    int tempScore = score;
    int digitX = WIDTH - 70;
    int digitWidth = 20;
    
    do {
        int digit = tempScore % 10;
        SDL_Rect dest = { digitX, 10, digitWidth, 30 };
        SDL_RenderCopy(renderer, digits[digit], NULL, &dest);
        digitX -= digitWidth + 5;
        tempScore /= 10;
    } while (tempScore > 0);
}

void GameLoop::Clear() {
    SDL_DestroyTexture(player);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(blockTexture);
    SDL_DestroyTexture(hurdleTexture);
    for (int i = 0; i < 10; ++i) {
        SDL_DestroyTexture(digits[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
