#pragma once

#include "Entity.hpp"

class Player : public Entity {
public:
    static float velocityMultiplier;

    void updateVelocity(int xY[], float dt);

    void attract(float speed, float direction, float dt);

    void reset();

    static Player *getInstance(SDL_Texture *texture = NULL);

private:
    int hp;

    static Player *instance;

    Player(SDL_Texture *texture);
};