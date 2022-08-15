#include <cmath>
#include "Player.hpp"
#include "Utils.hpp"

using namespace Utils;

float Player::velocityMultiplier = 1;
Player *Player::instance = NULL;

Player::Player(SDL_Texture *texture)
        : Entity(0, 0, PLAYER_BASE_X, PLAYER_BASE_Y, texture, PLAYER_SIZE, PLAYER_SIZE), hp(PLAYER_BASE_HP) {}

void Player::updateVelocity(int xY[], float dt) {
    for (int i = 0; i < 2; i++) {
        switch (xY[i]) {
            case -1:
                if (velocity[i] < -PLAYER_BASE_VELOCITY) {
                    velocity[i] *= (1 + DT_MULTIPLIER * dt);
                } else if (velocity[i] <= 0) {
                    velocity[i] = -PLAYER_BASE_VELOCITY * BASE_VELOCITY_MULTIPLIER;
                } else {
                    velocity[i] -= OPPOSITE_DT_MULTIPLIER * dt;
                }
                break;
            case 0:
                velocity[i] *= (1 - SLOW_DT_MULTIPLIER * dt);
                break;
            case 1:
                if (velocity[i] > PLAYER_BASE_VELOCITY) {
                    velocity[i] *= (1 + DT_MULTIPLIER * dt);
                } else if (velocity[i] >= 0) {
                    velocity[i] = PLAYER_BASE_VELOCITY * BASE_VELOCITY_MULTIPLIER;
                } else {
                    velocity[i] += OPPOSITE_DT_MULTIPLIER * dt;
                }
                break;
        }
    }
}

void Player::attract(float speed, float direction, float dt) {
    float speedXY[2] = {(float) speed * std::cos(direction),
                        (float) -speed * std::sin(direction)};
    this->move(dt, speedXY);
}

void Player::reset() {
    pos.setXY(PLAYER_BASE_X, PLAYER_BASE_Y);
    velocity[0] = 0;
    velocity[1] = 0;
    hp = PLAYER_BASE_HP;
}

Player *Player::getInstance(SDL_Texture *texture) {
    if (instance == NULL) {
        instance = new Player(texture);
    }
    return instance;
}