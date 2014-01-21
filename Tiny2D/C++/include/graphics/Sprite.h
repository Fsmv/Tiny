#pragma once

#include "SDL.h"
#include "graphics/Drawable.h"

namespace Tiny2D {
class Sprite : public Tiny2D::Drawable {
public:
    Sprite(const char *filename);
    ~Sprite();

    void draw(SDL_Surface *surface);
    void draw(SDL_Surface *surface, int x, int y);
    int getWidth();
    int getHeight();

private:
    SDL_Surface *image;
    SDL_Rect drawRect;
};
}
