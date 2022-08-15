#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector2D.hpp"

class Entity {
public:
    Entity(float vX, float vY, int x, int y, SDL_Texture *texture, int w, int h);

    void move(float dt, float speed[] = NULL);

    inline Vector2D &getPos() { return pos; }

    inline SDL_Rect getCurrentFrame() { return currentFrame; }

    inline SDL_Texture *getTexture() { return texture; }

protected:
    Vector2D pos;
    // t[0] : horizontal, t[1] : vertical.
    float velocity[2];
    SDL_Rect currentFrame;
    SDL_Texture *texture;

private:
};