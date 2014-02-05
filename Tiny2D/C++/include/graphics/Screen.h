#pragma once

#include "SDL.h"
#include "graphics/Drawable.h"
#include "utils/InputHandler.h"

namespace Tiny2D {
class Screen : virtual public Drawable {
public:
    Screen(int width, int height, Tiny2D::InputHandler *ih);
    virtual ~Screen() { SDL_DestroyTexture(this->texture); }

    virtual void load(SDL_Renderer *renderer) {}
    void init(SDL_Renderer *renderer);
    void draw(SDL_Renderer *renderer);

    virtual void tick(unsigned int dt) = 0;
    virtual void render(SDL_Renderer *renderer) = 0;

    void translate(int dx, int dy);

protected:
    SDL_Texture *texture = nullptr;
    Tiny2D::InputHandler *ih;

private:
    SDL_Rect clipRect, drawRect;
};
}
