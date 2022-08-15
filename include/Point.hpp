#pragma once

#include "Entity.hpp"

class Point : public Entity {
public:
    Point(int x, int y, float direction, SDL_Texture *texture);

    static Point generateRandomPoint(SDL_Texture *texture);

private:
    float direction;
};