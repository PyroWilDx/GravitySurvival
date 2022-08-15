#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Entity.hpp"

class RenderWindow {
public:
    RenderWindow(const char *title, int w, int h);

    void setBackgroundColor(int r, int g, int b);

    SDL_Texture *loadTexture(const char *filePath);

    void cleanUp();

    void clear();

    void render(Entity &entity);

    void display();

    inline SDL_Renderer *getRenderer() { return renderer; }

private:
    SDL_Window *window;
    SDL_Renderer *renderer;
};