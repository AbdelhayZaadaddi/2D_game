#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>

class Game {
private:
    bool isRunning;
    SDL_Window *window;
    int counter;

public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int hright, bool fullscreen);

    void handelEvents();

    void update();
    void render();
    void clean();

    bool running();

    static SDL_Renderer* renderer;


};

#endif