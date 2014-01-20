#pragma once

#include "graphics/Drawable.h"

namespace Tiny2D {
class Screen : Drawable {
public:
    Screen(int width, int height) : width(width), heigth(height);
    ~Screen();

    void draw(SDL_Surface *surface);
    virtual void tick(unsigned int dt);
    virtual void render();

    void translate(int dx, int dy);
private:
    int width, height;
    int offsetx = 0;
    int offsety = 0;
};
}
