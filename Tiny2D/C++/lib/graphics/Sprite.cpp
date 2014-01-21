#include "graphics/Sprite.h"
#include "SDL_image.h"

Sprite::Sprite(const char *filename) {
    this->image = IMG_Load(filename);
    if(!this->image) {
        Logger logger("Sprite");
        logger.error("Failed to load image");
    }

    this->drawRect.w = this->image->w;
    this->drawRect.h = this->image->h;
}

Sprite::~Sprite() {
    SDL_FreeSurface(this->image);
}

void Sprite::draw(SDL_Surface *surface) {
    draw(surface, 0, 0);
}

void Sprite::draw(SDL_Surface *surface, int x, int y) {
    this->drawRect.x = x;
    this->drawRect.y = y;
    SDL_BlitSurface(this->image, nullptr, surface, &drawRect);
}
