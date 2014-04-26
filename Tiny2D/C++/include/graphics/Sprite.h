#pragma once

#include "SDL.h"
#include "graphics/Drawable.h"

namespace Tiny2D {
class Sprite : virtual public Tiny2D::Drawable {
public:
    Sprite() {};
    Sprite(SDL_Renderer *renderer, const char *filename);
    virtual ~Sprite();

    virtual void load(SDL_Renderer *renderer, const char *filename);
    virtual void draw(SDL_Renderer *renderer);
    virtual void draw(SDL_Renderer *renderer, int x, int y);
    int getWidth();
    int getHeight();

protected:
    SDL_Texture *image = nullptr;
    SDL_Rect drawRect;
};
}
