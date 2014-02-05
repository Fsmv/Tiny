#include "graphics/Sprite.h"
#include "utils/Logger.h"
#include "SDL_image.h"


using namespace Tiny2D;

Sprite::Sprite(SDL_Renderer *renderer, const char *filename) {
    load(renderer, filename);
}

Sprite::~Sprite() {
    if(this->image != nullptr) {
        SDL_DestroyTexture(this->image);
    }
}

void Sprite::load(SDL_Renderer *renderer, const char *filename) {
    this->~Sprite();

    SDL_Surface *temp = IMG_Load(filename);
    this->image = SDL_CreateTextureFromSurface(renderer, temp);

    if(!this->image) {
        Logger logger("Sprite");
        logger.error("Failed to load image");
    }

    this->drawRect.w = temp->w;
    this->drawRect.h = temp->h;
    SDL_FreeSurface(temp);
}

void Sprite::draw(SDL_Renderer *renderer) {
    draw(renderer, 0, 0);
}

void Sprite::draw(SDL_Renderer *renderer, int x, int y) {
    this->drawRect.x = x;
    this->drawRect.y = y;
    SDL_RenderCopy(renderer, this->image, nullptr, &this->drawRect);
}
