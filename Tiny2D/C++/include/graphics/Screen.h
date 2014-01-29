#pragma once

#include "SDL.h"
#include "graphics/Drawable.h"
#include "utils/InputHandler.h"

namespace Tiny2D {
class Screen : virtual public Drawable {
public:
    Screen(int width, int height, Tiny2D::InputHandler *ih);
    virtual ~Screen() { SDL_FreeSurface(this->surface); }

    void draw(SDL_Surface *surface);

    virtual void tick(unsigned int dt) = 0;
    virtual void render() = 0;

    void translate(int dx, int dy);

protected:
    SDL_Surface *surface;
    Tiny2D::InputHandler *ih;

private:
    SDL_Rect clipRect, drawRect;
};
}
