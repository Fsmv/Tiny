#pragma once

#include "SDL.h"
#include "graphics/Drawable.h"

namespace Tiny2D {
class Sprite : virtual public Tiny2D::Drawable {
public:
    Sprite() {};
    Sprite(SDL_Renderer *renderer, const char *filename);
    virtual ~Sprite();

    void load(SDL_Renderer *renderer, const char *filename);
    void draw(SDL_Renderer *renderer);
    void draw(SDL_Renderer *renderer, int x, int y);
    int getWidth();
    int getHeight();

private:
    SDL_Texture *image;
    SDL_Rect drawRect;
};
}
