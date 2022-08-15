#include "Point.hpp"
#include "Utils.hpp"

using namespace Utils;

Point::Point(int x, int y, float p_direction, SDL_Texture *texture)
        : Entity(0, 0, x, y, texture, POINT_SIZE, POINT_SIZE), direction(p_direction) {
    velocity[0] = POINT_BASE_VELOCITY * std::cos(p_direction);
    velocity[1] = POINT_BASE_VELOCITY * std::sin(p_direction);
}

Point Point::generateRandomPoint(SDL_Texture *texture) {
    float rd = randomFloat() * 4;
    int x, y;
    float rd_direction;
    if (rd < 1) {
        x = 0;
        y = randomFloat() * (HEIGHT - POINT_SIZE);
        rd_direction = randomFloat() * PI - PI / 2;
    } else if (rd < 2) {
        x = randomFloat() * (WIDTH - POINT_SIZE);
        y = 0;
        rd_direction = randomFloat() * PI - PI;
    } else if (rd < 3) {
        x = WIDTH - POINT_SIZE;
        y = randomFloat() * (HEIGHT - POINT_SIZE);
        rd_direction = randomFloat() * PI + PI / 2;
    } else {
        x = randomFloat() * (WIDTH - POINT_SIZE);
        y = HEIGHT - POINT_SIZE;
        rd_direction = randomFloat() * PI;
    }
    return Point(x, y, rd_direction, texture);
}