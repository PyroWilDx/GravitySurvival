#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Entity.hpp"

using namespace std;

class Text : public Entity {
public:
    Text(int x, int y, const string &font_path, int font_size, const string &text, const SDL_Color &color,
         SDL_Renderer *renderer);

private:
    SDL_Texture *loadFont(const string &font_path, int font_size, const string &text, const SDL_Color &color,
                          SDL_Renderer *renderer);
};

