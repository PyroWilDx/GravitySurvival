#include "Entity.hpp"
#include "Utils.hpp"

using namespace Utils;

Entity::Entity(float vX, float vY, int x, int y, SDL_Texture *p_texture, int w, int h)
        : texture(p_texture) {
    pos = Vector2D(x, y);
    velocity[0] = vX;
    velocity[1] = vY;
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = w;
    currentFrame.h = h;
}

void Entity::move(float dt, float speed[]) {
    if (speed == NULL) {
        speed = velocity;
    }
    float distance = dt * TARGET_FPS;
    pos.addXY(speed[0] * distance, speed[1] * distance);
}