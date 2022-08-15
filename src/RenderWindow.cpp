#include <iostream>
#include "RenderWindow.hpp"

using namespace std;

RenderWindow::RenderWindow(const char *title, int w, int h)
        : window(NULL), renderer(NULL) {
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
    if (window == NULL)
        cout << "Window failed to init. Error: " << SDL_GetError() << endl;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void RenderWindow::setBackgroundColor(int r, int g, int b) {
    SDL_SetRenderDrawColor(renderer, r, g, b, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

SDL_Texture *RenderWindow::loadTexture(const char *filePath) {
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);
    if (texture == NULL)
        cout << "Failed to load a texture. Error" << SDL_GetError() << endl;
    return texture;
}

void RenderWindow::cleanUp() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity &entity) {
    SDL_Rect src;
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;
    src.w = entity.getCurrentFrame().w;
    src.h = entity.getCurrentFrame().h;

    SDL_Rect dst;
    dst.x = entity.getPos().getX();
    dst.y = entity.getPos().getY();
    dst.w = entity.getCurrentFrame().w;
    dst.h = entity.getCurrentFrame().h;

    SDL_RenderCopy(renderer, entity.getTexture(), &src, &dst);
}

void RenderWindow::display() {
    SDL_RenderPresent(renderer);
}