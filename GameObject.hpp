#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Game.hpp"
#include "TextureManager.h"

class GameObject {
public:
    GameObject(const char* texturesheet, int x, int y);
    ~GameObject();

    void Update();
    void Render();
    void Clean();

private:
    int xpos;
    int ypos;
    
    SDL_Texture* objectTexture;
    SDL_Rect srcRect, destRect;
};

#endif