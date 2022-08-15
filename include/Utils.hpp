#pragma once

#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <SDL2/SDL.h>

using namespace std;

namespace Utils {
    const float PI = 3.1415926536f;

    const int WIDTH = 1280;
    const int HEIGHT = 720;
    const int PLAYER_SIZE = 32;
    const int POINT_SIZE = 8;

    const int PLAYER_BASE_X = WIDTH / 2;
    const int PLAYER_BASE_Y = HEIGHT / 2;
    const int PLAYER_BASE_HP = 2;

    const int TARGET_FPS = 60;

    const float PLAYER_BASE_VELOCITY = 2.0f;
    const float BASE_VELOCITY_MULTIPLIER = 1.2f;
    const float DT_MULTIPLIER = 0.8f;
    const float SLOW_DT_MULTIPLIER = 2.0f;
    const int OPPOSITE_DT_MULTIPLIER = 32;

    const float POINT_BASE_VELOCITY = 10.0f;

    // 0 : LEFT, 1 : RIGHT, 2 : UP, 3 : DOWN
    const int TOTAL_KEYS = 4;

    inline float getTime() {
        return SDL_GetTicks() * 0.001f;
    }

    float randomFloat();

    void triNaif(vector<string> &T);

};