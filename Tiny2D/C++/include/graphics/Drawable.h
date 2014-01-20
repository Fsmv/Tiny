#pragma once

#include "SDL.h"

namespace Tiny2D {
class Drawable {
public:
    /**
     * Draws this object onto the provided surface
     *
     * @param surface the surface to draw onto
     */
    virtual void draw(SDL_Surface surface) = 0;
};
}
