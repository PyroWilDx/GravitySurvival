#include "Vector2D.hpp"

using namespace std;

Vector2D::Vector2D()
        : x(0), y(0) {}

Vector2D::Vector2D(float p_x, float p_y)
        : x(p_x), y(p_y) {}

void Vector2D::addXY(float p_x, float p_y) {
    x += p_x;
    y += p_y;
}

void Vector2D::setXY(float p_x, float p_y) {
    x = p_x;
    y = p_y;
}

float Vector2D::getX() {
    return x;
}

float Vector2D::getY() {
    return y;
}
