#include "TextureManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

SDL_Texture* TextureManager::Texture(const char* filelocation, SDL_Renderer* ren)
{
    SDL_Surface* surface = IMG_Load(filelocation);
    if (!surface) {
        std::cerr << "Unable to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, surface);
    SDL_FreeSurface(surface);
    return tex;
}
