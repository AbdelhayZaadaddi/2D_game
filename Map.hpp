#ifndef MAP_HPP
#define MAP_HPP

#include "Game.hpp"

class Map{
private:
    SDL_Rect src, dest;
    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;

    int map[20][25];
public:
    Map();
    ~Map();

    void loadMap();
    void drawMap();
};

#endif