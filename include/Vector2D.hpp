#pragma once

#include <string>

class Vector2D {
public:
    Vector2D();

    Vector2D(float x, float y);

    void addXY(float x, float y);

    void setXY(float x, float y);

    float getX();

    float getY();

private:
    float x, y;
};