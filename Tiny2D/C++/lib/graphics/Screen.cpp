#include "graphics/Screen.h"

using namespace Tiny2D;

Screen::Screen(int width, int height, InputHandler *ih) : ih(ih) {
    unsigned int rmask, bmask, gmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    bmask = 0x00ff0000;
    gmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    bmask = 0x0000ff00;
    gmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    this->surface = SDL_CreateRGBSurface(0, width, height, 32, rmask, bmask, gmask, amask);
    this->clipRect.w = this->drawRect.w = width;
    this->clipRect.h = this->drawRect.h = height;

    this->clipRect.x = this->drawRect.x = 0;
    this->clipRect.y = this->drawRect.y = 0;

    SDL_SetClipRect(this->surface, &this->clipRect);
}

void Screen::draw(SDL_Surface *surface) {
    render();
    //Blit surface overwrites the rect's x and y
    SDL_Rect drawCopy = drawRect;
    SDL_BlitSurface(this->surface, nullptr, surface, &drawCopy);
}

void Screen::translate(int dx, int dy) {
    this->drawRect.x -= dx;
    this->drawRect.y -= dy;

    this->clipRect.x = this->drawRect.x >= 0 ? 0 : -this->drawRect.x;
    this->clipRect.y = this->drawRect.y >= 0 ? 0 : -this->drawRect.y;

    SDL_SetClipRect(this->surface, &this->clipRect);
}
