#pragma once

#include "SDL.h"
#include "graphics/Drawable.h"

namespace Tiny2D {
class Screen : public Drawable {
public:
    Screen(int width, int height);
    ~Screen() { SDL_FreeSurface(this->surface); }

    void draw(SDL_Surface *surface);

    virtual void tick(unsigned int dt) = 0;
    virtual void render() = 0;

    void translate(int dx, int dy);

protected:
    SDL_Surface *surface;

private:
    SDL_Rect clipRect, drawRect;
};
}
