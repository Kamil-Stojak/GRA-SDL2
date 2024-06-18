#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class TextureManager {
public:
    static SDL_Texture* Texture(const char* filename, SDL_Renderer* renderer);
};

#endif // TEXTUREMANAGER_H
