#pragma once

#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "graphics/Drawable.h"

namespace Tiny2D {
class Text : virtual public Tiny2D::Drawable {
public:
    Text() {};
    Text(SDL_Renderer *renderer, std::string str, TTF_Font *font);
    Text(SDL_Renderer *renderer, std::string str, std::string font, int size);
    virtual ~Text();

    virtual void load(SDL_Renderer *renderer, std::string str, std::string font, int size);
    virtual void draw(SDL_Renderer *renderer);
    virtual void draw(SDL_Renderer *renderer, int x, int y);
    int getWidth();
    int getHeight();

    static TTF_Font *loadFont(std::string filename, int size);

    void setText(std::string);
    void setColor(const SDL_Color &color);
    void setFont(TTF_Font *font);
protected:
    void render();

    SDL_Texture *image = nullptr;
    SDL_Rect drawRect;
    SDL_Renderer *renderer = nullptr;
    std::string text;
    TTF_Font *font = nullptr;
    SDL_Color color;
};
}
