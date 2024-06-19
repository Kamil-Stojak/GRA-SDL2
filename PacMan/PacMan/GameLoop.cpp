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
    isGameOver = false;
}

GameLoop::~GameLoop() {
    Clear();
}

bool GameLoop::getGameState() {
    return GameState;
}

void GameLoop::Intialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL Initialization Failed: " << SDL_GetError() << std::endl;
        return;
    }

// Tworzenie okna
    window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if (window) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            std::cout << "Initialization successful" << std::endl;

            // Ładowanie tekstur
            player = TextureManager::Texture("Image/shiba2.png", renderer);
            background = TextureManager::Texture("Image/TLO2.png", renderer);
            blockTexture = TextureManager::Texture("Image/KOSTKA.png", renderer);
            hurdleTexture = TextureManager::Texture("Image/PLOTEK.png", renderer);
            gameOverBackground = TextureManager::Texture("Image/TLO.png", renderer);
            for (int i = 0; i < 10; ++i) {
                std::string path = "Image/liczby/" + std::to_string(i) + ".png";
                digits[i] = TextureManager::Texture(path.c_str(), renderer);
            }

            // Obsługa błędów ładowania tekstur
            if (!player || !background || !blockTexture || !hurdleTexture || !gameOverBackground) {
                std::cout << "Failed to load textures" << std::endl;
                GameState = false;
                return;
            }

            // Inicjalizacja bloków i przeszkód
            for (int i = 0; i < WIDTH / 40 + 1; ++i) {
                SDL_Rect block = { i * 40, HEIGHT - 40, 40, 40 };
                blocks.push_back(block);
            }
            for (int i = 1; i < WIDTH / 200; ++i) {
                SDL_Rect hurdle = { i * 200 + rand() % 200, HEIGHT - 70, 20, 60 };
                hurdles.push_back(hurdle);
            }
            GameState = true;//<------- Gra jest gotowa do uruchomienia w tym miejscu
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
        GameState = false;// Zamknięcie gry przy wyjściu z okna
    }

    //skakanie
    if (!isGameOver && event1.type == SDL_KEYDOWN && event1.key.keysym.sym == SDLK_SPACE && jumpCount < 2) {
        isJumping = true;
        playerYVelocity = -15;
        jumpCount++;
    }
}

//ruch postaci, kolizje, punkty
void GameLoop::Update() {

    // Ustawienia graficzne postaci w px
    srcPlayer.h = 31;
    srcPlayer.w = 27;
    srcPlayer.x = srcPlayer.y = 0;

    destPlayer.w = 27;  
    destPlayer.h = 31;  
    destPlayer.x = 10;
    if (destPlayer.y == 0) {
        destPlayer.y = HEIGHT - 75;//położenia postaci
    }

// Obsługa skoku postaci
    if (!isGameOver && isJumping) {
        destPlayer.y += playerYVelocity;
        playerYVelocity += 1;
        if (destPlayer.y >= HEIGHT - 75) {
            destPlayer.y = HEIGHT - 75;
            isJumping = false;
            jumpCount = 0;
        }
    }

    UpdateBlocksAndHurdles();// Aktualizacja pozycji bloków i przeszkód
    CheckCollisions();// Sprawdzenie kolizji postaci z przeszkodami
    
    static int scoreCounter = 0;
    scoreCounter++;

    // Zwiększenie punktacji co 30 klatek gry
    if (!isGameOver && scoreCounter >= 30) {
        score++;
        scoreCounter = 0;
    }

    SDL_Delay(20);// Opóźnienie gry dla płynniejszego działania
}

// Aktualizacja pozycji bloków i przeszkód
void GameLoop::UpdateBlocksAndHurdles() {
    for (auto& block : blocks) {
        block.x -= 2;
        if (block.x < -40) {
            block.x = WIDTH;// Przesunięcie bloku na początek ekranu po opuszczeniu go
        }
    }
    
    for (auto& hurdle : hurdles) {
        hurdle.x -= 2;
        if (hurdle.x < -40) {
            hurdle.x = WIDTH + rand() % 200;// Przesunięcie przeszkody na początek ekranu po opuszczeniu go

        }
    }
}

// Sprawdzenie kolizji postaci z przeszkodami
void GameLoop::CheckCollisions() {
    for (const auto& hurdle : hurdles) {
        if (SDL_HasIntersection(&destPlayer, &hurdle)) {
            isGameOver = true; // Ustawienie stanu GameOver przy kolizji z przeszkodą
            break;
        }
    }
}

// Renderowanie gry
void GameLoop::Render() {
    SDL_RenderClear(renderer);// Wyczyszczenie renderera
    SDL_RenderCopy(renderer, background, NULL, NULL);// Renderowanie tła gry

// Renderowanie bloków
    for (const auto& block : blocks) {
        SDL_RenderCopy(renderer, blockTexture, NULL, &block);
    }
    // Renderowanie przeszkód
    for (const auto& hurdle : hurdles) {
        SDL_RenderCopy(renderer, hurdleTexture, NULL, &hurdle);
    }

// Renderowanie postaci
    SDL_RenderCopy(renderer, player, &srcPlayer, &destPlayer);

    // Jeśli gra jest zakończona "renderuj ekran Game Over"
    if (isGameOver) {
        SDL_RenderCopy(renderer, gameOverBackground, NULL, NULL);
        RenderGameOver();// Renderowanie wyniku na ekranie Game Over
    } else {
        RenderScore();// Renderowanie wyniku w trakcie rozgrywki
    }

    SDL_RenderPresent(renderer);
}

// Renderowanie licznika punktów w trakcie rozgrywki
void GameLoop::RenderScore() {
    int tempScore = score;
    int digitX = WIDTH / 2 - 35;
    int digitWidth = 20;

    // Renderowanie cyfr wyniku na ekranie
    do {
        int digit = tempScore % 10;
        SDL_Rect dest = { digitX, HEIGHT / 2 - 15, digitWidth, 30 };
        SDL_RenderCopy(renderer, digits[digit], NULL, &dest);
        digitX -= digitWidth + 5;
        tempScore /= 10;
    } while (tempScore > 0);
}
// Renderowanie wyniku na ekranie Game Over
void GameLoop::RenderGameOver() {
    int tempScore = score;
    int digitX = WIDTH / 2 - 35;
    int digitY = HEIGHT / 2 + 50;
    int digitWidth = 20;

    // Renderowanie cyfr wyniku na ekranie Game Over
    do {
        int digit = tempScore % 10;
        SDL_Rect dest = { digitX, digitY, digitWidth, 30 };
        SDL_RenderCopy(renderer, digits[digit], NULL, &dest);
        digitX -= digitWidth + 5;
        tempScore /= 10;
    } while (tempScore > 0);
}
// Zwalnianie zasobów pamięci
void GameLoop::Clear() {
    SDL_DestroyTexture(player);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(blockTexture);
    SDL_DestroyTexture(hurdleTexture);
    SDL_DestroyTexture(gameOverBackground);
    for (int i = 0; i < 10; ++i) {
        SDL_DestroyTexture(digits[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
