#include "Text.hpp"
#include <iostream>

using namespace std;

Text::Text(int x, int y, const string &font_path, int font_size, const string &text, const SDL_Color &color,
           SDL_Renderer *renderer)
        : Entity(0, 0, x, y, nullptr, 0, 0) {
    texture = loadFont(font_path, font_size, text, color, renderer);
    SDL_QueryTexture(texture, nullptr, nullptr, &currentFrame.w, &currentFrame.h);
}

SDL_Texture *Text::loadFont(const string &font_path, int font_size, const string &text, const SDL_Color &color,
                            SDL_Renderer *renderer) {
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
    if (!font) cerr << "Failed to load font.\n";

    auto text_surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!text_surface) cerr << "Faild to create text surface.\n";

    auto text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
    if (!text_texture) cerr << "Faild to create text texture.\n";

    SDL_FreeSurface(text_surface);
    return text_texture;
}