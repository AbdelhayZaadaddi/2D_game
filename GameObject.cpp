#include "Game.hpp"
#include "TextureManager.h"
#include "GameObject.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y){
    objectTexture = TextureManager::LoadTexture(texturesheet);
    xpos = x;
    ypos = y;
}

void GameObject::Update(){
    xpos++;
    ypos++;
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.h = 32;
    destRect.w = 32;
    destRect.x = xpos;
    destRect.y = ypos;
}

void GameObject::Render(){
    SDL_RenderCopy(Game::renderer, objectTexture, &srcRect, &destRect);
}